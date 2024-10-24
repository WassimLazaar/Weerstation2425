// /*
//  * Copyright (c) 2017 Linaro Limited
//  *
//  * SPDX-License-Identifier: Apache-2.0
//  */

// #include <zephyr/kernel.h>
// #include <zephyr/device.h>
// #include <zephyr/drivers/uart.h>
#include "Weerstation.h"
#include <string.h>
#include <stdlib.h>

#define STACKSIZE 1024
#define PRIORITY 7

#define UART_DEVICE_NODE DT_NODELABEL(usart1) //Define the uart from DT

static const struct device *const uart_dev = DEVICE_DT_GET(UART_DEVICE_NODE); //Store in in variable uart_dev

volatile int temperature;
volatile int humidity;
volatile int pressure;
//volatile const char* timestamp = "24-10-2024";


/////////////////////////////////code voor het buffer gedeelte//////////////////////////////////////////////////
#define BUFFER_SIZE 200  // Voor 24 uur bij 1 meting per minuut

//Function to send characters over UART
void print_uart(char *buf)
{
	int msg_len = strlen(buf);

	for (int i = 0; i < msg_len; i++) {
		uart_poll_out(uart_dev, buf[i]);
	}
}

struct Measurement {
    int temperature;
    int pressure;
    int humidity;
    //const char* timestamp;  // Voor het opslaan van het tijdstip
};

struct Measurement databuffer[BUFFER_SIZE];
int buffer_index = 0;  // Huidige positie in de buffer

// Functie om metingen toe te voegen aan de buffer
void add_measurement(int temp, int press, int hum) {
    databuffer[buffer_index].temperature = temp;
    databuffer[buffer_index].pressure = press;
    databuffer[buffer_index].humidity = hum;
    //databuffer[buffer_index].timestamp = time;
    
    // Update de buffer index, en wrap rond als we het maximale aantal bereiken (ringbuffer)
    buffer_index = (buffer_index + 1) % BUFFER_SIZE;
}

void send_buffered_data(void) {
    const char* api_key = "ESPIsAFunDevice12345";

    // Loop door de buffer en verstuur alle metingen
    for (int i = 0; i < BUFFER_SIZE; i++) {
		if (databuffer[i].humidity == 0)
		{
			break;
		}
		
        struct Measurement meas = databuffer[i];
        
        // Formatteer de meetgegevens als POST-data
        int post_data_length = snprintf(NULL, 0, "api_key=%s&temperature=%d&pressure=%d&humidity=%d",
                                        api_key, meas.temperature, meas.pressure, meas.humidity) + 1;
        char* buff_post_data = (char*) calloc(post_data_length, sizeof(char));
        snprintf(buff_post_data, post_data_length, "api_key=%s&temperature=%d&pressure=%d&humidity=%d",
                 api_key, meas.temperature, meas.pressure, meas.humidity);

        // Verzend de POST-data via de ESP-module
        int content_length = snprintf(NULL, 0, "Content-Length: %d\r\n", post_data_length) + 1;
        char* buff_content = (char*) calloc(content_length, sizeof(char));
        snprintf(buff_content, content_length, "Content-Length: %d\r\n", post_data_length);

        int request_length = snprintf(NULL, 0, "POST /Request_data_ESP/post-data.php HTTP/1.1\r\n"
                                          "Host: 172.20.10.10\r\n"
                                          "Content-Type: application/x-www-form-urlencoded\r\n"
                                          "%s\r\n%s\r\n", buff_content, buff_post_data) + 1;
        char* buff_request = (char*) calloc(request_length, sizeof(char));
        snprintf(buff_request, request_length, "POST /Request_data_ESP/post-data.php HTTP/1.1\r\n"
                                              "Host: 172.20.10.10\r\n"
                                              "Content-Type: application/x-www-form-urlencoded\r\n"
                                              "%s\r\n%s\r\n", buff_content, buff_post_data);

        int sendData_length = snprintf(NULL, 0, "AT+CIPSEND=%d\r\n", request_length) + 1;
        char* buff_data_send = (char*) calloc(sendData_length, sizeof(char));
        snprintf(buff_data_send, sendData_length, "AT+CIPSEND=%d\r\n", request_length);

        // Verstuur de lengte van de POST data
        print_uart(buff_data_send);
        k_sleep(K_MSEC(2000));

        // Verstuur de daadwerkelijke POST data
        print_uart(buff_request);
        k_sleep(K_MSEC(2000));

        // Free de geheugenbuffers
        free(buff_post_data);
        free(buff_content);
        free(buff_request);
        free(buff_data_send);
    }

    print_uart("AT+CIPCLOSE\r\n"); // Sluit de verbinding na het versturen van de gegevens
    k_sleep(K_MSEC(2000));
}

///////////////////////////////////einde code voor het buffer gedeelte////////////////////////////////////////////////

static const struct device *get_bme280_device(void)
{
	const struct device *const dev = DEVICE_DT_GET_ANY(bosch_bme280);

	if (dev == NULL) {
		/* No such node, or the node does not have status "okay". */
		printk("\nError: no device found.\n");
		return NULL;
	}

	if (!device_is_ready(dev)) {
		printk("\nError: Device \"%s\" is not ready; "
		       "check the driver initialization logs for errors.\n",
		       dev->name);
		return NULL;
	}

	printk("Found device \"%s\", getting sensor data\n", dev->name);
	return dev;
}

void esp(void)
{
	const char* api_key = "ESPIsAFunDevice12345"; //API key extra protection

	//Request string for posting data to webserver
	const char* strRequest = "POST /Request_data_ESP/post-data.php HTTP/1.1\r\n"
							 "Host: 172.20.10.10\r\n"
							 "Content-Type: application/x-www-form-urlencoded\r\n";

	//Contionous flow of data to webserver
	while (1)
	{
		print_uart("AT\r\n"); //simple AT commando
		k_sleep(K_MSEC(2000));
		print_uart("AT+CIFSR\r\n"); //validate IP address
		k_sleep(K_MSEC(2000));
		print_uart("AT+CIPSTART=\"TCP\",\"172.20.10.10\",80\r\n"); //Start server connection to localhost
		k_sleep(K_MSEC(2000));

		//INIT data that needs to be posted to webserver (variables) 
		int post_data_length = snprintf(NULL, 0, "api_key=%s&temperature=%d&pressure=%d&humidity=%d", 
										api_key, temperature, pressure, humidity) + 1; //Get length of the message + 1 for /0
		char* buff_post_data = (char*) calloc(post_data_length, sizeof(char)); //Allocate space for the buffer
		snprintf(buff_post_data, post_data_length, "api_key=%s&temperature=%d&pressure=%d&humidity=%d", api_key, temperature, pressure, humidity); //store the message in buffer

		//INIT content length in REQUEST string 
		int content_length = snprintf(NULL, 0, "Content-Length: %d\r\n", post_data_length) + 1; //Get length of the string + 1 for /0
		char* buff_content = (char*) calloc(content_length, sizeof(char)); //Allocate space for the buffer
		snprintf(buff_content, content_length, "Content-Length: %d\r\n", post_data_length); //store the message in buffer

		//INIT FULL REQUEST for posting data
		int request_length = snprintf(NULL, 0, "%s%s\r\n%s\r\n", 
									strRequest, buff_content, buff_post_data) + 1; //Get length of the full request + 1 for /0
		char* buff_request = (char*) calloc(request_length, sizeof(char)); //Allocate space for the buffer
		snprintf(buff_request, request_length, "%s%s\r\n%s\r\n", strRequest, buff_content, buff_post_data); //store the message in buffer

		//INIT for CHIPSEND data length for ESP command
		int sendData_length = snprintf(NULL, 0, "AT+CIPSEND=%d\r\n", request_length) + 1; //Get length of the full request + 1 for /0
		char* buff_data_send = (char*) calloc(sendData_length, sizeof(char)); //Allocate space for the buffer
		snprintf(buff_data_send, sendData_length, "AT+CIPSEND=%d\r\n", request_length); //store the message in buffer

		// print_uart("AT+CWJAP=\"iPhone van Mike\",'\"wiskunde01\r\n");
		// k_sleep(K_MSEC(10000));
		k_sleep(K_MSEC(2000));

		print_uart(buff_data_send); //First send the length of receiving message to ESP
		k_sleep(K_MSEC(2000));
		print_uart(buff_request); //SEND the POST method with data to webserver
		k_sleep(K_MSEC(2000));

		//Free the allocations
		free(buff_post_data);
		free(buff_content);
		free(buff_request);
		free(buff_data_send);

		k_sleep(K_MSEC(2000));

		send_buffered_data();
	}
	print_uart("AT+CIPCLOSE\r\n"); //After program end connection
}

void sensor(void)
{
	const struct device *dev = get_bme280_device();

		for (int i = 0; i < BUFFER_SIZE; i++) {
	    databuffer[i].temperature = 0;
		databuffer[i].pressure = 0;
		databuffer[i].humidity = 0;
	}
	
	while(1){
		struct sensor_value temp, press, hum;

		sensor_sample_fetch(dev);
		sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temp);
		sensor_channel_get(dev, SENSOR_CHAN_PRESS, &press);
		sensor_channel_get(dev, SENSOR_CHAN_HUMIDITY, &hum);

		temperature = temp.val1;  
		pressure = press.val1;
		humidity = hum.val1;

		// Huidige tijd verkrijgen in milliseconden (of vervang door een RTC tijd indien beschikbaar)
		// uint32_t current_time = k_uptime_get() / 1000;  // Tijd in seconden

		// Voeg de meetwaarden toe aan de buffer
		//add_measurement(temperature, pressure, humidity);

	
		k_sleep(K_MSEC(2000));
	}
}

K_THREAD_DEFINE(sensor_id, STACKSIZE, sensor, NULL, NULL, NULL,
		PRIORITY, 0, 0);
K_THREAD_DEFINE(esp_id, STACKSIZE, esp, NULL, NULL, NULL,
		PRIORITY, 0, 0);
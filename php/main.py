import time
import serial
import random

# Function to read data from the serial port
def read_from_port(ser):
    while ser.in_waiting > 0:  # If incoming bytes are waiting to be read from the serial input buffer
        data_str = ser.read(ser.in_waiting).decode('ascii')  # Read the bytes and convert from binary array to ASCII
        print(data_str, end='')  # Print the incoming string without adding a newline automatically

# Function to send data to the serial port and read its response
def send_and_read(ser, data):
    wait_time = 0.1  # Time to wait between sending and reading (in seconds)
    time.sleep(wait_time)  # Wait before sending data
    ser.write(data)  # Send data
    time.sleep(wait_time)  # Wait after sending
    read_from_port(ser)  # Read response from serial port
    time.sleep(wait_time)  # Wait after reading

# Open serial port
esp8266 = serial.Serial("COM4", 115200, timeout=60)
temperature = None
humidity = None
pressure = None
x = 0

try:
    # Get device status
    send_and_read(esp8266, b'AT+CIFSR\r\n')  # Get the local IP address
    send_and_read(esp8266, b'AT+CIPSTART="TCP","172.20.10.2",80\r\n')  # Start TCP connection
    time.sleep(5)

    while (x < 10):
        # logger = esp8266.readline().decode('ascii')
        # if "temperature" in logger or "humidity" in logger or "pressure " in logger:
        #     temperature = logger[6:11]
        #     humidity = logger[23:30]
        #     pressure = logger[49:55]
        #     print(f"temperature = {temperature}, humidity = {humidity}, pressure = {pressure}")

        temperature = round(random.uniform(15.0, 30.0), 2) 
        humidity = round(random.uniform(30.0, 70.0), 2)    
        pressure = round(random.uniform(950.0, 1050.0), 2)

        api_key = 'ESPIsAFunDevice12345'

        post_data = f'api_key={api_key}&temperature={temperature}&humidity={humidity}&pressure={pressure}'
        
        # Create HTTP POST request
        request = f'POST /Request_data_ESP/post-data.php HTTP/1.1\r\n' \
                f'Host: 172.20.10.2\r\n' \
                f'User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\n' \
                f'Content-Type: application/x-www-form-urlencoded\r\n' \
                f'Content-Length: {len(post_data)}\r\n' \
                f'\r\n' \
                f'{post_data}' \
                f'\r\n'
        
        # 1. Send the length of the request
        send_and_read(esp8266, ('AT+CIPSEND=' + str(len(request)) + '\r\n').encode())
        
        # 2. Send the actual HTTP request
        send_and_read(esp8266, (request).encode())
        
        time.sleep(1)  # Give time for the response
        read_from_port(esp8266)  # Read the response from the server
        x += 1

    # Close the TCP connection
    send_and_read(esp8266, b'AT+CIPCLOSE\r\n')

finally:
    esp8266.close()  # Always close the serial connection

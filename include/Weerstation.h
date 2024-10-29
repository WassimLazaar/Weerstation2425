#ifndef WEERSTATION_H
#define WEERSTATION_H

//alle includes
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/__assert.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <string.h>
#include <stdlib.h>

//defines for system
#define STACKSIZE 1024
#define PRIORITY 7
#define UART_DEVICE_NODE DT_NODELABEL(usart1) //Define the uart from DT
#define BUFFER_SIZE 200  // Voor 24 uur bij 1 meting per minuut

#endif // WEERSTATION_H
#pragma once

#include <Arduino.h>

typedef struct {
    HardwareSerial *serial_port;
    uint8_t de_pin;
    uint8_t re_pin;
    uint32_t baud_rate;
} rs485_uart_t;

// Initialise RS485 with UART, DE, and RE pins
void rs485_init(rs485_uart_t *dev);

int rs485_read(rs485_uart_t *dev);
void rs485_write_buffer(rs485_uart_t *dev, uint8_t* data, size_t len);
int rs485_available(rs485_uart_t *dev);
void rs485_begin_transmission(rs485_uart_t *dev);
void rs485_end_transmission(rs485_uart_t *dev);

void rs485_enter_shutdown(rs485_uart_t *dev);
void rs485_exit_shutdown(rs485_uart_t *dev);

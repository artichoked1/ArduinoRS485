#include <Arduino.h>
#include "ArduinoRS485.h"

void rs485_init(rs485_uart_t *dev) {
    pinMode(dev->de_pin, OUTPUT);
    pinMode(dev->re_pin, OUTPUT);

    dev->serial_port->begin(dev->baud_rate);
    
    digitalWrite(dev->de_pin, LOW); // DE low for receive mode
    digitalWrite(dev->re_pin, LOW); // RE high for receive mode
}

void rs485_begin_transmission(rs485_uart_t *dev) {
    digitalWrite(dev->de_pin, HIGH); // Set DE high for transmit mode
    digitalWrite(dev->re_pin, HIGH);  // Set RE low for transmit mode
    delayMicroseconds(1000); // Allow time for the state change
}

void rs485_end_transmission(rs485_uart_t *dev) {
    digitalWrite(dev->de_pin, LOW); // Set DE low for receive mode
    digitalWrite(dev->re_pin, LOW); // Set RE high for receive mode
    delayMicroseconds(1000); // Allow time for the state change
}

void rs485_write_buffer(rs485_uart_t *dev, uint8_t* data, size_t len) {
    dev->serial_port->write(data, len); // Write the entire buffer to the serial port
    dev->serial_port->flush(); // Ensure all data is sent
}

int rs485_read(rs485_uart_t *dev) {
    if (dev->serial_port->available()) {
        return dev->serial_port->read(); // Will be 0–255 or -1
    }
    return -1;
}

int rs485_available(rs485_uart_t *dev) {
    return dev->serial_port->available(); // Returns the number of bytes available for reading
}

void rs485_enter_shutdown(rs485_uart_t *dev) {
    digitalWrite(dev->de_pin, LOW); // DE low for shutdown
    digitalWrite(dev->re_pin, LOW); // RE low for shutdown
}

void rs485_exit_shutdown(rs485_uart_t *dev) {
    rs485_end_transmission(dev); // Switch back to receive mode
}


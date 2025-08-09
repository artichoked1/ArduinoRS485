#include <Arduino.h> // Necesarry for PlatformIO
#include "ArduinoRS485.h"

// struct for RS485 UART device
rs485_uart_t rs485_dev = {
	.serial_port = &Serial,      // Hardware serial, can be changed to MCUs with other HardwareSerials like those in MCUDude's cores.
	.baud_rate = 9600,
	.de_pin	= 2,            // Driver Enable pin
	.re_pin	= 3             // Receiver Enable pin
};

void setup()
{
	Serial.begin(9600); // For debug, ideally use a different serial port for RS485 or software serial.
	rs485_init(&rs485_dev);
	Serial.println("RS485 demo started");
}

void loop()
{
	// Send "Hello" every second
	rs485_begin_transmission(&rs485_dev);
	const char msg[] = "Hello\n";
	rs485_write_buffer(&rs485_dev, (uint8_t *)msg, sizeof(msg) - 1);
	rs485_end_transmission(&rs485_dev);

	delay(1000);

	// Check for incoming data
	while (rs485_available(&rs485_dev) > 0) {
		int byteRead = rs485_read(&rs485_dev);
		if (byteRead >= 0)
			Serial.write(byteRead); // Print to debug console
	}
}

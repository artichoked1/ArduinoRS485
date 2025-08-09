# Arduino RS485 Library

This library provides a simple wrapper around serial for communication over RS485. It it uses lightweight C-style functions to send and receive data, and has transceiver shutdown/wake for those that support it.

## Installation

Just download the repo as a zip and go to `Sketch / Include Library / Add .ZIP Library...` in the Arduino IDE. 

You can also clone the repo into your `libraries` folder.

Or add it to your `platformio.ini` file under `lib_deps`:

```ini
lib_deps =
    https://github.com/artichoked1/ArduinoRS485.git#1.0.0
```

## Usage

```cpp
#include "RS485.h"

// Configure RS485 device
rs485_uart_t dev = {
    .serial_port = &Serial1,
    .baud_rate   = 9600,
    .de_pin      = 2,
    .re_pin      = 3
};

// Initialise
rs485_init(&dev);

// Begin transmission
rs485_begin_transmission(&dev);
uint8_t data[] = { 'H', 'i', '\n' };
rs485_write_buffer(&dev, data, sizeof(data));
rs485_end_transmission(&dev);

// Read data if available
if (rs485_available(&dev) > 0) {
    int byteRead = rs485_read(&dev);
}

// Enter/exit shutdown
rs485_enter_shutdown(&dev);
rs485_exit_shutdown(&dev);
```
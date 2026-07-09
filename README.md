[![Version: 1.0 Release](https://img.shields.io/badge/Version-1.0%20Release-green.svg)](https://github.com/0x007e/hal-avr-mega-uart) ![Release](https://github.com/0x007e/hal-avr-mega-uart/actions/workflows/release.yml/badge.svg) [![License GPLv3](https://img.shields.io/badge/License-GPLv3-lightgrey)](https://www.gnu.org/licenses/gpl-3.0.html)

# `hal-avr-mega-uart` - AVR ATmega SPI Hardware Abstraction

The `hal-avr-mega-uart` is a lightweight `uart` hardware abstraction library for AVR `ATmega16A` microcontrollers. It provides a clean interface for `uart` initialization and communication while hiding direct register-level interaction from higher software layers. The library is intended for projects that want to separate low-level device startup code from application logic and establish a small, reusable system layer for AVR targets.

## Features

- `UART` configuration for AVR `ATmega16A` devices.
- `UART` communication for AVR `ATmega16A` devices.
- Encapsulation of low-level register access.
- Compact and reusable API for embedded projects.
- Foundation for layered HAL architectures.

> The `hal-avr-mega-uart` library reduces coupling by providing a focused interface for essential `uart` system services. This improves portability inside a project, keeps startup code organized, and makes higher-level modules easier to maintain.

## File Structure

![File Structure](https://0x007e.github.io/hal-avr-mega-uart/uart_8c__incl.png)

```
hal/
├── common/
|   └── enums/
|       └── UART_enums.h
└── avr/
    └── uart/
        ├── uart.c
        └── uart.h
```

## Downloads

The library can be downloaded (`zip` or `tar`), cloned or used as submodule in a project.

| Type      | File               | Description              |
|:---------:|:------------------:|:-------------------------|
| Library   | [zip](https://github.com/0x007E/hal-avr-mega-uart/releases/latest/download/library.zip) / [tar](https://github.com/0x007E/hal-avr-mega-uart/releases/latest/download/library.tar.gz) | AVR ATmega16A uart library |

### Using with `git clone`

```sh
mkdir -p ./hal/
git clone https://github.com/0x007E/hal-common.git ./hal
mv ./hal/hal-common ./hal/common

mkdir -p ./hal/avr0
git clone https://github.com/0x007E/hal-avr-mega-uart.git ./hal/avr
mv ./hal/avr/hal-avr-mega-uart ./hal/avr/uart
```

### Using as `git submodule`

```sh
git submodule add https://github.com/0x007E/hal-common.git   ./hal/common
git submodule add https://github.com/0x007E/hal-avr-mega-uart.git ./hal/avr/uart
```

## Programming

Additional parameters like uart baudrate, handshake, pin definitions and many more can be setup in the [header file](./uart.h). A user friendly description can be found [here](https://0x007e.github.io/hal-avr-mega-uart/uart_8h.html).

```c
#include "../hal/avr/uart/uart.h"

int main(void)
{
	uart_init();

    uart_putchar('T');
    uart_putchar('E');
    uart_putchar('S');
    uart_putchar('T');
    uart_putchar('\n');
    uart_putchar('\r');

    UART_Data status = UART_Empty;

    while (1)
    {
        printf("\n\rEnter character: ");
        unsigned char data = uart_getchar(&status);

        printf("\n\rCharacter: %c", data);
        
        // Non-blocking
        if(uart_scanchar(&data) == UART_Received)
        {
            printf("\n\rCharacter received: %c", data);
        }

        printf("\n\rEnter a number: ");

        unsigned int value = 0;

        if(scanf("%u", &value) == 1)
        {
            printf("\n\rNumber: %u", value);
        }
        else
        {
            uart_clear();
            printf("\n\rError->NaN!");
        }
    }
}
```

> To use `floating point` with `printf`/`scanf` on the `avr` platform, a guide howto configure `Microcip Studio` can be found in this [blog entry](https://0x007e.github.io/microcontroller/2025/09/09/microchip-studio-setup-fp.html).

## Additional Information

| Type       | Link               | Description              |
|:----------:|:------------------:|:-------------------------|
| AVR0-Series | [pdf](https://ww1.microchip.com/downloads/en/devicedoc/atmel-8154-8-bit-avr-atmega16a_datasheet.pdf) | ATmega16A datasheet |

---

R. GAECHTER
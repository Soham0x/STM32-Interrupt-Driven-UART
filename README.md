# STM32 Interrupt-Driven UART Communication

A register-level UART communication project developed using the STM32C031C6 microcontroller.

## Overview

This project implements an interrupt-driven USART1 communication driver using direct register-level programming. It uses separate circular buffers for transmission and reception, allowing UART communication to take place without continuously polling the peripheral.

A simple command interface is implemented to control an LED through UART commands.

## Features

- Register-level USART1 configuration.
- UART transmission and reception using interrupts.
- Separate circular buffers for TX and RX.
- Non-blocking data handling.
- UART command-based LED control.
- LED status reporting.
- Tested using Wokwi simulation.

## UART Commands

| Command | Function |
|---|---|
| `LED ON` | Turns the LED ON |
| `LED OFF` | Turns the LED OFF |
| `STATUS` | Reports the LED status |

## Implementation

The USART1 peripheral is configured through its control and baud-rate registers. Interrupts are used to handle received and transmitted data.

Circular buffers manage incoming and outgoing data using head and tail indices.

The main application processes received commands and performs the corresponding LED operation.

## Hardware and Tools

- Microcontroller: STM32C031C6
- IDE: STM32CubeIDE
- Language: C
- Simulation: Wokwi
- Peripheral: USART1

## Project Structure

- `Core/` – Application source and header files.
- `Drivers/` – STM32 HAL and CMSIS dependencies.
- `CCCC.ioc` – STM32CubeMX configuration.
- `STM32C031C6TX_FLASH.ld` – Linker script.

## Future Improvements

- UART error handling.
- TX buffer overflow protection.
- Improved command parsing.
- Testing on physical STM32 hardware.

## Author

Developed as a hands-on embedded firmware learning project.
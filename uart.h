/**
 * @file uart.h
 * @brief Header file with declarations and macros for hardware UART.
 * 
 * This file provides function prototypes, type definitions, and constants for
 * hardware-based UART communication on AVR0 microcontrollers.
 * 
 * @author g.raf
 * @date 2025-09-27
 * @version 1.0 Release
 * @copyright
 * Copyright (c) 2025 g.raf
 * Released under the GPLv3 License. (see LICENSE in repository)
 * 
 * @note This file mostly becomes part of larger projects and subject to the license specified in the repository. For updates and the complete revision history, see the GitHub repository.
 *
 * @see https://github.com/0x007e/hal-avr-mega "AVR ATmega GitHub Repository"
 */

#ifndef UART_H_
#define UART_H_

	#ifndef F_CPU
		/**
		 * @def F_CPU
		 * @brief System clock frequency definition.
		 *
		 * @details
		 * This macro defines the operating frequency of the microcontroller's clock in Hertz. It is used for timing calculations. The value should match the actual hardware clock frequency to ensure correct timing behavior.
		 */
		#define F_CPU 12000000UL
	#endif

	#ifndef UART_BAUDRATE
        /**
         * @def UART_BAUDRATE
         * @brief Default UART communication baud rate.
         *
         * @details
         * Sets the default serial communication speed to 9600 baud. Common values are 9600, 19200, 38400, 57600, 115200.
         *
         * @note Override this macro before including uart.h for different communication speeds.
         */
        #define UART_BAUDRATE 9600UL
		
		// Required for setbaud.h
		#define BAUD UART_BAUDRATE
    #endif

    #ifndef UART_DATASIZE
        /**
         * @def UART_DATASIZE
         * @brief Number of data bits per frame (5-8).
         *
         * @details
         * Configures the character length transmitted/received:
         * Valid values: 5, 6, 7, 8, 9H, 9L (default: 8).
         * - 5 = 5 Bits
         * - 6 = 6 Bits
         * - 7 = 7 Bits
         * - 8 = 8 Bits
         *
         * @note 8 data bits (8N1) is the most common serial configuration.
         */
        #define UART_DATASIZE 8
    #endif

    #ifndef UART_PARITY
        /**
         * @def UART_PARITY
         * @brief Parity bit configuration.
         *
         * @details
         * Selects parity checking for error detection:
         * - 0 = no parity, default
         * - 1 = even parity
         * - 2 = odd parity
         *
         * @note Parity adds one bit to each frame for basic error checking.
         */
        #define UART_PARITY 0
    #endif

    #ifndef UART_STOPBITS
        /**
         * @def UART_STOPBITS
         * @brief Number of stop bits per frame (1-2).
         *
         * @details
         * Configures stop bits signaling frame end:
         * - 1 = 1 Bit (default)
	     * - 2 = 2 Bits
         *
         * @note Stop bits must be idle (high) level.
         */
        #define UART_STOPBITS 1
    #endif

    #ifndef UART_RXC_ECHO
        /**
         * @def UART_RXC_ECHO
         * @brief Enables local echo of received characters.
         *
         * @details
         * When defined, each received character is automatically transmitted back through TX (echo effect). Useful for terminal applications.
         *
         * @note Disabled automatically if UART_TXCIE or UART_UDRIE interrupts are enabled.
         */
        // #define UART_RXC_ECHO

        #ifdef _DOXYGEN_    // Used for documentation, can be ignored
            #define UART_RXC_ECHO
        #endif
    #endif
	
    #ifndef UART_HANDSHAKE
        /**
         * @def UART_HANDSHAKE
         * @brief Flow control / handshaking mode.
         *
         * @details
         * Configures flow control between communicating systems:
         * - 0 = Disabled (default)
         * - 1 = Software flow control (XON/XOFF)
         * - 2 = Hardware flow control (RTS/CTS)
         *
         * @note Enables reliable data transfer when receiver buffer overflows.
         */
        #define UART_HANDSHAKE 0
		
        #if UART_HANDSHAKE == 2
            /**
             * @def UART_HANDSHAKE_DDR
             * @brief DDR direction register for hardware handshake pins (RTS/CTS).
             */
            #ifndef UART_HANDSHAKE_DDR
                #define UART_HANDSHAKE_DDR DDRC
            #endif
			
            /**
             * @def UART_HANDSHAKE_PIN
             * @brief PIN register for hardware handshake pins (RTS/CTS).
             */
            #ifndef UART_HANDSHAKE_PIN
                #define UART_HANDSHAKE_PIN PINC
            #endif

            /**
             * @def UART_HANDSHAKE_PORT
             * @brief PORT register for hardware handshake pins (RTS/CTS).
             */
            #ifndef UART_HANDSHAKE_PORT
                #define UART_HANDSHAKE_PORT PORTC
            #endif

            /**
             * @def UART_HANDSHAKE_CTS_PIN
             * @brief Clear To Send input pin bitmask.
             *
             * @details
             * CTS pin signals when remote device is ready to receive data. Transmission pauses when CTS is inactive (low).
             */
            #ifndef UART_HANDSHAKE_CTS_PIN
                #define UART_HANDSHAKE_CTS_PIN  PINC0
            #endif

            /**
             * @def UART_HANDSHAKE_RTS_PIN
             * @brief Request To Send output pin bitmask.
             *
             * @details
             * RTS pin signals to remote device that local receiver is ready. Set active (high) when buffer has space.
             */
            #ifndef UART_HANDSHAKE_RTS_PIN
                #define UART_HANDSHAKE_RTS_PIN  PINC1
            #endif

        #endif

        #ifndef UART_HANDSHAKE_XON
            /**
             * @def UART_HANDSHAKE_XON
             * @brief XON character (transmit when ready to receive).
             */
            #define UART_HANDSHAKE_XON 0x11
        #endif
        
        #ifndef UART_HANDSHAKE_XOFF
            /**
             * @def UART_HANDSHAKE_XOFF
             * @brief XOFF character (transmit when not ready to receive).
             */
            #define UART_HANDSHAKE_XOFF 0x13
        #endif
    #endif

    #ifndef UART_STDMODE
        /**
         * @def UART_STDMODE
         * @brief Standard I/O integration mode (printf/scanf).
         *
         * @details
         * Enables avr-libc stdio functions over UART:
         * - 0 = None
         * - 1 = printf + scanf (default)
         * - 2 = printf only
         * - 3 = scanf only
         *
         * @note Requires fdevopen() setup in application code.
         */
        #define UART_STDMODE 1
    #endif

    /**
     * @defgroup UART_Interrupts UART Interrupt Control Macros
     * @brief Configuration macros for interrupt-based UART processing.
     *
     * @attention 
     * !!! Interrupts are NOT implemented in this library !!!
     * If interrupts are used, polling functions will be disabled. Users must implement ISR handlers separately.
     */
    /* @{ */
    #ifndef UART_RXCIE
        /**
         * @def UART_RXCIE
         * @brief Enable or disable UART RX Complete interrupt processing.
         *
         * @details
         * When defined, enables USART Receive Complete interrupt (RX_CIE). Intended for interrupt-driven receive handling via ISR(USART0_RXC_vect).
         *
         * @attention Interrupts are not implemented in this library. Defining this macro disables polling-based receive functions.
         *
         * @note Implement custom ISR for interrupt handling.
         */
         // #define UART_RXCIE
    #endif

    #ifndef UART_TXCIE
        /**
         * @def UART_TXCIE
         * @brief Enable or disable UART TX Complete interrupt processing.
         *
         * @details
         * When defined, enables USART Transmit Complete interrupt (TX_CIE).  Intended for interrupt-driven transmit handling via ISR(USART0_TXC_vect).
         *
         * @attention Interrupts are not implemented in this library. Defining this macro disables polling-based transmit functions. Mutually exclusive with UART_UDRIE.
         *
         * @note Implement custom ISR for interrupt handling.
         */
        // #define UART_TXCIE
    #endif

    #ifndef UART_UDRIE
        /**
         * @def UART_UDRIE
         * @brief Enable or disable UART Data Register Empty interrupt processing.
         *
         * @details
         * When defined, enables USART Data Register Empty interrupt (UDRIE). Intended for interrupt-driven transmit via ISR(USART0_DRE_vect). Automatically loads next byte when transmit buffer is empty.
         *
         * @attention Interrupts are not implemented in this library. Only available when UART_TXCIE is NOT defined.
         *
         * @note Implement custom ISR for interrupt handling.
         */
        #ifndef UART_TXCIE
            // #define UART_UDRIE
        #else
            #error "UART_TXCIE and UART_UDRIE cannot be used together"
        #endif
    #endif
    /* @} */

	#include <stdio.h>
	#include <avr/io.h>
	#include <util/setbaud.h>

	#include "../common/enums/UART_enums.h"

	void uart_init(void);
	void uart_disable(void);

	#if !defined(UART_TXCIE) && !defined(UART_UDRIE)
		char uart_putchar(char data);
	
		#if UART_STDMODE == 1 || UART_STDMODE == 2
			int uart_printf(char data, FILE *stream);
		#endif
	#endif

	#if !defined(UART_RXCIE)
			 char uart_getchar(UART_Data *status);
		UART_Data uart_scanchar(char *data);
		UART_Error uart_error_flags(void);
        
		#if UART_STDMODE == 1 || UART_STDMODE == 3
				 int uart_scanf(FILE *stream);
				void uart_clear(void);
		#endif
	#endif

	#if !defined(UART_TXCIE) && !defined(UART_UDRIE) && !defined(UART_RXCIE)
		#if UART_HANDSHAKE > 0
			UART_Handshake uart_handshake(UART_Handshake status);
		#endif
	#endif

#endif /* UART_H_ */
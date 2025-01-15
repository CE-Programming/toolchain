/**
 * @file
 * @authors
 * @brief CE SPI controller define file
 */

#ifndef SYS_SPI_H
#define SYS_SPI_H

#include <stdint.h>

/* @cond */
#define spi_ControlRegister0     ((volatile void*)0xF80000)
#define spi_ControlRegister1     ((volatile void*)0xF80004)
#define spi_ControlRegister2     ((volatile void*)0xF80008)
#define spi_StatusBits           ((const volatile void*)0xF8000C)
#define spi_InterruptControl     ((volatile void*)0xF80010)
#define spi_InterruptStatus      ((const volatile void*)0xF80014)
#define spi_FIFO                 ((volatile void*)0xF80018)
#define spi_InsideReservedRange  ((volatile void*)0xF8001C)
#define spi_Revision             ((const volatile void*)0xF80060)
#define spi_Features             (*(const volatile uint32_t*)0xF80064)
/* @endcond */

#endif

/**
 * @file
 * @authors
 * @brief CE SPI controller define file
 */

#ifndef SYS_SPI_H
#define SYS_SPI_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* @cond */
#define spi_ControlRegister0     ((volatile uint16_t*)0xF80000)
#define spi_ControlRegister1     ((volatile uint24_t*)0xF80004)
#define spi_ControlRegister2     ((volatile uint16_t*)0xF80008)

#define spi_ClockDivider         ((volatile uint16_t*)0xF80004)
#define spi_DataWidth            ((volatile uint8_t*)0xF80006)
#define spi_PadWidth             ((volatile uint8_t*)0xF80007)

#define spi_StatusBits           ((const volatile uint24_t*)0xF8000C)
#define spi_InterruptControl     ((volatile uint24_t*)0xF80010)
#define spi_InterruptStatus      ((const volatile uint8_t*)0xF80014)

#define spi_Fifo8                ((volatile uint8_t*)0xF80018)
#define spi_Fifo16               ((volatile uint16_t*)0xF80018)
#define spi_Fifo24               ((volatile uint24_t*)0xF80018)
#define spi_Fifo32               ((volatile uint32_t*)0xF80018)

#define spi_InsideReservedRange  (*((const volatile uint32_t*)0xF8001C))
#define spi_Revision             (*((const volatile uint32_t*)0xF80060))
#define spi_Features             (*((const volatile uint32_t*)0xF80064))
/* @endcond */

/* spi_ControlRegister0 */

#define SPI_CLOCK_POLARITY     (1 << 0)
#define SPI_CLOCK_PHASE        (1 << 1)
#define SPI_SLAVE              (0 << 2)
#define SPI_MASTER             (3 << 2)
#define SPI_SLAVE_MONO         (0 << 2)
#define SPI_SLAVE_STEREO       (1 << 2)
#define SPI_MASTER_MONO        (2 << 2)
#define SPI_MASTER_STEREO      (3 << 2)
#define SPI_OP_MODE            (3 << 2)
#define SPI_FS_JUSTIFY         (1 << 4)
#define SPI_FS_POLARITY        (1 << 5)
#define SPI_LSB                (1 << 6)
#define SPI_LOOP_BACK          (1 << 7)
#define SPI_FS_DIST            (3 << 8)
#define SPI_FLASH              (1 << 11)
#define SPI_FR_FORMAT          (1 << 12)

/* spi_ControlRegister1 */

#define SPI_CLOCK_DIV          (0xFFFF << 0)
#define SPI_DATA_WIDTH         (0x1F << 0)
#define SPI_PAD_WIDTH          (0xFF << 0)

/* spi_ControlRegister2 */

#define SPI_CHIP_ENABLE        (1 << 0)
#define SPI_TX_DATA_OUT_ENABLE (1 << 1)
#define SPI_RX_CLEAR           (1 << 2)
#define SPI_TX_CLEAR           (1 << 3)
#define SPI_CHIP_RESET         (1 << 6)
#define SPI_RX_ENABLE          (1 << 7)
#define SPI_TX_ENABLE          (1 << 8)
#define SPI_FS                 (1 << 9)
#define SPI_CHIP_SELECT        (3 << 10)

/* spi_Fifo */

#define SPI_RX_FIFO_FULL       (1 << 0)
#define SPI_TX_FIFO_NOT_FULL   (1 << 1)
#define SPI_CHIP_BUSY          (1 << 2)
#define SPI_RX_FIFO_BYTES      (0x1F << 4)
#define SPI_TX_FIFO_BYTES      (0x1F << 12)

#ifdef __cplusplus
}
#endif

#endif

#include "max7219.h"
#include <wiringPiSPI.h>

#define SPI_CHANNEL 0
#define SPI_SPEED   1000000

void max7219_send(uint8_t address, uint8_t data) {
    uint8_t buffer[2] = {address, data};
    wiringPiSPIDataRW(SPI_CHANNEL, buffer, 2);
}

void max7219_init(uint8_t decode_mode, uint8_t intensity, uint8_t scan_limit) {
    wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED);
    
    max7219_send(MAX7219_REG_SHUTDOWN, 0x01);
    max7219_send(MAX7219_REG_DISPLAYTEST, 0x00);
    max7219_send(MAX7219_REG_SCANLIMIT, scan_limit & 0x07);
    max7219_send(MAX7219_REG_DECODEMODE, decode_mode);
    max7219_set_intensity(intensity);
    max7219_clear();
}

void max7219_clear(void) {
    for (uint8_t i = MAX7219_REG_DIGIT0; i <= MAX7219_REG_DIGIT7; i++) {
        max7219_send(i, 0x00);
    }
}

void max7219_set_intensity(uint8_t intensity) {
    max7219_send(MAX7219_REG_INTENSITY, intensity & 0x0F);
}

void max7219_display_number(int num) {
    for (uint8_t i = MAX7219_REG_DIGIT0; i <= MAX7219_REG_DIGIT7; i++) {
        max7219_send(i, num % 10);
        num /= 10;
        if (num == 0) break;
    }
}

#include "DigiPot.h"

#define POT_0 0x00
#define POT_1 0x10

DigiPot::DigiPot(PinName miso, PinName mosi, PinName clk, PinName cs) {
    chsel = new DigitalOut(cs);
    spi = new SPI(mosi, miso, clk);// mosi, miso, sclk
    spi->format(8,0); // 8 bits , mode 0
    spi->frequency(1000000); // Default SPI frequency. ( 250kHz maximum for read commands).
    level = 0x00;
}

void DigiPot::increment() {
    setLevel(level++);
}

void DigiPot::decrement() {
    setLevel(level--);
}

void DigiPot::setLevel(unsigned char level) {
    *chsel = 0;
    spi->write(POT_0);
    spi->write(level);
    *chsel = 1;
    *chsel = 0;
    spi->write(POT_1);
    spi->write(level);
    *chsel = 1;
}

void DigiPot::mute() {
    setLevel(0x00);
}

void DigiPot::unmute() {
    setLevel(level);
}

unsigned char DigiPot::getLevel() {
    return level;
}
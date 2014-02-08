#include "DigiPot.h"
#include <math.h>

#define POT_0 0x00
#define POT_1 0x10
#define MAX 129.0
#define MIN 0
#define MAX_P 100
#define BASE 10.0
#define ROUND 0.5

DigiPot::DigiPot(PinName miso, PinName mosi, PinName clk, PinName cs, Mode mode) {
    chsel = new DigitalOut(cs);
    spi = new SPI(mosi, miso, clk);
    this->mode = mode;
    spi->format(8,0); 
    spi->frequency(1000000);
    level = 0x00;
    percent = 0x00;
    scale = log10(MAX);
}

void DigiPot::increment() {
    if (mode == LINEAR) {
        if (level < MAX) {
            setLevel(level++);    
        }
    } else {
        if (percent < MAX_P) {
            setLevel(round(pow(BASE, ((scale/MAX_P)*percent++))));
        }        
    }
}

void DigiPot::decrement() {
    if (mode == LINEAR) {
        if (level > MIN) {
            setLevel(level--);    
        }
    } else {
        if (percent > MIN) {
            setLevel(round(pow(BASE, ((scale/MAX_P)*percent--))));
        }
    }
}

void DigiPot::setLevel(unsigned char level) {
    *chsel = 0;
    spi->write(POT_0);
    spi->write(level);
    *chsel = 1;
    wait_us(2);
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

unsigned char DigiPot::round(double value) {
    return (unsigned char) floor(value+ROUND);    
}

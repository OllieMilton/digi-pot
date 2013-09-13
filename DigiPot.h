#ifndef DIGIPOT_H
#define DIGIPOT_H

#include <mbed.h>

class DigiPot {

    public:    
        DigiPot(PinName miso, PinName mosi, PinName clk, PinName cs);
        void increment();
        void decrement();
        void setLevel(unsigned char);
        void mute();
        void unmute();
        unsigned char getLevel();
    private:
        SPI *spi;
        DigitalOut *chsel;
        unsigned char level;
};

#endif
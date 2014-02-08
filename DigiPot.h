#ifndef DIGIPOT_H
#define DIGIPOT_H

#include <mbed.h>

enum Mode {
    LINEAR, LOGARITHMIC    
};

class DigiPot {

    public:    
        DigiPot(PinName miso, PinName mosi, PinName clk, PinName cs, Mode mode);
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
        unsigned char percent;
        Mode mode;
        double scale;
        unsigned char round(double);
};

#endif
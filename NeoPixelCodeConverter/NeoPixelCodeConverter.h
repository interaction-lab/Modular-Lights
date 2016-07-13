//  ArdcodeCreator.h - Creates code for arduino

#ifndef NEOPIXELCODECONVERTER_h
#define NEOPIXELCODECONVERTER_h

#include <iostream>
#include <fstream>
#include <vector>
#include <LightParameter.h>

using namespace std;

class NeoPixelCodeConverter{

public:
    void create(vector<LightParameter> b, int no_Leds, int no_Patterns);

    uint32_t Color(uint8_t r, uint8_t g, uint8_t b);
    uint32_t Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w);
};

#endif
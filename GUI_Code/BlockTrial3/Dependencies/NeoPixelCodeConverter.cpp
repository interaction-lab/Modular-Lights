#include "NeoPixelCodeConverter.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <Dependencies/LightParameter.h>
#include <QDebug>

/* Name:  create
Purpose:
Inputs:

*/
void NeoPixelCodeConverter::create(vector<LightParameter> a, int no_Leds, int no_Patterns)                      //function to create arduino code
{
    ofstream ofile("/home/lwathieu/Documents/GitHub/Modular-LED-HRI-/GUI_Code/BlockTrial3/testfile/testfile.ino");
    qDebug() << "Got Here!!!!!";
    ofile<<"#include <Adafruit_NeoPixel.h>\n#include <LightSignal.h>\n#include <LightParameter.h>\n\nLightSignal Strip("<<no_Leds<<", 6, NEO_RGBW + NEO_KHZ800);\n\nLightParameter Pattern["<<no_Patterns<<"];\n\nvoid setup() {\nSerial.begin(115200);\nStrip.begin();\n\n";
    for( int i = 0; i < no_Patterns; i++)
    {
        ofile<<"Pattern["<<i<<"].initialize( ";


        switch(a[i].pattern)
        {
        case 1:
            ofile<<"RAINBOW_CYCLE";
            break;
        case 2:
            ofile<<"THEATER_CHASE";
            break;
        case 3:
            ofile<<"COLOR_WIPE";
            break;
        case 4:
            ofile<<"SCANNER";
            break;
         case 5:
            ofile<<"FADE";
            break;
         case 6:
            ofile<<"BLINK";
            break;
         case 7:
            ofile<<"ON_AND_OFF";
            break;
         case 8:
            ofile<<"PULSATING";
            break;
         case 9:
            ofile<<"LOADING";
            break;
         case 10:
            ofile<<"STEP";
            break;
         default:
            ofile<<"NONE";
            break;
        }
        switch(a[i].direction)
        {
        case 0:
            ofile<<", FORWARD";
            break;
        case 1:
            ofile<<", REVERSE";
            break;
        }
        ofile<<", "<<a[i].start_time<<", ";
        ofile<<a[i].cycles<<", ";
        ofile<<a[i].index<<", ";
        ofile<<a[i].on_time<<", ";
        ofile<<a[i].off_time<<", ";
        ofile<<a[i].totalsteps<<", ";
        ofile<<a[i].brightness<<", ";
        ofile<<a[i].Color1<<", ";
        ofile<<a[i].Color2<<", ";
        ofile<<a[i].interval<<", ";
        ofile<<"(int []){";

        /*ofile<<"Pattern["<<i<<"].pattern ="<<a[i].pattern<<";\n";
        ofile<<"Pattern["<<i<<"].direction ="<<a[i].direction<<";\n";
        ofile<<"Pattern["<<i<<"].Interval ="<<a[i].Interval<<";\n";
        ofile<<"Pattern["<<i<<"].lastUpdate ="<<a[i].lastUpdate<<";\n";
        ofile<<"Pattern["<<i<<"].totalsteps ="<<a[i].totalsteps<<";\n";
        ofile<<"Pattern["<<i<<"].Color1 ="<<a[i].Color1<<";\n";
        ofile<<"Pattern["<<i<<"].Color2 ="<<a[i].Color2<<";\n";*/
        for( int j = 0; j < a[i].grouplength; j++)
        {
            ofile<<a[i].group[j]<<", ";
        }
        ofile<<"}, "<<a[i].grouplength<<");\n";
        //ofile<<"Pattern["<<i<<"].stopTime = Pattern["<<i<<"].cycles*Pattern["<<i<<"].Interval;\n\n";
    }
    ofile<<"}\n\nvoid loop() {\nfor(int i = 0; i < "<<no_Patterns<<"; i++){\n    Strip.mainLoop(&Pattern[i]);\n }\n}";

    ofile.close();
}

uint32_t NeoPixelCodeConverter::Color(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

uint32_t NeoPixelCodeConverter::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  return ((uint32_t)w << 24) | ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}


/*UpdateData NeoPixelCodeConverter::initialize(ActivePattern Pattern, Direction dir, int start, int cycle, int index, int totalsteps, int brightness, uint32_t color1, unsigned long interval, int g[],int length)              //initialization function(overloaded)
{
    UpdateData c;

    c.pattern = Pattern;
    cout<<c.pattern<<"y\n";
    c.direction = dir;
    c.startTime = start;
    c.cycles = cycle;
    c.Index = index;
    c.brightness = brightness;
    c.totalsteps = totalsteps;
    //c.status = false;
    c.complete = false;
    c.Interval = interval;
    c.Color1 = color1;
    c.Color2 = 0;
    c.lastUpdate = 0;
    c.groupLength = length;
    cout<<sizeof(g)<<"\n"<<g[3]<<"\n";
    for( int i=0; i < c.groupLength; i++)
    {
        c.group[i] = g[i];
    }


    return c;
}

UpdateData NeoPixelCodeConverter::initialize(ActivePattern Pattern, Direction dir, int start, int cycle, int index, int totalsteps, int brightness, uint32_t color1, uint32_t color2, unsigned long interval, int g[], int length)              //initialization function(overloaded)
{
    UpdateData c;

    c.pattern = Pattern;
    cout<<c.pattern;
    c.direction = dir;
    c.startTime = start;
    c.cycles = cycle;
    c.Index = index;
    c.brightness = brightness;
    c.totalsteps = totalsteps;
    //c.status = false;
    c.complete = false;
    c.Interval = interval;
    c.Color1 = color1;
    c.Color2 = color2;
    c.lastUpdate = 0;
    c.groupLength = length;
    cout<<sizeof(g)<<"\n"<<g[3]<<"\n";
    for( int i=0; i < c.groupLength; i++)
    {
        c.group[i] = g[i];
    }


    return c;
}
UpdateData NeoPixelCodeConverter::initialize(ActivePattern Pattern, Direction dir, int start, int cycle, int on, int off, int index, int totalsteps, int brightness, uint32_t color1, unsigned long interval, int g[], int length)
{
    UpdateData c;

    c.pattern = Pattern;
    cout<<c.pattern;
    c.direction = dir;
    c.startTime = start;
    c.cycles = cycle;
    c.Index = index;
    c.brightness = brightness;
    c.totalsteps = totalsteps;
    //c.status = false;
    c.complete = false;
    c.Interval = interval;
    c.Color1 = color1;
    c.Color2 = 0;
    c.lastUpdate = 0;
    c.on_time = on;
    c.off_time = off;
    c.groupLength = length;
    cout<<sizeof(g)<<"\n"<<g[3]<<"\n";
    for( int i=0; i < c.groupLength; i++)
    {
        c.group[i] = g[i];
    }


    return c;
}*/

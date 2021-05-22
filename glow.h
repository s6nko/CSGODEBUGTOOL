#pragma once

struct GlowStruct 
{
    BYTE base[4];               //0000
    float red;                  //0004
    float green;                //0008
    float blue;                 //000C
    float alpha;                //0010
    BYTE buffer[16];            //0014
    bool renderWhenOccluded;    //0024
    bool renderWhenUnOccluded;  //0025
    bool fullBloom;             //0026
    BYTE buffer1[5];            //0027
    int glowStyle;              //002C
};
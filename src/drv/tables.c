/*
    Quattro - Data tables
*/

#include "stdint.h"
#include "stddef.h"
#include "quattro.h"
#include "tables.h"

/******************************************************************************
*  ROM tables
******************************************************************************/
/*
 Notice that the order of the tables vary on some drivers, which changes the
 value of the out-of-bounds entries.

 Also Mitsubishi MCUs have little endian byte order, while Hitachi MCUs are
 big endian. In the cases where the out of bounds values are from a byte-sized
 table, the results will be different for each MCU type.

 Example of songs using out of bounds frequency values:
  xevi3dg  - song 0x8e
  dirtdash - song 0x21 (plays on sub 0x31)
  fgtlayer - song 0x1d

 Example of songs using out of bounds envelope values:
  ridgera2 - song 0x52 (voice 00 LFO depth delta)

 Examples of good test cases:
  dirtdash - song 0x03 (reg 0x04=0x30 and reg 0x80=0x02)
  pacapp   - song 0x02 (reg 0x01 selects wave number)
*/

uint16_t Q_EnvelopeRateTable[0xa0] = {
    0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0007, 0x0009, // 00
    0x000B, 0x000D, 0x000F, 0x0011, 0x0013, 0x0015, 0x0017, 0x0019,
    0x001B, 0x001D, 0x001F, 0x0022, 0x0024, 0x0027, 0x002A, 0x002D, // 10
    0x0030, 0x0033, 0x0037, 0x003B, 0x0040, 0x0044, 0x0049, 0x004F,
    0x0054, 0x005A, 0x0061, 0x0068, 0x0070, 0x0078, 0x0081, 0x008A, // 20
    0x0094, 0x009F, 0x00AA, 0x00B7, 0x00C4, 0x00D2, 0x00E1, 0x00F2,
    0x0103, 0x0116, 0x012A, 0x0140, 0x0157, 0x0170, 0x018B, 0x01AB, // 30
    0x01C7, 0x01E8, 0x020B, 0x0231, 0x025A, 0x0285, 0x02B4, 0x02E6,
    0x031C, 0x0356, 0x0394, 0x03D6, 0x041D, 0x046A, 0x04BC, 0x0514, // 40
    0x0572, 0x05D7, 0x0644, 0x06B8, 0x0735, 0x07BA, 0x084A, 0x08E4,
    0x0989, 0x0A3A, 0x0AF8, 0x0BC3, 0x0C9E, 0x0D88, 0x0E83, 0x0F91, // 50
    0x10B2, 0x11E8, 0x1334, 0x1498, 0x1617, 0x17B1, 0x1969, 0x1B40,
    0x1D3A, 0x1F59, 0x219F, 0x240F, 0x26AC, 0x297A, 0x2C7C, 0x2FB6, // 60
    0x332B, 0x36E1, 0x3ADC, 0x3F20, 0x43B4, 0x489D, 0x4DE1, 0x5386,
    0x5995, 0x6014, 0x670B, 0x6E84, 0x7687, 0x7F1F, 0x8857, 0x923A, // 70
    0x9CD4, 0xA833, 0xB465, 0xC17A, 0xCF81, 0xDE8D, 0xEEB0, 0xFFFF,

    // Out-of-bounds from C74, C75, C76
    0x0000, 0x0101, 0x0201, 0x0303, 0x0504, 0x0706, 0x0807, 0x0a09, // 80
    0x0d0b, 0x0f0e, 0x1110, 0x1412, 0x1615, 0x1918, 0x1c1a, 0x1f1d,
    0x2521, 0x2c28, 0x3430, 0x3d38, 0x4641, 0x514c, 0x5d57, 0x6a63, // 90
    0x7871, 0x8770, 0x988f, 0xaaa1, 0xbdb3, 0xd2c7, 0xe8dc, 0xfff3,

};

// taken from rom, but you can generate a similar table with:
// f(n) = 0x80*pow(1.0594631,n)+0.5
uint16_t Q_PitchTable[0x6c] = {
    0x0088, 0x0090, 0x0098, 0x00A1, 0x00AB, 0x00B5, 0x00C0, 0x00CB, // 00
    0x00D7, 0x00E4, 0x00F2, 0x0100, 0x010F, 0x011F, 0x0130, 0x0143,
    0x0156, 0x016A, 0x0180, 0x0196, 0x01AF, 0x01C8, 0x01E3, 0x0200, // 10
    0x021E, 0x023F, 0x0261, 0x0285, 0x02AB, 0x02D4, 0x02FF, 0x032D,
    0x035D, 0x0390, 0x03C7, 0x0400, 0x043D, 0x047D, 0x04C2, 0x050A, // 20
    0x0557, 0x05A8, 0x05FE, 0x0659, 0x06BA, 0x0721, 0x078D, 0x0800,
    0x087A, 0x08FB, 0x0983, 0x0A14, 0x0AAE, 0x0B50, 0x0BFD, 0x0CB3, // 30
    0x0D74, 0x0E41, 0x0F1A, 0x1000, 0x10F4, 0x11F6, 0x1307, 0x1429,
    0x155B, 0x16A1, 0x17F9, 0x1966, 0x1AE9, 0x1C82, 0x1E34, 0x2000, // 40
    0x21E7, 0x23EB, 0x260E, 0x2851, 0x2AB7, 0x2D41, 0x2FF2, 0x32CC,
    0x35D1, 0x3904, 0x3C68, 0x4000, 0x43CE, 0x47D6, 0x4C1C, 0x50A3, // 50
    0x556E, 0x5A82, 0x5FE4, 0x6598, 0x6BA2, 0x7209, 0x78D1, 0x8000,
    0x879C, 0x8FAC, 0x9837, 0xA145, 0xAADB, 0xB504, 0xBFC8, 0xCB2F, // 60
    0xD744, 0xE411, 0xF1A1, 0xFFFF
};

/*
 c76.bin > followed by lfo wave table
*/

uint16_t Q_LfoWaveTable[0xb0] = {
    0x0013, 0x2510, 0x440B, 0x5904, 0x6084, 0x598B, 0x4490, 0x2593, // 00
    0x0093, 0xDB90, 0xBC8B, 0xA784, 0xA004, 0xA70B, 0xBC10, 0xDB13,
    0x000C, 0x180C, 0x300C, 0x480C, 0x608C, 0x488C, 0x308C, 0x188C, // 10
    0x008C, 0xE88C, 0xD08C, 0xB88C, 0xA00C, 0xB80C, 0xD00C, 0xE80C,
    0x6000, 0x6000, 0x6000, 0x6000, 0x6000, 0x6000, 0x6000, 0x6000, // 20
    0xA000, 0xA000, 0xA000, 0xA000, 0xA000, 0xA000, 0xA000, 0xA000,
    0x6000, 0x6000, 0x6000, 0x6000, 0x6000, 0x6000, 0x6000, 0x6000, // 30
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0xA000, 0xA000, 0xA000, 0xA000, 0xA000, 0xA000, 0xA000, 0xA000, // 40
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0003, 0x0603, 0x0C03, 0x1203, 0x1803, 0x1E03, 0x2403, 0x2A03, // 50
    0x3003, 0x3603, 0x3C03, 0x4203, 0x4803, 0x4E03, 0x5403, 0x5A03,
    0x0083, 0xFA83, 0xF483, 0xEE83, 0xE883, 0xE283, 0xDC83, 0xD683, // 60
    0xD083, 0xCA83, 0xC483, 0xBE83, 0xB883, 0xB283, 0xAC83, 0xA683,
    0x5A83, 0x5483, 0x4E83, 0x4883, 0x4283, 0x3C83, 0x3683, 0x3083, // 70
    0x2A83, 0x2483, 0x1E83, 0x1883, 0x1283, 0x0C83, 0x0683, 0x0083,
    0xA603, 0xAC03, 0xB203, 0xB803, 0xBE03, 0xC403, 0xCA03, 0xD003, // 80
    0xD603, 0xDC03, 0xE203, 0xE803, 0xEE03, 0xF403, 0xFA03, 0x0003,
    0x6000, 0x6000, 0x0000, 0x0000, 0x6000, 0x6000, 0x0000, 0x0000, // 90
    0xA000, 0xA000, 0x0000, 0x0000, 0xA000, 0xA000, 0x0000, 0x0000,
    0x0006, 0x0C06, 0x1806, 0x2406, 0x3006, 0x3C06, 0x4806, 0x5406, // a0
    0x0086, 0xF486, 0xE886, 0xDC86, 0xD086, 0xC486, 0xB886, 0xAC86
};

uint8_t Q_PanTable[0x40] = {
    0x00, 0x00, 0x01, 0x01, 0x01, 0x02, 0x03, 0x03,
    0x04, 0x05, 0x06, 0x07, 0x07, 0x08, 0x09, 0x0A,
    0x0B, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x14, // 10
    0x15, 0x16, 0x18, 0x19, 0x1A, 0x1C, 0x1D, 0x1F,
    0x21, 0x25, 0x28, 0x2C, 0x30, 0x34, 0x38, 0x3D, // 20
    0x41, 0x46, 0x4C, 0x51, 0x57, 0x5D, 0x63, 0x6A,
    0x71, 0x78, 0x80, 0x87, 0x8F, 0x98, 0xA1, 0xAA, // 30
    0xB3, 0xBD, 0xC7, 0xD2, 0xDC, 0xE8, 0xF3, 0xFF
};

uint8_t Q_VolumeTable[0x100] = {
    0xFF, 0xFB, 0xF6, 0xF0, 0xEB, 0xE7, 0xE2, 0xDD,
    0xD9, 0xD4, 0xD0, 0xCB, 0xC7, 0xC3, 0xBF, 0xBB,
    0xB7, 0xB3, 0xB0, 0xAC, 0xA8, 0xA5, 0xA2, 0x9E, // 10
    0x9B, 0x98, 0x95, 0x91, 0x8E, 0x8C, 0x89, 0x86,
    0x83, 0x80, 0x7E, 0x7B, 0x78, 0x76, 0x74, 0x71, // 20
    0x6F, 0x6D, 0x6A, 0x68, 0x66, 0x64, 0x62, 0x60,
    0x5E, 0x5C, 0x5A, 0x58, 0x56, 0x54, 0x53, 0x51, // 30
    0x4F, 0x4E, 0x4C, 0x4A, 0x49, 0x47, 0x46, 0x44,
    0x43, 0x42, 0x40, 0x3F, 0x3E, 0x3C, 0x3B, 0x3A, // 40
    0x39, 0x38, 0x36, 0x35, 0x34, 0x33, 0x32, 0x31,
    0x30, 0x2F, 0x2E, 0x2D, 0x2C, 0x2B, 0x2A, 0x29, // 50
    0x29, 0x28, 0x27, 0x26, 0x25, 0x25, 0x24, 0x23,
    0x22, 0x22, 0x21, 0x20, 0x20, 0x1F, 0x1E, 0x1E, // 60
    0x1D, 0x1C, 0x1C, 0x1B, 0x1B, 0x1A, 0x1A, 0x19,
    0x19, 0x18, 0x18, 0x17, 0x17, 0x16, 0x16, 0x15, // 70
    0x15, 0x14, 0x14, 0x14, 0x13, 0x13, 0x12, 0x12,
    0x12, 0x11, 0x11, 0x10, 0x10, 0x10, 0x0F, 0x0F, // 80
    0x0F, 0x0F, 0x0E, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D,
    0x0D, 0x0C, 0x0C, 0x0C, 0x0C, 0x0B, 0x0B, 0x0B, // 90
    0x0B, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x09, 0x09,
    0x09, 0x09, 0x09, 0x08, 0x08, 0x08, 0x08, 0x08, // a0
    0x08, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
    0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, // b0
    0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
    0x05, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, // c0
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, // d0
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, // e0
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, // f0
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00
};

/******************************************************************************
*  Helper tables (These aren't found in the original code)
* Maps of the members of the track and channel structs to be used
* in the track command parser.
******************************************************************************/

// These can be redefined for big endian.

// always big endian
#define MAP_WORDB(struct,member)  offsetof(struct,member)+1,offsetof(struct,member)
// always little endian
#define MAP_WORDL(struct,member)  offsetof(struct,member),offsetof(struct,member)+1

#define MAP_BYTE(struct,member)  offsetof(struct,member)
#define MAP_WORD(struct,member)  offsetof(struct,member),offsetof(struct,member)+1
#define MAP_UPPER(struct,member)  offsetof(struct,member)+1
#define MAP_LOWER(struct,member)  offsetof(struct,member)


// #define MAP_POSI(struct,member)  offsetof(struct,member),offsetof(struct,member)+1,offsetof(struct,member)+2

// we dummy out pointer writes since we dont want to give the track too much control...
uint8_t Q_TrackStructMap[0x22] = {
/* 00 */ MAP_WORDB(Q_Track,UpdateTime), // These 3 could also be dummied
/* 02 */ MAP_WORD(Q_Track,Unused1), // pointers
/* 04 */ MAP_WORD(Q_Track,Unused1),

/* 06 */ MAP_LOWER(Q_Track,TrackVolume),
/* 07 */ MAP_BYTE(Q_Track,BaseTempo),

/* 08 */ MAP_BYTE(Q_Track,TempoFraction),
/* 09 */ MAP_BYTE(Q_Track,Tempo),
/* 0a */ MAP_WORDB(Q_Track,Flags),
/* 0c */ MAP_BYTE(Q_Track,TempoMulFactor),
/* 0d */ MAP_BYTE(Q_Track,TempoMode),
/* 0e */ MAP_WORD(Q_Track,Unused1),

/* 10 */ MAP_WORD(Q_Track,Unused1), // Track position pointer
/* 12 */ MAP_BYTE(Q_Track,Unused1), // Track bank position

/* 13 */ MAP_BYTE(Q_Track,KeyOnBuffer),
/* 14 */ MAP_BYTE(Q_Track,SubStackPos),
/* 15 */ MAP_BYTE(Q_Track,RepeatStackPos),
/* 16 */ MAP_BYTE(Q_Track,LoopStackPos),
/* 17 */ MAP_BYTE(Q_Track,SkipTrack),

/* 18 */ MAP_WORD(Q_Track,Fadeout),
/* 1a */ MAP_BYTE(Q_Track,RestCount),
/* 1b */ MAP_BYTE(Q_Track,TempoReg),
/* 1c */ MAP_WORD(Q_Track,Unused1), // don't let the track mess with pointers....
/* 1e */ MAP_WORD(Q_Track,Unused1),
/* 20 */ MAP_WORDB(Q_Track,GlobalVolume),
/* 21 */ //MAP_BYTE(Q_Track,Unused2)
};

uint8_t Q_ChannelStructMap[0x20] =
{
/* 00 */ MAP_WORDB(Q_Channel,WaveNo),
/* 02 */ MAP_BYTE(Q_Channel,Volume),
/* 03 */ MAP_BYTE(Q_Channel,Pan),
/* 04 */ MAP_BYTE(Q_Channel,Detune),
/* 05 */ MAP_BYTE(Q_Channel,BaseNote),
/* 06 */ MAP_LOWER(Q_Channel,EnvNo),
/* 07 */ MAP_LOWER(Q_Channel,PitchEnvNo),
/* 08 */ MAP_BYTE(Q_Channel,NoteDelay),
/* 09 */ MAP_BYTE(Q_Channel,GateTime),
/* 0a */ MAP_BYTE(Q_Channel,SampleOffset),
/* 0b */ MAP_BYTE(Q_Channel,Transpose),
/* 0c */ MAP_BYTE(Q_Channel,LfoNo),
/* 0d */ MAP_BYTE(Q_Channel,Portamento),
/* 0e */ MAP_BYTE(Q_Channel,PanMode),
/* 0f */ MAP_BYTE(Q_Channel,PitchReg),

/* 10 */ MAP_BYTE(Q_Channel,PresetMap),
/* 11 */ MAP_BYTE(Q_Channel,VoiceNo),
/* 12 */ MAP_BYTE(Q_Channel,Legato),
/* 13 */ MAP_BYTE(Q_Channel,Enabled),
/* 14 */ MAP_BYTE(Q_Channel,ChannelLink),
/* 15 */ MAP_BYTE(Q_Channel,Preset),
/* 16 */ MAP_WORD(Q_Channel,Unused), // voice pointer
/* 18 */ MAP_WORD(Q_Channel,Unused), // source pointer
/* 1a */ MAP_BYTE(Q_Channel,KeyOnNote),
/* 1b */ MAP_BYTE(Q_Channel,KeyOnFlag),
/* 1c */ MAP_BYTE(Q_Channel,VolumeReg),
/* 1d */ MAP_BYTE(Q_Channel,CutoffMode),
/* 1e */ MAP_UPPER(Q_Channel,EnvNo),
/* 1f */ MAP_UPPER(Q_Channel,PitchEnvNo),
};
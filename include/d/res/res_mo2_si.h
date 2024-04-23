#ifndef RES_MO2_SI_H
#define RES_MO2_SI_H

#include "global.h"

enum MO2_SI_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    MO2_SI_BCK_AHAZUSHI=0x7,
    MO2_SI_BCK_AHAZUSHI01=0x8,
    MO2_SI_BCK_AHAZUSHI02=0x9,
    MO2_SI_BCK_AHAZUSHI03=0xA,
    MO2_SI_BCK_AKAITEN=0xB,
    MO2_SI_BCK_AKAITEN01=0xC,
    MO2_SI_BCK_AKAITEN02=0xD,
    MO2_SI_BCK_AKAITEN03=0xE,
    MO2_SI_BCK_ATATE=0xF,
    MO2_SI_BCK_ATATE01=0x10,
    MO2_SI_BCK_ATATE02=0x11,
    MO2_SI_BCK_ATATE03=0x12,
    MO2_SI_BCK_ATSUKI=0x13,
    MO2_SI_BCK_ATSUKI01=0x14,
    MO2_SI_BCK_ATSUKI02=0x15,
    MO2_SI_BCK_ATSUKI03=0x16,
    MO2_SI_BCK_AWATEDEMO=0x17,
    MO2_SI_BCK_BWAIT=0x18,
    MO2_SI_BCK_BWALKFB=0x19,
    MO2_SI_BCK_BWALKLR=0x1A,
    MO2_SI_BCK_DEFAULT=0x1B,
    MO2_SI_BCK_GAKEDEMO=0x1C,
    MO2_SI_BCK_HIPDMG01=0x1D,
    MO2_SI_BCK_HIPDMG02=0x1E,
    MO2_SI_BCK_JEND=0x1F,
    MO2_SI_BCK_JSTART=0x20,
    MO2_SI_BCK_KKEIKAI=0x21,
    MO2_SI_BCK_KOKERUB=0x22,
    MO2_SI_BCK_KOKERUF=0x23,
    MO2_SI_BCK_KWAIT=0x24,
    MO2_SI_BCK_KWALK=0x25,
    MO2_SI_BCK_LF=0x26,
    MO2_SI_BCK_MO_KANTERA=0x27,
    MO2_SI_BCK_NABIGPUNCH=0x28,
    MO2_SI_BCK_NABIGPUNCH01=0x29,
    MO2_SI_BCK_NABIGPUNCH02=0x2A,
    MO2_SI_BCK_NABIGPUNCH03=0x2B,
    MO2_SI_BCK_NAJAB=0x2C,
    MO2_SI_BCK_NBWAIT=0x2D,
    MO2_SI_BCK_NBWALKFB=0x2E,
    MO2_SI_BCK_NBWALKLR=0x2F,
    MO2_SI_BCK_NWALK=0x30,
    MO2_SI_BCK_OKIRUA=0x31,
    MO2_SI_BCK_OKIRUU=0x32,
    MO2_SI_BCK_PAOMUKE=0x33,
    MO2_SI_BCK_PUTSUBUSE=0x34,
    MO2_SI_BCK_RUNDEMO01=0x35,
    MO2_SI_BCK_RUNDEMO02=0x36,
    MO2_SI_BCK_SCATCH=0x37,
    MO2_SI_BCK_SHAKKEN=0x38,
    MO2_SI_BCK_SKYORO=0x39,
    MO2_SI_BCK_SLIPDEMO=0x3A,
    MO2_SI_BCK_SWALK=0x3B,
    MO2_SI_BCK_TACKLEDEMO=0x3C,
    MO2_SI_BCK_TALK=0x3D,
    MO2_SI_BCK_UKYADEMO=0x3E,
    MO2_SI_BCK_WAIT=0x3F,
    MO2_SI_BCK_WAITDEMO=0x40,
    MO2_SI_BCK_WALK=0x41,
    MO2_SI_BCK_YOROKEB=0x42,
    MO2_SI_BCK_YOROKEF=0x43,
    
    /* BMD */
    MO2_SI_BMD_CULL=0x46,
    MO2_SI_BMD_CULLMORE=0x47,
    MO2_SI_BMD_GA=0x48,
    MO2_SI_BMD_HOP=0x49,
    MO2_SI_BMD_KBA=0x4A,
    MO2_SI_BMD_KBB=0x4B,
    MO2_SI_BMD_KBC=0x4C,
    MO2_SI_BMD_KBD=0x4D,
    MO2_SI_BMD_KBE=0x4E,
    MO2_SI_BMD_LF=0x4F,
    MO2_SI_BMD_MK_KANTERANEW=0x50,
    MO2_SI_BMD_MO=0x51,
    MO2_SI_BMD_MOHIMO=0x52,
    MO2_SI_BMD_MOS=0x53,
    MO2_SI_BMD_MOYARI=0x54,
    MO2_SI_BMD_MO_FIRE=0x55,
    MO2_SI_BMD_MO_FIRE02=0x56,
    MO2_SI_BMD_MO_KANTERA=0x57,
    MO2_SI_BMD_PL=0x58,
    MO2_SI_BMD_SEARCHCORN=0x59,
    MO2_SI_BMD_SEARCHCUBE=0x5A,
    MO2_SI_BMD_SEARCHITA=0x5B,
    
    /* BRK */
    MO2_SI_BRK_LF=0x5E,
    MO2_SI_BRK_MK_KANTERANEW=0x5F,
    MO2_SI_BRK_MO_FIRE=0x60,
    MO2_SI_BRK_MO_FIRE02=0x61,
    MO2_SI_BRK_MO_KANTERA=0x62,
    MO2_SI_BRK_PL=0x63,
    
    /* BTP */
    MO2_SI_BTP_TCLOSE=0x66,
    MO2_SI_BTP_TDAMAGE=0x67,
    MO2_SI_BTP_THAKKEN=0x68,
    MO2_SI_BTP_TKOUGEKI=0x69,
    MO2_SI_BTP_TMABATAKI=0x6A,
    MO2_SI_BTP_TMIHIRAKI=0x6B,
    MO2_SI_BTP_TOPEN=0x6C,
    
    /* MSG */
    MO2_SI_BIN_ZEL_M100003=0x6F,
    MO2_SI_BIN_ZL00020=0x70,
};

#endif /* RES_MO2_SI_H */

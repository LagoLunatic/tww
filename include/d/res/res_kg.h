#ifndef RES_KG_H
#define RES_KG_H

#include "global.h"

enum KG_RES_FILE_ID {
    /* BDLM */
    KG_BDL_KG=0x0,
    KG_BDL_KG_PLATE=0x3,
    
    /* BTP */
    KG_BTP_KG=0x1,
    KG_BTP_KG_PLATE=0x4,
    KG_BTP_MOPEN=0x5,
    KG_BTP_RADIO=0x6,
    KG_BTP_WARAI=0x7,
    KG_BTP_SLEEP=0x14,
    
    /* BCKS */
    KG_BCK_KG_WAIT01=0x2,
    KG_BCK_KG_CAPTAIN=0x8,
    KG_BCK_KG_CAPTAIN02=0x9,
    KG_BCK_KG_KAMAE=0xA,
    KG_BCK_KG_KIDS=0xB,
    KG_BCK_KG_KWAIT=0xC,
    KG_BCK_KG_RADIO=0xD,
    KG_BCK_KG_SASIKAE=0xE,
    KG_BCK_KG_TALK01=0xF,
    KG_BCK_KG_WAIT02=0x10,
    KG_BCK_KG_GONZO=0x11,
    KG_BCK_KG_TETORA=0x12,
    KG_BCK_KG_TETORA02=0x13,
};

enum KG_RES_FILE_INDEX {
    /* BDLM */
    KG_INDEX_BDL_KG=0x5,
    KG_INDEX_BDL_KG_PLATE=0x6,
    
    /* BTP */
    KG_INDEX_BTP_KG=0x9,
    KG_INDEX_BTP_KG_PLATE=0xA,
    KG_INDEX_BTP_MOPEN=0xB,
    KG_INDEX_BTP_RADIO=0xC,
    KG_INDEX_BTP_WARAI=0xD,
    KG_INDEX_BTP_SLEEP=0xE,
    
    /* BCKS */
    KG_INDEX_BCK_KG_WAIT01=0x11,
    KG_INDEX_BCK_KG_CAPTAIN=0x12,
    KG_INDEX_BCK_KG_CAPTAIN02=0x13,
    KG_INDEX_BCK_KG_KAMAE=0x14,
    KG_INDEX_BCK_KG_KIDS=0x15,
    KG_INDEX_BCK_KG_KWAIT=0x16,
    KG_INDEX_BCK_KG_RADIO=0x17,
    KG_INDEX_BCK_KG_SASIKAE=0x18,
    KG_INDEX_BCK_KG_TALK01=0x19,
    KG_INDEX_BCK_KG_WAIT02=0x1A,
    KG_INDEX_BCK_KG_GONZO=0x1B,
    KG_INDEX_BCK_KG_TETORA=0x1C,
    KG_INDEX_BCK_KG_TETORA02=0x1D,
};

#endif /* RES_KG_H */

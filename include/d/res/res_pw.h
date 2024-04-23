#ifndef RES_PW_H
#define RES_PW_H

#include "global.h"

enum PW_RES_FILE_ID { // IDs and indexes are synced
    /* BAS */
    PW_BAS_ATTACK1=0x7,
    PW_BAS_NIGERU1=0x8,
    
    /* BCK */
    PW_BCK_ANSIN1=0xB,
    PW_BCK_ATTACK1=0xC,
    PW_BCK_BUNRETU1=0xD,
    PW_BCK_DAMAGE1=0xE,
    PW_BCK_DAMAGE_K1=0xF,
    PW_BCK_DERUA1=0x10,
    PW_BCK_DERUB1=0x11,
    PW_BCK_DERUB2=0x12,
    PW_BCK_DOKI1=0x13,
    PW_BCK_IDOU1=0x14,
    PW_BCK_IDOU2=0x15,
    PW_BCK_IKIGIRE1=0x16,
    PW_BCK_JITTAIKA1=0x17,
    PW_BCK_KIDUKU1=0x18,
    PW_BCK_KIDUKU2=0x19,
    PW_BCK_KIZETU1=0x1A,
    PW_BCK_NIGERU1=0x1B,
    PW_BCK_PRESS1=0x1C,
    PW_BCK_SIRIMOTI1=0x1D,
    PW_BCK_SYOUTEN1=0x1E,
    PW_BCK_TORITUKI1=0x1F,
    PW_BCK_TORITUKI2=0x20,
    PW_BCK_TORITUKI3=0x21,
    PW_BCK_TORITUKI_WAIT1=0x22,
    PW_BCK_WAIT1=0x23,
    PW_BCK_WAIT2=0x24,
    
    /* BDLM */
    PW_BDL_PW=0x27,
    
    /* BRK */
    PW_BRK_DEFAULT=0x2A,
    PW_BRK_HIT=0x2B,
    PW_BRK_JITTAIKA1=0x2C,
    
    /* BTP */
    PW_BTP_IROGAE1=0x2F,
};

#endif /* RES_PW_H */

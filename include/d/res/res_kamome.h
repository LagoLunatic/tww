#ifndef RES_KAMOME_H
#define RES_KAMOME_H

#include "global.h"

enum KAMOME_RES_FILE_ID { // IDs and indexes are synced
    /* BAS */
    KAMOME_BAS_KA_FLY1=0x5,
    KAMOME_BAS_KA_LAND1=0x6,
    KAMOME_BAS_KA_MOVE1=0x7,
    KAMOME_BAS_KA_WAIT1=0x8,
    KAMOME_BAS_KA_WAIT2=0x9,
    
    /* BCK */
    KAMOME_BCK_KA_EAT1=0xC,
    KAMOME_BCK_KA_FLY1=0xD,
    KAMOME_BCK_KA_LAND1=0xE,
    KAMOME_BCK_KA_MOVE1=0xF,
    KAMOME_BCK_KA_SING1=0x10,
    KAMOME_BCK_KA_SING2=0x11,
    KAMOME_BCK_KA_WAIT1=0x12,
    KAMOME_BCK_KA_WAIT2=0x13,
    KAMOME_BCK_KA_WAIT3=0x14,
    
    /* BDL */
    KAMOME_BDL_KA=0x17,
    KAMOME_BDL_KA_HYOI=0x18,
};

#endif /* RES_KAMOME_H */

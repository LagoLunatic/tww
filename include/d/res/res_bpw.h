#ifndef RES_BPW_H
#define RES_BPW_H

#include "global.h"

enum BPW_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    BPW_BCK_ATTACK_KAN1=0x5,
    BPW_BCK_BOYON_L1=0x6,
    BPW_BCK_BOYON_S1=0x7,
    BPW_BCK_CORE1=0x8,
    BPW_BCK_CORE_NIGE1=0x9,
    BPW_BCK_DAMAGE1=0xA,
    BPW_BCK_DOSUN1=0xB,
    BPW_BCK_DOSUN_WAIT1=0xC,
    BPW_BCK_DOSUN_WAIT11=0xD,
    BPW_BCK_GATAGATA1=0xE,
    BPW_BCK_HIROU1=0xF,
    BPW_BCK_HIT1=0x10,
    BPW_BCK_HONOO1=0x11,
    BPW_BCK_HONOO_END1=0x12,
    BPW_BCK_HONOO_WAIT1=0x13,
    BPW_BCK_HUKKATU1=0x14,
    BPW_BCK_IKI1=0x15,
    BPW_BCK_IKI_END1=0x16,
    BPW_BCK_IKI_WAIT1=0x17,
    BPW_BCK_JITA1=0x18,
    BPW_BCK_JUMP1=0x19,
    BPW_BCK_KAN_DEFAULT1=0x1A,
    BPW_BCK_KYORO_GARN1=0x1B,
    BPW_BCK_MOVEB1=0x1C,
    BPW_BCK_MOVEF1=0x1D,
    BPW_BCK_MOVES1=0x1E,
    BPW_BCK_OPENING1=0x1F,
    BPW_BCK_OPENING2=0x20,
    BPW_BCK_OPENING_KAN1=0x21,
    BPW_BCK_OPENING_KAN2=0x22,
    BPW_BCK_PRESS1=0x23,
    BPW_BCK_SONOBA_PRESS1=0x24,
    BPW_BCK_SONOBA_PRESS2=0x25,
    BPW_BCK_SUIKOMU1=0x26,
    BPW_BCK_TAMA1=0x27,
    BPW_BCK_TAME1=0x28,
    BPW_BCK_TORITUKI1=0x29,
    BPW_BCK_WAIT1=0x2A,
    BPW_BCK_WARAU1=0x2B,
    
    /* BDLM */
    BPW_BDL_BPW=0x2E,
    BPW_BDL_BPW_KAN1=0x2F,
    
    /* BRK */
    BPW_BRK_BPW_KAN1=0x32,
    BPW_BRK_DEFAULT=0x33,
    BPW_BRK_HIRARU1=0x34,
    BPW_BRK_HIT=0x35,
    BPW_BRK_NOROI_E1=0x36,
    BPW_BRK_NOROI_S1=0x37,
};

#endif /* RES_BPW_H */

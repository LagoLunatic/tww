#ifndef RES_BTSW_H
#define RES_BTSW_H

#include "global.h"

enum BTSW_RES_FILE_ID {
    /* BCKS */
    BTSW_BCK_BN_KASIGE=0xF,
    BTSW_BCK_BN_ONEGAI=0x10,
    BTSW_BCK_BN_SIWAKE01=0x11,
    BTSW_BCK_BN_SIWAKE02=0x12,
    BTSW_BCK_BN_SUGOI=0x13,
    BTSW_BCK_BN_TALK01=0x14,
    BTSW_BCK_BN_TALK02=0x15,
    BTSW_BCK_BN_WAIT01=0x16,
    BTSW_BCK_BN_WAIT02=0x17,
    BTSW_BCK_BN_WALK=0x18,
    
    /* BDL */
    BTSW_BDL_BN_KABAN=0xC,
    BTSW_BDL_BM_LETTER=0x19,
    BTSW_BDL_BN_TIRASI=0x1A,
    
    /* BDLM */
    BTSW_BDL_QMAIL=0x4,
    BTSW_BDL_BN=0xD,
    
    /* BMDM */
    BTSW_BMD_SHOP_CURSOR01=0x5,
    
    /* BRK */
    BTSW_BRK_SHOP_CURSOR01=0x8,
    
    /* BTP */
    BTSW_BTP_QMAIL=0xA,
    BTSW_BTP_BN_MABA=0xE,
};

enum BTSW_RES_FILE_INDEX {
    /* BCKS */
    BTSW_INDEX_BCK_BN_KASIGE=0x8,
    BTSW_INDEX_BCK_BN_ONEGAI=0x9,
    BTSW_INDEX_BCK_BN_SIWAKE01=0xA,
    BTSW_INDEX_BCK_BN_SIWAKE02=0xB,
    BTSW_INDEX_BCK_BN_SUGOI=0xC,
    BTSW_INDEX_BCK_BN_TALK01=0xD,
    BTSW_INDEX_BCK_BN_TALK02=0xE,
    BTSW_INDEX_BCK_BN_WAIT01=0xF,
    BTSW_INDEX_BCK_BN_WAIT02=0x10,
    BTSW_INDEX_BCK_BN_WALK=0x11,
    
    /* BDL */
    BTSW_INDEX_BDL_BN_KABAN=0x14,
    BTSW_INDEX_BDL_BM_LETTER=0x15,
    BTSW_INDEX_BDL_BN_TIRASI=0x16,
    
    /* BDLM */
    BTSW_INDEX_BDL_QMAIL=0x19,
    BTSW_INDEX_BDL_BN=0x1A,
    
    /* BMDM */
    BTSW_INDEX_BMD_SHOP_CURSOR01=0x1D,
    
    /* BRK */
    BTSW_INDEX_BRK_SHOP_CURSOR01=0x20,
    
    /* BTP */
    BTSW_INDEX_BTP_QMAIL=0x23,
    BTSW_INDEX_BTP_BN_MABA=0x24,
};

#endif /* RES_BTSW_H */

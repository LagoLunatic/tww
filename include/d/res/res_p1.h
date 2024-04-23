#ifndef RES_P1_H
#define RES_P1_H

#include "global.h"

enum P1_RES_FILE_ID {
    /* BMT */
    P1_BMT_P1B_BODY=0xA,
    P1_BMT_P1C_BODY=0x28,
    
    /* BTP */
    P1_BTP_MABA_A=0xB,
    P1_BTP_MABA_B=0xC,
    P1_BTP_MABA_C=0x29,
    P1_BTP_P1A_DUMMY_TEX_ALL=0x46,
    
    /* BDL */
    P1_BDL_P1=0x31,
    P1_BDL_DORA_STICK=0x35,
    
    /* BDLM */
    P1_BDL_P1A_HEAD=0x32,
    P1_BDL_P1B_HEAD=0x33,
    P1_BDL_P1C_HEAD=0x34,
    
    /* BCKS */
    P1_BCK_ANGRY=0x4D,
    P1_BCK_C_STOP=0x50,
    P1_BCK_C_TALK01=0x51,
    P1_BCK_C_TALK02=0x52,
    P1_BCK_C_WAIT=0x53,
    P1_BCK_CHECK01=0x54,
    P1_BCK_CHECK02=0x55,
    P1_BCK_LOOK=0x57,
    P1_BCK_OMOKJ=0x58,
    P1_BCK_TALK=0x59,
    P1_BCK_TALK02=0x5A,
    P1_BCK_TALK03=0x5B,
    P1_BCK_TALK04=0x5C,
    P1_BCK_TORIKJ=0x5D,
    P1_BCK_WAIT=0x5E,
    P1_BCK_WAIT02=0x5F,
};

enum P1_RES_FILE_INDEX {
    /* BMT */
    P1_INDEX_BMT_P1B_BODY=0x7,
    P1_INDEX_BMT_P1C_BODY=0x8,
    
    /* BTP */
    P1_INDEX_BTP_MABA_A=0xB,
    P1_INDEX_BTP_MABA_B=0xC,
    P1_INDEX_BTP_MABA_C=0xD,
    P1_INDEX_BTP_P1A_DUMMY_TEX_ALL=0xE,
    
    /* BDL */
    P1_INDEX_BDL_P1=0x11,
    P1_INDEX_BDL_DORA_STICK=0x12,
    
    /* BDLM */
    P1_INDEX_BDL_P1A_HEAD=0x15,
    P1_INDEX_BDL_P1B_HEAD=0x16,
    P1_INDEX_BDL_P1C_HEAD=0x17,
    
    /* BCKS */
    P1_INDEX_BCK_ANGRY=0x1A,
    P1_INDEX_BCK_C_STOP=0x1B,
    P1_INDEX_BCK_C_TALK01=0x1C,
    P1_INDEX_BCK_C_TALK02=0x1D,
    P1_INDEX_BCK_C_WAIT=0x1E,
    P1_INDEX_BCK_CHECK01=0x1F,
    P1_INDEX_BCK_CHECK02=0x20,
    P1_INDEX_BCK_LOOK=0x21,
    P1_INDEX_BCK_OMOKJ=0x22,
    P1_INDEX_BCK_TALK=0x23,
    P1_INDEX_BCK_TALK02=0x24,
    P1_INDEX_BCK_TALK03=0x25,
    P1_INDEX_BCK_TALK04=0x26,
    P1_INDEX_BCK_TORIKJ=0x27,
    P1_INDEX_BCK_WAIT=0x28,
    P1_INDEX_BCK_WAIT02=0x29,
};

#endif /* RES_P1_H */

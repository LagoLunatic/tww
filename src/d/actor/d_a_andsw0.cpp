//
// Generated by dtk
// Translation Unit: d_a_andsw0.cpp
//

#include "d/actor/d_a_andsw0.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/actor/d_a_bk.h"
#include "d/actor/d_a_bb.h"

enum {
    ACT_ON_ALL = 0,
    ACT_OFF_ALL,
    ACT_WAIT = 10,
    ACT_TIMER = 20,
    ACT_TIMER2,
    ACT_TIMER_SET = 30,
};

/* 00000078-00000080       .text daAndsw0_Draw__FP12andsw0_class */
static s32 daAndsw0_Draw(andsw0_class*) {
    return 1;
}

/* 00000080-000003C4       .text daAndsw0_check__FP12andsw0_class */
static void daAndsw0_check(andsw0_class* i_this) {
    s32 numToCheck = i_this->mNumSwitchesToCheck;
    u32 switchToCheck;
    if (i_this->mFirstSwitchToCheck) {
        switchToCheck = i_this->mFirstSwitchToCheck;
    } else {
        switchToCheck = i_this->mSwitchToSet + 1;
    }

    switch(i_this->mAction) {
        case ACT_ON_ALL:
            for(int i = 0; i < numToCheck; i++) {
                if(dComIfGs_isSwitch(switchToCheck, fopAcM_GetRoomNo(i_this)) == false) {
                    break;
                }

                if(i == numToCheck - 1) {
                    if(i_this->mBehaviorType != 3) {
                        dComIfGs_onSwitch(i_this->mSwitchToSet, fopAcM_GetRoomNo(i_this));
                    }

                    switch(i_this->mBehaviorType) {
                        case 0:
                            i_this->mAction = ACT_WAIT;
                            break;
                        case 3:
                            i_this->mAction = ACT_TIMER_SET;
                            i_this->mTimer = 65;
                            break;
                        default:
                            i_this->mAction = ACT_OFF_ALL;
                            break;
                    }
                }

                switchToCheck += 1;
            }

            break;
        case ACT_OFF_ALL: {
            u32 switchToCheck2 = i_this->mFirstSwitchToCheck ? i_this->mFirstSwitchToCheck : i_this->mSwitchToSet + 1;

            for(int i = 0; i < numToCheck; i++) {
                if(dComIfGs_isSwitch(switchToCheck2, fopAcM_GetRoomNo(i_this)) == false) {
                    dComIfGs_offSwitch(i_this->mSwitchToSet, fopAcM_GetRoomNo(i_this));
                    i_this->mAction  = ACT_ON_ALL;
                    break;
                }
                
                switchToCheck2 += 1;
            }

            break;
        }
        case ACT_TIMER:
            i_this->mTimer = (i_this->home.angle.z & 0xFF) * 15;
            if(fopAcM_isSwitch(i_this, i_this->mSwitchToSet)) {
                i_this->mAction = ACT_WAIT;
            }
            else {
                for(int i = 0; i < numToCheck; i++) {
                    if(fopAcM_isSwitch(i_this, switchToCheck)) {
                        i_this->mAction += 1;
                        break;
                    }
                    
                    switchToCheck += 1;
                }
            }

            break;
        case ACT_TIMER2:
            i_this->mTimer -= 1;
            if(i_this->mTimer == 0) {
                for(int i = 0; i < numToCheck; i++) {
                    fopAcM_offSwitch(i_this, switchToCheck);
                    switchToCheck += 1;
                }
                
                i_this->mAction = ACT_TIMER;
            }
            else {
                switchToCheck = i_this->mFirstSwitchToCheck ? i_this->mFirstSwitchToCheck : i_this->mSwitchToSet + 1;

                for(int i = 0; i < numToCheck; i++) {
                    if(fopAcM_isSwitch(i_this, switchToCheck) == false) {
                        break;
                    }

                    if(i == numToCheck - 1) {
                        fopAcM_onSwitch(i_this, i_this->mSwitchToSet);
                        i_this->mAction = ACT_WAIT;
                    }
                    
                    switchToCheck += 1;
                }
            }

            break;
        case ACT_TIMER_SET:
            i_this->mTimer -= 1;
            if(i_this->mTimer == 0) {
                fopAcM_onSwitch(i_this, i_this->mSwitchToSet);
                i_this->mAction = ACT_WAIT;
            }

            break;
        case ACT_WAIT:
        default:
            break;
    }
}

static void* ac[7];
static s32 check_count;

/* 000003C4-0000044C       .text bk_s_sub1__FPvPv */
static void* bk_s_sub1(void* i_this, void*) {
    if(fopAcM_IsActor(i_this) && fopAcM_GetName(i_this) == PROC_BK && (fopAcM_GetParam(i_this) & 0xF) == 7)  {
        s32 count = check_count; //regswaps without this
        if(count < 2) {
            ac[check_count] = i_this;
            check_count++;
        }

        return 0;
    }

    return 0;
}

/* 0000044C-000004D4       .text bk_s_sub2__FPvPv */
static void* bk_s_sub2(void* i_this, void*) {
    if(fopAcM_IsActor(i_this) && fopAcM_GetName(i_this) == PROC_BK && (fopAcM_GetParam(i_this) & 0xF) == 4)  {
        s32 count = check_count; //regswaps without this
        if(count == 2) {
            ac[check_count] = i_this;
            check_count++;
        }

        return 0;
    }

    return 0;
}

/* 000004D4-0000055C       .text bk_s_sub3__FPvPv */
static void* bk_s_sub3(void* i_this, void*) {
    if(fopAcM_IsActor(i_this) && fopAcM_GetName(i_this) == PROC_BK && (fopAcM_GetParam(i_this) & 0xF) == 5)  {
        s32 count = check_count; //regswaps without this
        if(count < 5) {
            ac[check_count] = i_this;
            check_count++;
        }

        return 0;
    }

    return 0;
}

/* 0000055C-000005D4       .text bb_s_sub__FPvPv */
static void* bb_s_sub(void* search, void*) {
    if(fopAcM_IsActor(search) && fopAcM_GetName(search) == PROC_BB)  {
        s32 count = check_count; //regswaps without this
        if(count < 7) {
            ac[check_count] = search;
            check_count++;
        }

        return 0;
    }

    return 0;
}

/* 000005D4-000006AC       .text hajimari_actor_entry__FP12andsw0_class */
static s32 hajimari_actor_entry(andsw0_class* i_this) {
    for(int i = 0; i < 7; i++) {
        ac[i] = 0;
    }
    check_count = 0;

    fpcM_Search(&bk_s_sub1, i_this);
    fpcM_Search(&bk_s_sub2, i_this);
    fpcM_Search(&bk_s_sub3, i_this);
    check_count = 5;
    fpcM_Search(&bb_s_sub, i_this);

    for(int i = 0; i < 7; i++) {
        if(ac[i] == 0) {
            return 0;
        }
    }

    return 1;
}

/* 000006AC-0000081C       .text hajimarinomori_check__FP12andsw0_class */
static void hajimarinomori_check(andsw0_class* i_this) {
    fopAc_ac_c* actor = i_this;
    if (i_this->mBehaviorType == 0) {
        if (hajimari_actor_entry(i_this)) {
            i_this->mBehaviorType = 1;
        }
    }
    else {
        for(int i = 0; i < 7; i++) {}

        if (dComIfGs_isEventBit(4)) {
            bb_class* kargaroc = (bb_class*)ac[5];
            fopAcM_delete(kargaroc);
            kargaroc = (bb_class*)ac[6];
            fopAcM_delete(kargaroc);
            
            bk_class* bokoblin = (bk_class*)ac[3];
            bokoblin->m121C = 1;
            bokoblin = (bk_class*)ac[4];
            bokoblin->m121C = 1;
            
            if (dComIfGs_isEventBit(0x301)) {
                bokoblin = (bk_class*)ac[0];
                bokoblin->m121C = 1;
            }
            if (dComIfGs_isEventBit(0x480)) {
                bokoblin = (bk_class*)ac[1];
                bokoblin->m121C = 1;
            }
            if (dComIfGs_isEventBit(0x301) && dComIfGs_isEventBit(0x480)) {
                bokoblin = (bk_class*)ac[2];
                bokoblin->m121C = 1;
            }
        }
        else {
            bk_class* bokoblin = (bk_class*)ac[0];
            bokoblin->m121C = 1;
            bokoblin = (bk_class*)ac[1];
            bokoblin->m121C = 1;
        }
        
        fopAcM_delete(actor);
    }
}

/* 0000081C-00000914       .text event_start_check__FP12andsw0_class */
static void event_start_check(andsw0_class* i_this) {
    fopAc_ac_c* actor = i_this;
    switch (i_this->mEventState) {
    case 0:
        if (i_this->mEventIdx != -1 && fopAcM_isSwitch(actor, i_this->mSwitchToSet)) {
            if (actor->eventInfo.checkCommandDemoAccrpt()) {
                i_this->mEventState++;
            } else {
                fopAcM_orderOtherEventId(actor, i_this->mEventIdx, i_this->mEventNo);
            }
        }

        break;
    case 1:
        if (dComIfGp_evmng_endCheck(i_this->mEventIdx)) {
            dComIfGp_event_reset();
            i_this->mEventState++;
        }
        break;
    case 2:
        break;
    }
}

/* 00000914-00000964       .text daAndsw0_Execute__FP12andsw0_class */
static s32 daAndsw0_Execute(andsw0_class* i_this) {
    event_start_check(i_this);
    if (i_this->mNumSwitchesToCheck == 0xFF)
        hajimarinomori_check(i_this);
    else
        daAndsw0_check(i_this);
    return 1;
}

/* 00000964-0000096C       .text daAndsw0_IsDelete__FP12andsw0_class */
static s32 daAndsw0_IsDelete(andsw0_class*) {
    return 1;
}

/* 0000096C-00000974       .text daAndsw0_Delete__FP12andsw0_class */
static s32 daAndsw0_Delete(andsw0_class*) {
    return 1;
}

/* 00000974-00000A64       .text daAndsw0_Create__FP10fopAc_ac_c */
static s32 daAndsw0_Create(fopAc_ac_c* ac) {
    fopAcM_SetupActor(ac, andsw0_class);

    andsw0_class * i_this = (andsw0_class *)ac;
    i_this->mNumSwitchesToCheck = (fopAcM_GetParam(ac) >> 0) & 0xFF;
    i_this->mBehaviorType = (fopAcM_GetParam(ac) >> 8) & 0xFF;
    i_this->mSwitchToSet = (fopAcM_GetParam(ac) >> 24) & 0xFF;
    i_this->mFirstSwitchToCheck = (fopAcM_GetParam(ac) >> 16) & 0xFF;
    i_this->mTimer = (i_this->home.angle.z & 0xFF) * 15;
    i_this->mEventNo = i_this->home.angle.x;
    i_this->mEventIdx = dComIfGp_evmng_getEventIdx(NULL, i_this->mEventNo);
    if (i_this->mBehaviorType == 2)
        i_this->mAction = ACT_TIMER;
    if (i_this->mFirstSwitchToCheck == 0xFF)
        i_this->mFirstSwitchToCheck = 0;
    if (i_this->mNumSwitchesToCheck == 0xFF) {
        i_this->mSwitchToSet = 0;
        i_this->mBehaviorType = 0;
    }

    return cPhs_COMPLEATE_e;
}

static actor_method_class l_daAndsw0_Method = {
    (process_method_func)daAndsw0_Create,
    (process_method_func)daAndsw0_Delete,
    (process_method_func)daAndsw0_Execute,
    (process_method_func)daAndsw0_IsDelete,
    (process_method_func)daAndsw0_Draw,
};

actor_process_profile_definition g_profile_ANDSW0 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_ANDSW0,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(andsw0_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x0135,
    /* Actor SubMtd */ &l_daAndsw0_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};

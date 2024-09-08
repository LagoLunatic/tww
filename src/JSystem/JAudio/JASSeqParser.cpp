//
// Generated by dtk
// Translation Unit: JASSeqParser.cpp
//

#include "JSystem/JAudio/JASSeqParser.h"
#include "JSystem/JAudio/JASPlayer.h"
#include "JSystem/JAudio/JASTrack.h"
#include "JSystem/JAudio/JASChannel.h"
#include "JSystem/JSupport/JSupport.h"
#include "JSystem/JUtility/JUTAssert.h"

JASystem::TSeqParser::CmdFunc JASystem::TSeqParser::sCmdPList[64] = {
    NULL,
    &JASystem::TSeqParser::cmdOpenTrack,
    &JASystem::TSeqParser::cmdOpenTrackBros,
    NULL,
    &JASystem::TSeqParser::cmdCall,
    NULL,
    &JASystem::TSeqParser::cmdRet,
    NULL,
    &JASystem::TSeqParser::cmdJmp,
    &JASystem::TSeqParser::cmdLoopS,
    &JASystem::TSeqParser::cmdLoopE,
    &JASystem::TSeqParser::cmdReadPort,
    &JASystem::TSeqParser::cmdWritePort,
    &JASystem::TSeqParser::cmdCheckPortImport,
    &JASystem::TSeqParser::cmdCheckPortExport,
    &JASystem::TSeqParser::cmdWait,
    NULL,
    &JASystem::TSeqParser::cmdParentWritePort,
    &JASystem::TSeqParser::cmdChildWritePort,
    NULL,
    &JASystem::TSeqParser::cmdSetLastNote,
    &JASystem::TSeqParser::cmdTimeRelate,
    &JASystem::TSeqParser::cmdSimpleOsc,
    &JASystem::TSeqParser::cmdSimpleEnv,
    &JASystem::TSeqParser::cmdSimpleADSR,
    &JASystem::TSeqParser::cmdTranspose,
    &JASystem::TSeqParser::cmdCloseTrack,
    &JASystem::TSeqParser::cmdOutSwitch,
    &JASystem::TSeqParser::cmdUpdateSync,
    &JASystem::TSeqParser::cmdBusConnect,
    &JASystem::TSeqParser::cmdPauseStatus,
    &JASystem::TSeqParser::cmdSetInterrupt,
    &JASystem::TSeqParser::cmdDisInterrupt,
    &JASystem::TSeqParser::cmdClrI,
    &JASystem::TSeqParser::cmdSetI,
    &JASystem::TSeqParser::cmdRetI,
    &JASystem::TSeqParser::cmdIntTimer,
    &JASystem::TSeqParser::cmdVibDepth,
    &JASystem::TSeqParser::cmdVibDepthMidi,
    &JASystem::TSeqParser::cmdSyncCPU,
    &JASystem::TSeqParser::cmdFlushAll,
    &JASystem::TSeqParser::cmdFlushRelease,
    &JASystem::TSeqParser::cmdWait,
    &JASystem::TSeqParser::cmdPanPowSet,
    &JASystem::TSeqParser::cmdIIRSet,
    &JASystem::TSeqParser::cmdFIRSet,
    &JASystem::TSeqParser::cmdEXTSet,
    &JASystem::TSeqParser::cmdPanSwSet,
    &JASystem::TSeqParser::cmdOscRoute,
    &JASystem::TSeqParser::cmdIIRCutOff,
    &JASystem::TSeqParser::cmdOscFull,
    &JASystem::TSeqParser::cmdVolumeMode,
    &JASystem::TSeqParser::cmdVibPitch,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    &JASystem::TSeqParser::cmdCheckWave,
    &JASystem::TSeqParser::cmdPrintf,
    &JASystem::TSeqParser::cmdNop,
    &JASystem::TSeqParser::cmdTempo,
    &JASystem::TSeqParser::cmdTimeBase,
    &JASystem::TSeqParser::cmdFinish,
};

const JASystem::Arg_s JASystem::Arglist[0x40] = {
    {0x0000, 0x0000},
    {0x0002, 0x0008},
    {0x0002, 0x0008},
    {0x0001, 0x0002},
    {0x0000, 0x0000},
    {0x0000, 0x0000},
    {0x0001, 0x0000},
    {0x0001, 0x0002},
    {0x0000, 0x0000},
    {0x0001, 0x0001},
    {0x0000, 0x0000},
    {0x0002, 0x0000},
    {0x0002, 0x000C},
    {0x0001, 0x0000},
    {0x0001, 0x0000},
    {0x0001, 0x0003},
    {0x0000, 0x0000},
    {0x0002, 0x000C},
    {0x0002, 0x000C},
    {0x0000, 0x0000},
    {0x0001, 0x0000},
    {0x0001, 0x0000},
    {0x0001, 0x0000},
    {0x0002, 0x0008},
    {0x0005, 0x0155},
    {0x0001, 0x0000},
    {0x0001, 0x0000},
    {0x0001, 0x0000},
    {0x0001, 0x0001},
    {0x0002, 0x0004},
    {0x0001, 0x0000},
    {0x0002, 0x0008},
    {0x0001, 0x0000},
    {0x0000, 0x0000},
    {0x0000, 0x0000},
    {0x0000, 0x0000},
    {0x0002, 0x0004},
    {0x0001, 0x0000},
    {0x0001, 0x0001},
    {0x0001, 0x0001},
    {0x0000, 0x0000},
    {0x0000, 0x0000},
    {0x0001, 0x0002},
    {0x0005, 0x0000},
    {0x0004, 0x0055},
    {0x0001, 0x0002},
    {0x0001, 0x0002},
    {0x0003, 0x0000},
    {0x0001, 0x0000},
    {0x0001, 0x0000},
    {0x0003, 0x0028},
    {0x0001, 0x0000},
    {0x0001, 0x0000},
    {0x0000, 0x0000},
    {0x0000, 0x0000},
    {0x0000, 0x0000},
    {0x0000, 0x0000},
    {0x0000, 0x0000},
    {0x0001, 0x0001},
    {0x0000, 0x0000},
    {0x0000, 0x0000},
    {0x0001, 0x0001},
    {0x0001, 0x0001},
    {0x0000, 0x0000},
};

/* 8027E680-8027E728       .text cmdOpenTrack__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdOpenTrack(TTrack* track, u32* args) {
    u32 param1 = args[0];
    u32 param2 = args[1];
    u8 b1 = param1 & 0xF;
    u8 b2 = (param1 >> 6) & 3;
    if (param1 & 0x20) {
        b2 = 4;
    }
    TTrack* child = track->openChild(b1, b2);
    JUT_ASSERT(255, child);
    child->start(track->getSeq()->getBase(), param2);
    return 0;
}

/* 8027E728-8027E800       .text cmdOpenTrackBros__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdOpenTrackBros(TTrack* track, u32* args) {
    if (!track->getParent()) {
        JUT_WARN(268, "%s", "cannot opentrackB in ROOT Track");
        return 0;
    }
    u32 param1 = args[0];
    u32 param2 = args[1];
    u8 b1 = param1 & 0xF;
    u8 b2 = (param1 >> 6) & 3;
    if (param1 & 0x20) {
        b2 = 4;
    }
    TTrack* bros = track->getParent()->openChild(b1, b2);
    JUT_ASSERT(282, bros);
    bros->start(track->getSeq()->getBase(), param2);
    return 0;
}

/* 8027E800-8027E90C       .text cmdCall__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdCall(TTrack* track, u32* args) {
    u8 flag = track->getSeq()->readByte();

    u32 data;
    if (flag & 0x80) {
        u8 cData = track->getSeq()->readByte();
        data = track->readReg16(cData);

        if (flag & 0x40) {
            u32 offs;
            if (flag & 0x20) {
                cData = track->getSeq()->readByte();
                offs = track->readReg16(cData);
            } else {
                offs = track->getSeq()->read24();
            }
            data = track->getSeq()->get24(offs + data * 3);
        }
    } else {
        data = track->getSeq()->read24();
    }

    if (conditionCheck(track, flag)) {
        track->getSeq()->call(data);
    }
    return 0;
}

/* 8027E90C-8027E9AC       .text cmdRet__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdRet(TTrack* track, u32* args) {
    if (conditionCheck(track, args[0])) {
        u32 var1 = track->getSeq()->mLoopIndex;
        bool tmp;
        if (var1 == 0) {
            tmp = false;
        } else {
            tmp = track->getSeq()->ret();
        }
        if (!tmp) {
            JUT_WARN(335, "%s", "cannot ret for call-stack is NULL");
            return 3;
        }
    }
    return 0;
}

/* 8027E9AC-8027EAF4       .text cmdJmp__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdJmp(TTrack* track, u32* args) {
    u8 flag;
    bool usetrackptr = false;
    int trackptr = 0;
    flag = track->getSeq()->readByte();
    u32 data;

    if (flag & 0x80) {
        u8 cData = track->getSeq()->readByte();

        if (flag & 0x40) {
            data = track->readReg16(cData) & 0xffff;
            u32 offs;
            if (flag & 0x20) {
                cData = track->getSeq()->readByte();
                offs = track->readReg16(cData);
            } else {
                offs = track->getSeq()->read24();
            }
            data = track->getSeq()->get24(offs + data * 3);
        } else {
            if (cData >= 0x28 && 0x2b >= cData) {
                trackptr = track->readReg32(cData);
                usetrackptr = true;
            } else {
                data = track->readReg32(cData);
            }
        }
    } else {
        data = track->getSeq()->read24();
    }

    if (conditionCheck(track, flag)) {
        if (usetrackptr) {
            track->getSeq()->start((void*)trackptr, 0);
        } else {
            track->getSeq()->jump(data);
        }
    }
    return 0;
}

/* 8027EAF4-8027EB2C       .text cmdLoopS__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdLoopS(TTrack* track, u32* args) {
    u32 timer = args[0];
    track->getSeq()->loopStart(timer);
    return 0;
}

/* 8027EB2C-8027EB54       .text cmdLoopE__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdLoopE(TTrack* track, u32* args) {
    track->getSeq()->loopEnd();
    return 0;
}

/* 8027EB54-8027EBAC       .text cmdReadPort__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdReadPort(TTrack* track, u32* args) {
    track->writeRegDirect(args[1], track->readSelfPort(args[0]));
    return 0;
}

/* 8027EBAC-8027EBE0       .text cmdWritePort__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdWritePort(TTrack* track, u32* args) {
    track->writeSelfPort(args[0], args[1]);
    return 0;
}

/* 8027EBE0-8027EC68       .text cmdParentWritePort__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdParentWritePort(TTrack* track, u32* args) {
    TTrack* parent = track->getParent();
    JUT_ASSERT(452, parent != NULL);
    parent->writePortAppDirect(args[0] & 0xf, args[1]);
    return 0;
}

/* 8027EC68-8027ED80       .text cmdChildWritePort__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdChildWritePort(TTrack* track, u32* args) {
    u8 param1 = args[0];
    u8 b1 = JSUHiNibble(param1);
    TTrack* child = track->getChild(b1);
    JUT_ASSERT(462, child != NULL);
    child->writePortAppDirect(JSULoNibble(param1), args[1]);
    return 0;
}

/* 8027ED80-8027ED98       .text cmdCheckPortImport__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdCheckPortImport(TTrack* track, u32* args) {
    track->mRegisterParam.setFlag(track->checkImport(args[0]));
    return 0;
}

/* 8027ED98-8027EDB0       .text cmdCheckPortExport__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdCheckPortExport(TTrack* track, u32* args) {
    track->mRegisterParam.setFlag(track->checkExport(args[0]));
    return 0;
}

/* 8027EDB0-8027EDC4       .text cmdWait__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdWait(TTrack* track, u32* args) {
    u32 param1 = args[0];
    track->getSeq()->wait(param1);
    return param1 != 0 ? 1 : 0;
}

/* 8027EDC4-8027EE44       .text cmdSetLastNote__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdSetLastNote(TTrack* track, u32* args) {
    u32 key = args[0];
    key += track->getTranspose();
    JUT_ASSERT(506, key < 256);
    track->mNoteMgr.setLastNote(key);
    return 0;
}

/* 8027EE44-8027EE5C       .text cmdTimeRelate__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdTimeRelate(TTrack* track, u32* args) {
    track->field_0x387 = args[0];
    return 0;
}

/* 8027EE5C-8027EE8C       .text cmdSimpleOsc__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdSimpleOsc(TTrack* track, u32* args) {
    track->oscSetupSimple(args[0]);
    return 0;
}

/* 8027EE8C-8027EEC0       .text cmdSimpleEnv__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdSimpleEnv(TTrack* track, u32* args) {
    track->oscSetupSimpleEnv(args[0], args[1]);
    return 0;
}

/* 8027EEC0-8027EF2C       .text cmdSimpleADSR__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdSimpleADSR(TTrack* track, u32* args) {
    track->field_0x2cc[0] = Player::sAdsrDef;
    track->field_0x2cc[0].table = track->field_0x304;
    track->field_0x304[1] = args[0];
    track->field_0x304[4] = args[1];
    track->field_0x304[7] = args[2];
    track->field_0x304[8] = args[3];
    track->field_0x374 = args[4];
    return 0;

}

/* 8027EF2C-8027EF3C       .text cmdTranspose__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdTranspose(TTrack* track, u32* args) {
    track->setTranspose(args[0]);
    return 0;
}

/* 8027EF3C-8027EFD8       .text cmdCloseTrack__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdCloseTrack(TTrack* track, u32* args) {
    u8 track_no = args[0];
    JUT_ASSERT(565, track_no < TTrack::MAX_CHILDREN);
    if (!track->mChildren[track_no]) {
        return 0;
    }
    track->mChildren[track_no]->close();
    track->mChildren[track_no] = NULL;
    return 0;
}

/* 8027EFD8-8027F02C       .text cmdOutSwitch__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdOutSwitch(TTrack* track, u32* args) {
    TTrack::TOuterParam* outer = track->getOuterParam();
    if (outer) {
        outer->setOuterSwitch(args[0]);
        outer->setOuterUpdate(0xffff);
    }
    return 0;
}

/* 8027F02C-8027F058       .text cmdUpdateSync__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdUpdateSync(TTrack* track, u32* args) {
    track->updateTrack(args[0]);
    return 0;
}

/* 8027F058-8027F088       .text cmdBusConnect__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdBusConnect(TTrack* track, u32* args) {
    track->connectBus(args[0], args[1]);
    return 0;
}

/* 8027F088-8027F098       .text cmdPauseStatus__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdPauseStatus(TTrack* track, u32* args) {
    track->setPauseStatus(args[0]);
    return 0;
}

/* 8027F098-8027F0A8       .text cmdVolumeMode__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdVolumeMode(TTrack* track, u32* args) {
    track->setVolumeMode(args[0]);
    return 0;
}

/* 8027F0A8-8027F0E0       .text cmdSetInterrupt__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdSetInterrupt(TTrack* track, u32* args) {
    track->mIntrMgr.setIntr(args[0], track->getSeq()->getBase() + args[1]);
    return 0;
}

/* 8027F0E0-8027F10C       .text cmdDisInterrupt__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdDisInterrupt(TTrack* track, u32* args) {
    track->mIntrMgr.resetInter(args[0]);
    return 0;
}

/* 8027F10C-8027F124       .text cmdClrI__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdClrI(TTrack* track, u32* args) {
    track->mIntrMgr.enable();
    track->getSeq()->clrIntr();
    return 0;
}

/* 8027F124-8027F134       .text cmdSetI__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdSetI(TTrack* track, u32* args) {
    track->mIntrMgr.disable();
    return 0;
}

/* 8027F134-8027F178       .text cmdRetI__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdRetI(TTrack* track, u32* args) {
    track->mIntrMgr.enable();
    track->getSeq()->retIntr();
    track->tryInterrupt();
    return 0;
}

/* 8027F178-8027F194       .text cmdIntTimer__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdIntTimer(TTrack* track, u32* args) {
    track->mIntrMgr.setTimer(args[0], args[1]);
    return 0;
}

/* 8027F194-8027F1EC       .text cmdSyncCPU__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdSyncCPU(TTrack* track, u32* args) {
    u16 var1 = 0xffff;
    if (TTrack::sCallBackFunc) {
        var1 = TTrack::sCallBackFunc(track, args[0]);
    }
    track->mRegisterParam.setFlag(var1);
    return 0;
}

/* 8027F1EC-8027F214       .text cmdFlushAll__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdFlushAll(TTrack* track, u32* args) {
    track->flushAll();
    return 0;
}

/* 8027F214-8027F23C       .text cmdFlushRelease__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdFlushRelease(TTrack* track, u32* args) {
    track->mChannelUpdater.stopAllRelease();
    return 0;
}

/* 8027F23C-8027F26C       .text cmdTimeBase__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdTimeBase(TTrack* track, u32* args) {
    track->setTimebase(args[0]);
    return 0;
}

/* 8027F26C-8027F29C       .text cmdTempo__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdTempo(TTrack* track, u32* args) {
    track->setTempo(args[0]);
    return 0;
}

/* 8027F29C-8027F2A4       .text cmdFinish__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdFinish(TTrack* track, u32* args) {
    return 3;
}

/* 8027F2A4-8027F2AC       .text cmdNop__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdNop(TTrack* track, u32* args) {
    return 0;
}

/* 8027F2AC-8027F330       .text cmdPanPowSet__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdPanPowSet(TTrack* track, u32* args) {
    track->setPanPower(0, args[0]);
    track->setPanPower(1, args[1]);
    track->setPanPower(2, args[2]);
    track->setPanPower(3, args[3] * 327.67f);
    track->setPanPower(4, args[4] * 327.67f);
    return 0;
}

/* 8027F330-8027F368       .text cmdFIRSet__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdFIRSet(TTrack* track, u32* args) {
    track->getOuterParam()->setFirFilter((s16*)track->getSeq()->getAddr(args[0]));
    return 0;
}

/* 8027F368-8027F3BC       .text cmdEXTSet__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdEXTSet(TTrack* track, u32* args) {
    u8* outerParamAddr = track->getSeq()->getAddr(args[0]);
    TTrack::TOuterParam* outerParam = (TTrack::TOuterParam*)outerParamAddr;
    outerParam->initExtBuffer();
    track->assignExtBuffer((TTrack::TOuterParam*)outerParamAddr);
    return 0;
}

/* 8027F3BC-8027F460       .text cmdPanSwSet__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdPanSwSet(TTrack* track, u32* args) {
    u8 calcTypes[] = { 0, 0, 0, 1, 1, 2, 2 };
    u8 parentCalcTypes[] = { 0, 1, 2, 0, 2, 0, 2 };

    for (u8 i = 0; i < 3; i++) {
        track->mCalcTypes[i] = calcTypes[args[i] >> 5];
        track->mParentCalcTypes[i] = parentCalcTypes[args[i] >> 5];
        track->mChannelUpdater.mCalcTypes[i] = args[i] & 0x1F;
        track->mUpdateFlags |= (OUTERPARAM_Fxmix | OUTERPARAM_Pan | OUTERPARAM_Dolby);
    }

    return 0;
}

/* 8027F460-8027F47C       .text cmdOscRoute__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdOscRoute(TTrack* track, u32* args) {
    track->mOscRoute[(args[0] / 16) & 0xF] = args[0] & 0xF;
    return 0;
}

/* 8027F47C-8027F4C4       .text cmdVibDepth__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdVibDepth(TTrack* track, u32* args) {
    f32 depth = ((u8)args[0] << 8 | (u8)args[0] << 1);
    depth /= 393204.0f;
    track->mVibrate.setDepth(depth);
    return 0;
}

/* 8027F4C4-8027F4FC       .text cmdVibDepthMidi__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdVibDepthMidi(TTrack* track, u32* args) {
    f32 depth = args[0];
    depth /= 393204.0f;
    track->mVibrate.setDepth(depth);
    return 0;
}

/* 8027F4FC-8027F544       .text cmdVibPitch__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdVibPitch(TTrack* track, u32* args) {
    f32 pitch = u16((u8)args[0] << 8 | (u8)args[0] << 1);
    pitch /= 294903.0f;
    track->mVibrate.mPitch = pitch;
    return 0;
}

/* 8027F544-8027F5C8       .text cmdIIRSet__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdIIRSet(TTrack* track, u32* args) {
    for (u8 i = 0; i < 4; i++) {
        // TTrack::MoveParam_* iir = &track->mTimedParam.mInnerParam.mIIRs[i];
        // Fakematch? Accessing mIIRs directly results in fewer instructions than indexing into
        // mVolume as if it was an array.
        TTrack::MoveParam_* iir = (&track->mTimedParam.mInnerParam.mVolume) + (u8)(i + 0xC);
        iir->mTargetValue = (s16)args[i] / 32768.0f;
        iir->mCurrentValue = iir->mTargetValue;
        iir->mMoveAmount = 0.0f;
        iir->mMoveTime = 1.0f;
    }
    return 0;
}

/* 8027F5C8-8027F65C       .text cmdIIRCutOff__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdIIRCutOff(TTrack* track, u32* args) {
    u8 iirTableIdx = args[0];
    for (u8 i = 0; i < 4; i++) {
        s16* table = &JASystem::Player::CUTOFF_TO_IIR_TABLE[iirTableIdx * 4];
        // TTrack::MoveParam_* iir = &track->mTimedParam.mInnerParam.mIIRs[i];
        // Fakematch? Accessing mIIRs directly results in fewer instructions than indexing into
        // mVolume as if it was an array.
        TTrack::MoveParam_* iir = (&track->mTimedParam.mInnerParam.mVolume) + (u8)(i + 0xC);
        iir->mTargetValue = table[i] / (32768.0f - 1.0f);
        iir->mCurrentValue = iir->mTargetValue;
        iir->mMoveAmount = 0.0f;
        iir->mMoveTime = 1.0f;
    }
    return 0;
}

/* 8027F65C-8027F698       .text cmdOscFull__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdOscFull(TTrack* track, u32* args) {
    track->oscSetupFull(args[0], args[1], args[2]);
    return 0;
}

/* 8027F698-8027F6A8       .text cmdCheckWave__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdCheckWave(TTrack* track, u32* args) {
    track->mRegisterParam.setFlag(0);
    return 0;
}

/* 8027F6A8-8027F8F4       .text cmdPrintf__Q28JASystem10TSeqParserFPQ28JASystem6TTrackPUl */
int JASystem::TSeqParser::cmdPrintf(TTrack* track, u32* args) {
    char buf[128];
    u8 byteArray[4];
    int registers[4];
    u32 count = 0;

    u32 i;
    for (i = 0; i < 128; i++) {
        buf[i] = track->getSeq()->readByte();
        if (!buf[i]) {
            break;
        }
        if (buf[i] == '\\') {
            buf[i] = track->getSeq()->readByte();
            if (!buf[i]) {
                break;
            }

			switch (buf[i]) {
			case 'n':
				buf[i] = '\r';
				continue;
			default:
				continue;
			}
        }

        if (buf[i] != '%') {
            continue;
        }

        i++;
        buf[i] = track->getSeq()->readByte();
        if (!buf[i]) {
            break;
        }

        switch (buf[i]) {
        case 'd':
            byteArray[count] = 0;
            break;
        case 'x':
            byteArray[count] = 1;
            break;
        case 's':
            byteArray[count] = 2;
            break;
        case 'r':
            byteArray[count] = 3;
            buf[i] = 'd';
            break;
        case 'R':
            byteArray[count] = 4;
            buf[i] = 'x';
            break;
        case 't':
            byteArray[count] = 5;
            buf[i] = 'x';
            break;
        }
        count++;
    }

    for (i = 0; i < count; i++) {
        registers[i] = track->getSeq()->readByte();
        if (byteArray[i] == 2) {
            registers[i] = (int)track->getSeq()->getAddr(registers[i]);
        } else if (byteArray[i] == 5) {
            registers[i] = track->field_0x36c;
        } else if (byteArray[i] >= 3) {
            registers[i] = track->exchangeRegisterValue(registers[i]);
        }
    }

    OSReport(buf, registers[0], registers[1], registers[2], registers[3]);

    return 0;
}

/* 8027F8F4-8027FA48       .text Cmd_Process__Q28JASystem10TSeqParserFPQ28JASystem6TTrackUcUs */
int JASystem::TSeqParser::Cmd_Process(TTrack* track, u8 r5, u16 r6) {
    JASystem::Arg_s sp08 = Arglist[r5-0xC0];
    u16 r29 = sp08.m02;
    r29 |= r6;
    u32 sp18[10];
    for (int i = 0 ; i < sp08.m00; i++) {
        u32 r3 = 0;
        switch (r29 & 0x3) {
        case 0:
            r3 = track->getSeq()->readByte();
            break;
        case 1:
            r3 = track->getSeq()->read16();
            break;
        case 2:
            r3 = track->getSeq()->read24();
            break;
        case 3:
            r3 = track->exchangeRegisterValue(track->getSeq()->readByte());
            break;
        }
        sp18[i] = r3;
        r29 >>= 2;
    }
    
    JASystem::TSeqParser::CmdFunc cmdFunc = sCmdPList[r5-0xC0];
    if (cmdFunc == NULL) {
        return 0;
    }
    return (this->*cmdFunc)(track, sp18);
}

/* 8027FA48-8027FB08       .text RegCmd_Process__Q28JASystem10TSeqParserFPQ28JASystem6TTrackii */
int JASystem::TSeqParser::RegCmd_Process(TTrack* track, int r30, int r31) {
    u8 r5 = track->getSeq()->readByte();
    if (r30 != 0) {
        r5 = track->exchangeRegisterValue(r5);
    }
    u16 r6 = 0;
    if (r30 == 0 || r31 != 0) {
        u8 r3 = track->getSeq()->readByte();
        u16 r4 = 3;
        for (int i = 0; i < (u32)r31+1; i++) {
            if (r3 & 0x80) {
                r6 |= r4;
            }
            r3 <<= 1;
            r4 <<= 2;
        }
    }
    return Cmd_Process(track, r5, r6);
}

/* 8027FB08-8027FC98       .text cmdSetParam__Q28JASystem10TSeqParserFPQ28JASystem6TTrackUc */
int JASystem::TSeqParser::cmdSetParam(TTrack* track, u8 param_2) {
    u8 flag = track->getSeq()->readByte();

    s16 data;
    switch (param_2 & 0xC) {
    case 0:
        data = track->readReg16(track->getSeq()->readByte());
        break;
    case 4:
        data = track->getSeq()->readByte();
        break;
    case 8:
        u8 byte = track->getSeq()->readByte();
        if (byte & 0x80) {
            data = byte << 8;
        } else {
            data = byte << 8 | byte << 1;
        }
        break;
    case 12:
        data = track->getSeq()->read16();
        break;
    }

    int val = 0;
    switch (param_2 & 0x3) {
    case 0:
        val = -1;
        break;
    case 1:
        val = track->readReg16(track->getSeq()->readByte());
        break;
    case 2:
        val = track->getSeq()->readByte();
        break;
    case 3:
        val = track->getSeq()->read16();
        break;
    }

    track->setParam(flag, (int)data / 32767.0f, val);
    return 0;
}

/* 8027FC98-8027FCE4       .text cmdWait__Q28JASystem10TSeqParserFPQ28JASystem6TTrackUc */
int JASystem::TSeqParser::cmdWait(TTrack* track, u8 flag) {
    int end = flag == 0x80 ? 1 : 2;
    int val = 0;
    for (int i = 0; i < end; i++) {
        val <<= 8;
        val |= track->getSeq()->readByte();
    }
    track->getSeq()->mWaitTimer = val;
    if (val != 0) {
        return 1;
    } else {
        return 0;
    }
}

/* 8027FCE4-8027FE08       .text cmdNoteOff__Q28JASystem10TSeqParserFPQ28JASystem6TTrackUc */
int JASystem::TSeqParser::cmdNoteOff(TTrack* track, u8 flag) {
    if (flag == 0xF9) {
        u32 r30 = track->getSeq()->readByte();
        u32 rdata2 = (track->exchangeRegisterValue(r30 & 0x7) & 0xFF);
        JUT_ASSERT(0x496, rdata2 >= 1);
        JUT_ASSERT(0x497, rdata2 <= 7);
        
        flag = rdata2;
        flag += 0x80;
        if (r30 & 0x80) {
            flag |= 0x08;
        }
    }

    int r6 = 0;
    if ((s32)flag & 0x08) {
        r6 = track->getSeq()->readByte();
        if (r6 > 100) {
            r6 = (r6 - 98) * 20;
        }
    }
    track->noteOff(flag & 0x7, r6);
    return 0;
}

/* 8027FE08-80280148       .text cmdNoteOn__Q28JASystem10TSeqParserFPQ28JASystem6TTrackUc */
int JASystem::TSeqParser::cmdNoteOn(TTrack* track, u8 note) {
    /* Nonmatching */
    u32 r27 = track->getSeq()->readByte();
    if (r27 & 0x80) {
        note = track->exchangeRegisterValue(note);
    }

    note += track->getTranspose();

    u8 r26 = (r27 >> 5) & 0x3;
    u8 r25;
    u32 r24;
    u8 r31;
    if ((r27 >> 5) & 0x2) {
        r31 = note;
        note = track->mNoteMgr.getLastNote();
    }

    r25 = track->getSeq()->readByte();
    if (r25 & 0x80) {
        r25 = track->exchangeRegisterValue(r25 & 0x7F);
    }
    u8 r23;
    u8 noteid = r27 & 0x7;
    int r22 = 0;
    if (!noteid) {
        r23 = track->getSeq()->readByte();
        if (r23 & 0x80) {
            r23 = track->exchangeRegisterValue(r23 & 0x7F);
        }
        r24 = 0;
        int count = (r27 >> 3) & 0x3;
        for (int i = 0; i < count; i++) {
            r24 <<= 8;
            r24 |= track->getSeq()->readByte();
        }

        if ((u32)count == 1 && r24 & 0x80) {
            r24 = track->exchangeRegisterValue(r24 & 0x7F);
        }
    } else {
        if ((r27 >> 3) & 0x3) {
            noteid = track->exchangeRegisterValue(noteid - 1);
            JUT_ASSERT(0x4FE, noteid < 8);
        }
        if (r26 & 1) {
            r22 = track->exchangeRegisterValue(track->getSeq()->readByte());
            r26 ^= 1;
        }

        r24 = -1;
        r23 = 100;
    }

    track->mNoteMgr.setConnectCase(r26);
    r27 = r24;
    s32 time = r24;
    if (track->mNoteMgr.checkBeforeTieMode()) {
        if (track->mNoteMgr.getConnectCase() & 1) {
            time = -1;
        }
        if (time != -1) {
            time = track->seqTimeToDspTime(time, r23);
        }

        if (!track->mIsPaused || !(track->mPauseStatus & 0x10)) {
            track->gateOn(noteid, note, r25, time);
        }
    } else {
        if ((s32)r24 != -1) {
            time = track->seqTimeToDspTime(r24, r23);
        }
        if (track->mNoteMgr.getConnectCase() & 1) {
            time = -1;
        }

        if (!track->mIsPaused || !(track->mPauseStatus & 0x10)) {
            track->noteOn(noteid, note, r25, time, r22);
        }
    }

    track->mNoteMgr.setBaseTime(r24);
    track->mNoteMgr.setBeforeTieMode(track->mNoteMgr.getConnectCase() & 1);
    if (track->mNoteMgr.getConnectCase() & 0x2) {
        s32 val = time;
        if (time == -1) {
            val = track->seqTimeToDspTime(r27, r23);
        }

        JASystem::TChannel* channel = track->mNoteMgr.getChannel(0);
        if (channel) {
            channel->setKeySweepTarget((u8)r31 + track->getTranspose(), val);
        }

        note = r31;
    }

    track->mNoteMgr.setLastNote(note);
    if (r24 == 0xFFFFFFFF) {
        return 0;
    }

    track->getSeq()->wait(r24 ? r27 : -1);

    return 1;
}

/* 80280148-8028024C       .text conditionCheck__Q28JASystem10TSeqParserFPQ28JASystem6TTrackUc */
bool JASystem::TSeqParser::conditionCheck(TTrack* track, u8 param_2) {
    u16 val = (u32)track->mRegisterParam.getFlag();
    switch (param_2 & 0xF) {
    case 0:
        return true;
    case 1:
        return val == 0;
    case 2:
        return val != 0;
    case 3:
        return val == 1;
    case 4:
        return val >= 0x8000;
    case 5:
        return val < 0x8000;
    }

    JUT_ASSERT(0x578, false);

    return false;
}

/* 8028024C-802803B0       .text parseSeq__Q28JASystem10TSeqParserFPQ28JASystem6TTrack */
int JASystem::TSeqParser::parseSeq(TTrack* track) {
    while (true) {
        u8 flag = track->getSeq()->readByte();
        u32 r29 = 0;
        if (!(flag & 0x80)) {
            r29 = cmdNoteOn(track, flag);
        } else if (((flag & 0xF0) == 128) && !(flag & 0x07)) {
            r29 = cmdWait(track, flag);
        } else if (((flag & 0xF0) == 128) || flag == (u32)0xF9) {
            r29 = cmdNoteOff(track, flag);
        } else {
            switch ((s32)flag & 0xF0) {
            case 0x90:
                r29 = cmdSetParam(track, flag & 0xF);
                break;
            case 0xA0:
                track->writeRegParam(flag & 0xF);
                break;
            case 0xB0:
                r29 = RegCmd_Process(track, (flag >> 3) & 1, flag & 0x07);
                break;
            default:
                r29 = Cmd_Process(track, flag, 0);
                break;
            }
        }

        if (r29 == 0) {
            continue;
        }

        if (r29 == 1) {
            break;
        }

        if (r29 == 3) {
            return -1;
        }
    }

    return 0;
}

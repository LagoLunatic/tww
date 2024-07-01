//
// Generated by dtk
// Translation Unit: JAISequenceMgr.cpp
//

#include "JSystem/JAudio/JAISequenceMgr.h"
#include "JSystem/JAudio/JAIBasic.h"
#include "JSystem/JAudio/JAIGlobalParameter.h"
#include "JSystem/JKernel/JKRSolidHeap.h"
#include "string.h"

JAInter::LinkSound JAInter::SequenceMgr::seqControl;
JAInter::SeqUpdateData* JAInter::SequenceMgr::seqTrackInfo;
int* JAInter::SequenceMgr::FixSeqBufPointer;
JKRArchive* JAInter::SequenceMgr::arcPointer;

/* 80295684-802960A0       .text init__Q27JAInter11SequenceMgrFv */
void JAInter::SequenceMgr::init() {
    /* Nonmatching */
    JAIBasic* basic = JAIBasic::getInterface();
    JAISound* soundObjects = basic->makeSound(JAIGlobalParameter::getParamSeqControlBufferMax());
    JUT_ASSERT_MSG(41, soundObjects, "JAISequenceMgr::initHeap Cannot Alloc Heap!!\n");
    FixSeqBufPointer = new (JAIBasic::getCurrentJAIHeap(), 0x20) int[JAIGlobalParameter::getParamSeqPlayTrackMax()];
    seqControl.init(soundObjects, JAIGlobalParameter::getParamSeqControlBufferMax());
    for (int i = 0; i < JAIGlobalParameter::getParamSeqControlBufferMax(); i++) {
        SeqParameter* _para = new (JAIBasic::getCurrentJAIHeap(), 0x20) SeqParameter();
        JUT_ASSERT_MSG(47, _para, "JAISequenceMgr::initHeap Cannot Alloc Heap!!\n");
        seqControl.Buffer[i].field_0x3c = _para;
        _para->seqPan = new (JAIBasic::getCurrentJAIHeap(), 0x20) MoveParaSet[JAIGlobalParameter::getParamSeqParameterLines()];
        JUT_ASSERT_MSG(50, _para->seqPan, "JAISequenceMgr::initHeap Cannot Alloc Heap!!\n");
        _para->seqPitch = new (JAIBasic::getCurrentJAIHeap(), 0x20) MoveParaSet[JAIGlobalParameter::getParamSeqParameterLines()];
        JUT_ASSERT_MSG(52, _para->seqPitch, "JAISequenceMgr::initHeap Cannot Alloc Heap!!\n");
        _para->seqFxmix = new (JAIBasic::getCurrentJAIHeap(), 0x20) MoveParaSet[JAIGlobalParameter::getParamSeqParameterLines()];
        JUT_ASSERT_MSG(54, _para->seqFxmix, "JAISequenceMgr::initHeap Cannot Alloc Heap!!\n");
        _para->seqDolby = new (JAIBasic::getCurrentJAIHeap(), 0x20) MoveParaSet[JAIGlobalParameter::getParamSeqParameterLines()];
        JUT_ASSERT_MSG(56, _para->seqDolby, "JAISequenceMgr::initHeap Cannot Alloc Heap!!\n");
    }
    FixSeqBufPointer = new (JAIBasic::getCurrentJAIHeap(), 0x20) int[JAIGlobalParameter::getParamSeqPlayTrackMax()];
    JUT_ASSERT_MSG(60, FixSeqBufPointer, "JAISequenceMgr::initHeap Cannot Alloc Heap!!\n");
    seqTrackInfo = new (JAIBasic::getCurrentJAIHeap(), 0x20) SeqUpdateData[JAIGlobalParameter::getParamSeqPlayTrackMax()];
    JUT_ASSERT_MSG(62, seqTrackInfo, "JAISequenceMgr::initHeap Cannot Alloc Heap!!\n");
    for (int i = 0; i < JAIGlobalParameter::getParamSeqPlayTrackMax(); i++) {
        FixSeqBufPointer[i] = 0;
        SeqUpdateData* update = &seqTrackInfo[i];
        update->mSeqVolume = 1.0f;
        update->mSeqPitch = 0.5f;
        update->mSeqFxmix = 1.0f;
        update->mSeqPan = 0.0f;
        update->mSeqDolby = 0.0f;
        update->mSeqTempo = 1.0f;
        for (int j = 0; j < JAIGlobalParameter::getParamSeqTrackMax(); j++) {
            update->trackVolume[j] = 1.0f;
            update->trackPan[j] = 64.0f;
            update->trackPitch[j] = 1.0f;
            update->trackFxmix[j] = 0.0f;
            update->trackDolby[j] = 0.0f;
            update->trackupdate[j] = 0;
        }
    }
}

/* 802960A0-80296744       .text __ct__Q27JAInter13SeqUpdateDataFv */
JAInter::SeqUpdateData::SeqUpdateData() {
    field_0x0 = 0;
    field_0x1 = 0;
    field_0x2 = 0;
    field_0x3 = 0;
    field_0x8 = 0;
    field_0x48 = 0;
    systemTrackParameter = new (JAIBasic::getCurrentJAIHeap(), 0x20) PlayerParameter[33];
    JUT_ASSERT_MSG(81, systemTrackParameter, "JAISeqUpdateData Cannot alloc Heap!!\n");
    trackVolume = new (JAIBasic::getCurrentJAIHeap(), 0x20) f32[JAIGlobalParameter::getParamSeqTrackMax()];
    JUT_ASSERT_MSG(83, trackVolume, "JAISeqUpdateData Cannot Alloc Heap!!\n");
    trackPan = new (JAIBasic::getCurrentJAIHeap(), 0x20) f32[JAIGlobalParameter::getParamSeqTrackMax()];
    JUT_ASSERT_MSG(85, trackPan, "JAISeqUpdateData Cannot Alloc Heap!!\n");
    trackPitch = new (JAIBasic::getCurrentJAIHeap(), 0x20) f32[JAIGlobalParameter::getParamSeqTrackMax()];
    JUT_ASSERT_MSG(87, trackPitch, "JAISeqUpdateData Cannot Alloc Heap!!\n");
    trackFxmix = new (JAIBasic::getCurrentJAIHeap(), 0x20) f32[JAIGlobalParameter::getParamSeqTrackMax()];
    JUT_ASSERT_MSG(89, trackFxmix, "JAISeqUpdateData Cannot Alloc Heap!!\n");
    trackDolby = new (JAIBasic::getCurrentJAIHeap(), 0x20) f32[JAIGlobalParameter::getParamSeqTrackMax()];
    JUT_ASSERT_MSG(91, trackDolby, "JAISeqUpdateData Cannot Alloc Heap!!\n");
    trackupdate = new (JAIBasic::getCurrentJAIHeap(), 0x20) int[JAIGlobalParameter::getParamSeqTrackMax() + 1];
    JUT_ASSERT_MSG(99, trackupdate, "JAISeqUpdateData Cannot Alloc Heap!!\n");
}

/* 80296744-80296780       .text __dt__Q27JAInter15PlayerParameterFv */
JAInter::PlayerParameter::~PlayerParameter() {}

/* 80296780-802967B4       .text __ct__Q27JAInter15PlayerParameterFv */
JAInter::PlayerParameter::PlayerParameter() {}

/* 802967B4-80296820       .text getArchiveName__Q27JAInter11SequenceMgrFPc */
void JAInter::SequenceMgr::getArchiveName(char* buffer) {
    buffer[0] = 0;
    if (JAIGlobalParameter::getParamAudioResPath()) {
        strcat(buffer, JAIGlobalParameter::getParamAudioResPath());
    }
    strcat(buffer, JAIGlobalParameter::getParamSequenceArchivesPath());
    strcat(buffer, JAIGlobalParameter::getParamSequenceArchivesFileName());
}

/* 80296820-80296828       .text setArchivePointer__Q27JAInter11SequenceMgrFP10JKRArchive */
void JAInter::SequenceMgr::setArchivePointer(JKRArchive* param_1) {
    arcPointer = param_1;
}

/* 80296828-80296860       .text processGFrameSequence__Q27JAInter11SequenceMgrFv */
void JAInter::SequenceMgr::processGFrameSequence() {
    checkEntriedSeq();
    checkFadeoutSeq();
    checkStoppedSeq();
    checkPlayingSeq();
    checkStartedSeq();
    checkReadSeq();
    checkSeqWave();
}

/* 80296860-80296C24       .text checkEntriedSeq__Q27JAInter11SequenceMgrFv */
void JAInter::SequenceMgr::checkEntriedSeq() {
    /* Nonmatching */
}

/* 80296C24-80296CCC       .text checkFadeoutSeq__Q27JAInter11SequenceMgrFv */
void JAInter::SequenceMgr::checkFadeoutSeq() {
    /* Nonmatching */
}

/* 80296CCC-80296D6C       .text checkStoppedSeq__Q27JAInter11SequenceMgrFv */
void JAInter::SequenceMgr::checkStoppedSeq() {
    /* Nonmatching */
}

/* 80296D6C-80296E6C       .text checkPlayingSeq__Q27JAInter11SequenceMgrFv */
void JAInter::SequenceMgr::checkPlayingSeq() {
    /* Nonmatching */
}

/* 80296E6C-80296F00       .text checkStartedSeq__Q27JAInter11SequenceMgrFv */
void JAInter::SequenceMgr::checkStartedSeq() {
    /* Nonmatching */
}

/* 80296F00-8029713C       .text checkReadSeq__Q27JAInter11SequenceMgrFv */
void JAInter::SequenceMgr::checkReadSeq() {
    /* Nonmatching */
}

/* 8029713C-80297238       .text checkSeqWave__Q27JAInter11SequenceMgrFv */
void JAInter::SequenceMgr::checkSeqWave() {
    /* Nonmatching */
}

/* 80297238-80297378       .text checkPlayingSeqUpdateMultiplication__Q27JAInter11SequenceMgrFUlUcUlPQ27JAInter11MoveParaSetPUlUcPf */
void JAInter::SequenceMgr::checkPlayingSeqUpdateMultiplication(u32, u8, u32, JAInter::MoveParaSet*, u32*, u8, f32*) {
    /* Nonmatching */
}

/* 80297378-802974F8       .text checkPlayingSeqUpdateAddition__Q27JAInter11SequenceMgrFUlUcUlPQ27JAInter11MoveParaSetPUlUcPff */
void JAInter::SequenceMgr::checkPlayingSeqUpdateAddition(u32, u8, u32, JAInter::MoveParaSet*, u32*, u8, f32*, f32) {
    /* Nonmatching */
}

/* 802974F8-80297618       .text checkPlayingSeqUpdateTrack__Q27JAInter11SequenceMgrFUlUlPQ27JAInter11MoveParaSetPUlUcPf */
void JAInter::SequenceMgr::checkPlayingSeqUpdateTrack(u32, u32, JAInter::MoveParaSet*, u32*, u8, f32*) {
    /* Nonmatching */
}

/* 80297618-80297E18       .text checkPlayingSeqTrack__Q27JAInter11SequenceMgrFUl */
void JAInter::SequenceMgr::checkPlayingSeqTrack(u32) {
    /* Nonmatching */
}

/* 80297E18-80297F14       .text stopSeq__Q27JAInter11SequenceMgrFP8JAISound */
void JAInter::SequenceMgr::stopSeq(JAISound*) {
    /* Nonmatching */
}

/* 80297F14-80297FD0       .text checkDvdLoadArc__Q27JAInter11SequenceMgrFUlUl */
void JAInter::SequenceMgr::checkDvdLoadArc(u32, u32) {
    /* Nonmatching */
}

/* 80297FD0-80298208       .text storeSeqBuffer__Q27JAInter11SequenceMgrFPP8JAISoundPQ27JAInter5ActorUlUlUcPv */
void JAInter::SequenceMgr::storeSeqBuffer(JAISound**, JAInter::Actor*, u32, u32, u8, void*) {
    /* Nonmatching */
}

/* 80298208-802982C0       .text releaseSeqBuffer__Q27JAInter11SequenceMgrFP8JAISoundUl */
void JAInter::SequenceMgr::releaseSeqBuffer(JAISound*, u32) {
    /* Nonmatching */
}

/* 802982C0-802982D0       .text getPlayTrackInfo__Q27JAInter11SequenceMgrFUl */
JAInter::SeqUpdateData* JAInter::SequenceMgr::getPlayTrackInfo(u32) {
    /* Nonmatching */
}

/* 802982D0-802982F0       .text __ct__Q27JAInter7MuteBitFv */
JAInter::MuteBit::MuteBit() {
    flag1 = 0;
    flag3 = 0;
}

//
// Generated by dtk
// Translation Unit: control.cpp
//

#include "JSystem/JStudio/JStudio_JMessage/control.h"
#include "dolphin/types.h"

namespace JStudio_JMessage {

namespace {

// Fake inline.
// TODO: supposed to use JStudio::TObject::createFromAdaptor instead of this somehow
inline JStudio::TObject_message* message_creator(const JStudio::stb::data::TParse_TBlock_object& data,
                                                 TAdaptor_message* adaptor)
{
    JStudio::TObject_message* object = new JStudio::TObject_message(data, adaptor);

    if (!object) {
        return NULL;
    }
    if (object->mpAdaptor) {
        object->mpAdaptor->adaptor_do_prepare(object);
    }
    return object;
}

/* 8027A3F4-8027A4A8       .text createObject_MESSAGE_JMS___Q216JStudio_JMessage21@unnamed@control_cpp@FRCQ47JStudio3stb4data20TParse_TBlock_objectPQ28JMessage8TControl */
JStudio::TObject_message* createObject_MESSAGE_JMS_(const JStudio::stb::data::TParse_TBlock_object& data, JMessage::TControl* system)
{
    TAdaptor_message* adaptor = new TAdaptor_message(system);
    if (!adaptor) {
        return NULL;
    }

    return message_creator(data, adaptor);
}

} // namespace

/* 8027A4A8-8027A508       .text __dt__Q216JStudio_JMessage18TCreateObject_baseFv */
TCreateObject_base::~TCreateObject_base() {}

/* 8027A508-8027A5AC       .text create__Q216JStudio_JMessage18TCreateObject_baseFPPQ27JStudio7TObjectRCQ47JStudio3stb4data20TParse_TBlock_object */
bool TCreateObject_base::create(JStudio::TObject** newObject, const JStudio::stb::data::TParse_TBlock_object& data) {
    JStudio::TObject_message* (*func)(const JStudio::stb::data::TParse_TBlock_object&, JMessage::TControl*);
    switch (data.get()->type) {
    case 'JMSG':
        func = &createObject_MESSAGE_JMS_;
        break;
    default:
        return false;
    }

    JMessage::TControl* system = find(data);

    if (!system) {
        return false;
    }

    *newObject = func(data, system);
    return true;
}

/* 8027A5AC-8027A60C       .text __dt__Q216JStudio_JMessage13TCreateObjectFv */
TCreateObject::~TCreateObject() {}

/* 8027A60C-8027A614       .text find__Q216JStudio_JMessage13TCreateObjectFRCQ47JStudio3stb4data20TParse_TBlock_object */
JMessage::TControl* TCreateObject::find(const JStudio::stb::data::TParse_TBlock_object&) {
    return mControl;
}

} // namespace JStudio_JMessage

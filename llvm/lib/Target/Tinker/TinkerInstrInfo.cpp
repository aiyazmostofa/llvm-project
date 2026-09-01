#include "TinkerInstrInfo.h"
#include "TinkerSubtarget.h"

#define GET_INSTRINFO_CTOR_DTOR
#include "TinkerGenInstrInfo.inc"

using namespace llvm;

TinkerInstrInfo::TinkerInstrInfo(const TinkerSubtarget &STI)
    : TinkerGenInstrInfo(STI, RI) {}
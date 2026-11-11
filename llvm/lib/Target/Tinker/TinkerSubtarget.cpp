#include "TinkerSubtarget.h"
#include "llvm/Target/TargetMachine.h"

#define DEBUG_TYPE "tinker-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "TinkerGenSubtargetInfo.inc"

using namespace llvm;

void TinkerSubtarget::anchor() {}

TinkerSubtarget::TinkerSubtarget(const Triple &TT, const std::string &CPU,
                                 const std::string &FS, const TargetMachine &TM)
    : TinkerGenSubtargetInfo(TT, CPU, /*TuneCPU*/ CPU, FS), InstrInfo(*this),
      FrameLowering(*this), TLInfo(TM, *this) {}
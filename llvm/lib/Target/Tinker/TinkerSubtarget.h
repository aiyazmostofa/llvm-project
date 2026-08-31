#pragma once

#include "TinkerInstrInfo.h"
#include "TinkerRegisterInfo.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"

#define GET_SUBTARGETINFO_HEADER
#include "TinkerGenSubtargetInfo.inc"

namespace llvm {

class TinkerSubtarget : public TinkerGenSubtargetInfo {
  TinkerInstrInfo InstrInfo;
  TinkerRegisterInfo RegisterInfo;

public:
  const TinkerInstrInfo *getInstrInfo() const override { return &InstrInfo; }
  const TinkerRegisterInfo *getRegisterInfo() const override {
    return &RegisterInfo;
  }
};

} // namespace llvm
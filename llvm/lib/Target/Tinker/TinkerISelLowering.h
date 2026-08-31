#pragma once

#include "TinkerRegisterInfo.h"
#include "llvm/CodeGen/TargetLowering.h"

namespace llvm {

class TinkerSubtarget;

class TinkerTargetLowering : public TargetLowering {
public:
  explicit TinkerTargetLowering(const TargetMachine &TM,
                                const TinkerSubtarget &STI);
};

} // namespace llvm
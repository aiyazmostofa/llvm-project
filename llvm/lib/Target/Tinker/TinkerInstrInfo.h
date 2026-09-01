#pragma once

#include "TinkerRegisterInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "TinkerGenInstrInfo.inc"

namespace llvm {
class TinkerSubtarget;

class TinkerInstrInfo : public TinkerGenInstrInfo {
  const TinkerRegisterInfo RI;

public:
  explicit TinkerInstrInfo(const TinkerSubtarget &STI);

  const TinkerRegisterInfo &getRegisterInfo() const { return RI; }
};

} // namespace llvm
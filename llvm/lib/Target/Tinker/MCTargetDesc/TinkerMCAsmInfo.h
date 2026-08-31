#pragma once

#include "llvm/MC/MCAsmInfoELF.h"
#include "llvm/TargetParser/Triple.h"

namespace llvm {

class TinkerMCAsmInfoELF : public MCAsmInfoELF {
public:
  explicit TinkerMCAsmInfoELF(const Triple &TT, const MCTargetOptions &Options);
};

} // namespace llvm
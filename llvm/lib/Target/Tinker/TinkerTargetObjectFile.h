#pragma once

#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"

namespace llvm {

class TinkerTargetObjectFile : public TargetLoweringObjectFileELF {
public:
  TinkerTargetObjectFile();
};

} // namespace llvm
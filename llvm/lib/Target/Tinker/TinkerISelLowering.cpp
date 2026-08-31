#include "TinkerISelLowering.h"
#include "TinkerSubtarget.h"
#include "llvm/Target/TargetMachine.h"

using namespace llvm;

TinkerTargetLowering::TinkerTargetLowering(const TargetMachine &TM,
                                           const TinkerSubtarget &STI)
    : TargetLowering(TM, STI) {}
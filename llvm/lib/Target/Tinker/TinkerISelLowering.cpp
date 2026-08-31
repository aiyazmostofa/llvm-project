#include "TinkerISelLowering.h"
#include "TinkerSubtarget.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/CodeGenTypes/MachineValueType.h"
#include "llvm/CodeGen/CallingConvLower.h"
#include "MCTargetDesc/TinkerMCTargetDesc.h"

using namespace llvm;

TinkerTargetLowering::TinkerTargetLowering(const TargetMachine &TM,
                                           const TinkerSubtarget &STI)
    : TargetLowering(TM, STI) {}

#define GET_CALLING_CONV_IMPL
#include "TinkerGenCallingConv.inc"

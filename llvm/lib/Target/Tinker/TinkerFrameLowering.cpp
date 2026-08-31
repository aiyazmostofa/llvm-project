#include "TinkerFrameLowering.h"
#include "llvm/CodeGen/MachineFunction.h"

using namespace llvm;

TinkerFrameLowering::TinkerFrameLowering(const TinkerSubtarget &STI)
    : TargetFrameLowering(TargetFrameLowering::StackGrowsDown, Align(1), 0) {}

bool TinkerFrameLowering::hasFPImpl(const MachineFunction &MF) const {
  return true;
}

void TinkerFrameLowering::emitPrologue(MachineFunction &MF,
                                       MachineBasicBlock &MBB) const {}

void TinkerFrameLowering::emitEpilogue(MachineFunction &MF,
                                       MachineBasicBlock &MBB) const {}
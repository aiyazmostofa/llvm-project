#pragma once

#include "llvm/CodeGen/TargetFrameLowering.h"

namespace llvm {
class TinkerSubtarget;

class TinkerFrameLowering final : public TargetFrameLowering {
public:
  explicit TinkerFrameLowering(const TinkerSubtarget &STI);

  void emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
  void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const override;

  MachineBasicBlock::iterator
  eliminateCallFramePseudoInstr(MachineFunction &MF, MachineBasicBlock &MBB,
                                MachineBasicBlock::iterator MI) const override {
    return MBB.erase(MI);
  }

protected:
  bool hasFPImpl(const MachineFunction &MF) const override;
};

} // namespace llvm
#include "TinkerInstrInfo.h"
#include "TinkerSubtarget.h"
#include "MCTargetDesc/TinkerMCTargetDesc.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"

#define GET_INSTRINFO_CTOR_DTOR
#include "TinkerGenInstrInfo.inc"

using namespace llvm;

TinkerInstrInfo::TinkerInstrInfo(const TinkerSubtarget &STI)
    : TinkerGenInstrInfo(STI, RI) {}

// FIXME: Learn what renamable registers are.
void TinkerInstrInfo::copyPhysReg(MachineBasicBlock &MBB,
                                  MachineBasicBlock::iterator MI,
                                  const DebugLoc &DL, Register DestReg,
                                  Register SrcReg, bool KillSrc,
                                  bool RenamableDest, bool RenamableSrc) const {
  auto Opc = Tinker::Copy;
  BuildMI(MBB, MI, DL, get(Opc), DestReg).addReg(SrcReg, getKillRegState(KillSrc));
}

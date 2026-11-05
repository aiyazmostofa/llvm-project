#include "TinkerRegisterInfo.h"
#include "TinkerFrameLowering.h"
#include "TinkerSubtarget.h"
#include "llvm/CodeGen/MachineFunction.h"

#define GET_REGINFO_ENUM
#define GET_REGINFO_TARGET_DESC
#include "TinkerGenRegisterInfo.inc"

using namespace llvm;

TinkerRegisterInfo::TinkerRegisterInfo() : TinkerGenRegisterInfo(Tinker::R0) {}

const MCPhysReg *
TinkerRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  return CSR_SaveList;
}

const uint32_t *
TinkerRegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                         CallingConv::ID CC) const {
  return CSR_RegMask;
}

BitVector TinkerRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());
  markSuperRegs(Reserved, Tinker::R0);
  markSuperRegs(Reserved, Tinker::R1);
  markSuperRegs(Reserved, Tinker::SP);
  return Reserved;
}

bool TinkerRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                             int SPAdj, unsigned FIOperandNum,
                                             RegScavenger *RS) const {
  return false;
}

Register TinkerRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  return Tinker::SP;
}

#include "TinkerISelLowering.h"
#include "TinkerSubtarget.h"
#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/Target/TargetMachine.h"
#include "MCTargetDesc/TinkerMCTargetDesc.h"

using namespace llvm;

TinkerTargetLowering::TinkerTargetLowering(const TargetMachine &TM,
                                           const TinkerSubtarget &STI)
    : TargetLowering(TM, STI) {
  addRegisterClass(MVT::i64, &Tinker::GPRRegClass);
  addRegisterClass(MVT::f64, &Tinker::GPRRegClass);
  computeRegisterProperties(STI.getRegisterInfo());
}

#define GET_CALLING_CONV_IMPL
#include "TinkerGenCallingConv.inc"

/*
  FIXME: Don't fully understand the code below.
  It was taken from the book.
  After I get more knowledge, come back and see if I do understand it.
*/

SDValue TinkerTargetLowering::LowerFormalArguments(
    SDValue Chain, CallingConv::ID CallConv, bool IsVarArg,
    const SmallVectorImpl<ISD::InputArg> &Ins, const SDLoc &DL,
    SelectionDAG &DAG, SmallVectorImpl<SDValue> &InVals) const {
  MachineFunction &MF = DAG.getMachineFunction();
  MachineRegisterInfo &RegInfo = MF.getRegInfo();

  SmallVector<CCValAssign, 16> ArgLocs;
  CCState CCInfo(CallConv, IsVarArg, MF, ArgLocs, *DAG.getContext());
  CCInfo.AnalyzeFormalArguments(Ins, CC_Tinker_Common);

  for (size_t I = 0; I < ArgLocs.size(); ++I) {
    auto &VA = ArgLocs[I];
    if (VA.isRegLoc()) {
      if (VA.getLocInfo() != CCValAssign::Full)
        report_fatal_error("non-full passing, not yet implemented");
      EVT RegVT = VA.getLocVT();
      const TargetRegisterClass *DstRC = &Tinker::GPRRegClass;

      Register VReg = RegInfo.createVirtualRegister(DstRC);
      RegInfo.addLiveIn(VA.getLocReg(), VReg);
      SDValue ArgValue = DAG.getCopyFromReg(Chain, DL, VReg, RegVT);
      InVals.push_back(ArgValue);
    } else {
      report_fatal_error("can't spill to stack yet");
    }
  }
  return Chain;
}

SDValue TinkerTargetLowering::LowerReturn(
    SDValue Chain, CallingConv::ID CallConv, bool IsVarArg,
    const SmallVectorImpl<ISD::OutputArg> &Outs,
    const SmallVectorImpl<SDValue> &OutVals, const SDLoc &DL,
    SelectionDAG &DAG) const {
  if (Outs.size() > 1)
    report_fatal_error("can't return > 1 register");

  SmallVector<CCValAssign, 1> RetValLocs;
  MachineFunction &MF = DAG.getMachineFunction();

  CCState CCInfo(CallConv, IsVarArg, MF, RetValLocs, *DAG.getContext());
  CCInfo.AnalyzeReturn(Outs, RetCC_Tinker_Common);

  SDValue Glue;
  SmallVector<SDValue, 4> RetOps(1, Chain);

  for (size_t i = 0, e = RetValLocs.size(); i != e; ++i) {
    CCValAssign &VA = RetValLocs[i];
    if (!VA.isRegLoc())
      report_fatal_error("stack return not yet implemented");
    if (VA.getLocInfo() != CCValAssign::Full &&
        VA.getLocInfo() != CCValAssign::BCvt)
      report_fatal_error("extension/truncation of any sort, not yet implemented");

    Chain = DAG.getCopyToReg(Chain, DL, VA.getLocReg(), OutVals[i], Glue);
    Glue = Chain.getValue(1);
    RetOps.push_back(DAG.getRegister(VA.getLocReg(), VA.getLocVT()));
  }

  RetOps[0] = Chain;
  if (Glue.getNode())
    RetOps.push_back(Glue);

  return DAG.getNode(TinkerISD::RETURN_GLUE, DL, MVT::Other, RetOps);
}

const char *TinkerTargetLowering::getTargetNodeName(unsigned Opcode) const {
  switch ((TinkerISD::NodeType)Opcode) {
  case TinkerISD::FIRST_NUMBER:
    break;
  case TinkerISD::RETURN_GLUE:
    return "TinkerISD::RETURN_GLUE";
  }
  return nullptr;
}

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
  setOperationAction(ISD::ADD, MVT::i64, Custom);
  setOperationAction(ISD::BR_CC, MVT::i64, Expand);
  setOperationAction(ISD::BRCOND, MVT::Other, Custom);
  setOperationAction(ISD::SETCC, MVT::i64, Custom);
  setCondCodeAction(ISD::SETLT, MVT::i64, Expand);
  setCondCodeAction(ISD::SETLE, MVT::i64, Expand);
  setCondCodeAction(ISD::SETGE, MVT::i64, Expand);
  setCondCodeAction(ISD::SETULT, MVT::i64, Expand);
  setCondCodeAction(ISD::SETULE, MVT::i64, Expand);
  setCondCodeAction(ISD::SETUGE, MVT::i64, Expand);
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
  case TinkerISD::SUBI_FROM_ADDI:
    return "TinkerISD::SUBI_FROM_ADDI";
  case TinkerISD::TO_BOOL:
    return "TinkerISD::TO_BOOL";
  case TinkerISD::LOGICAL_NOT:
    return "TinkerISD::LOGICAL_NOT";
  case TinkerISD::NODE_BRANCH_NOT_ZERO:
    return "TinkerISD::NODE_BRANCH_NOT_ZERO";
  case TinkerISD::NODE_BRANCH_GREATER:
    return "TinkerISD::NODE_BRANCH_GREATER";
  }
  return nullptr;
}

SDValue TinkerTargetLowering::LowerOperation(SDValue Op,
                                             SelectionDAG &DAG) const {
  switch (Op.getOpcode()) {
  case ISD::ADD:
    return LowerADD(Op, DAG);
  case ISD::BRCOND:
    return LowerBRCOND(Op, DAG);
  case ISD::SETCC:
    return LowerSETCC(Op, DAG);
  default:
    report_fatal_error("lower operation not implemented");
  }
}

SDValue TinkerTargetLowering::LowerADD(SDValue Op, SelectionDAG &DAG) const {
  assert(Op.getValueType() == MVT::i64);
  if (!isa<ConstantSDNode>(Op.getOperand(1))) {
    return Op;
  }
  APInt Value = Op.getConstantOperandAPInt(1);
  if (Value.isNonNegative()) {
    return Op;
  }
  return DAG.getNode(TinkerISD::SUBI_FROM_ADDI, SDLoc(Op), MVT::i64, Op.getOperand(0),
                     DAG.getConstant(Value.abs(), SDLoc(Op), MVT::i64));
}

SDValue TinkerTargetLowering::LowerBRCOND(SDValue Op, SelectionDAG &DAG) const {
  auto Chain = Op.getOperand(0);
  auto UncastedCond = Op.getOperand(1);
  auto Target = Op.getOperand(2);
  if (UncastedCond.getOpcode() != ISD::SETCC) {
    return DAG.getNode(TinkerISD::NODE_BRANCH_NOT_ZERO, SDLoc(Op),
                             MVT::Other, Chain, UncastedCond, Target);
  }
  auto *Cond = cast<CondCodeSDNode>(UncastedCond.getOperand(2));
  if (Cond->get() == ISD::CondCode::SETGT) {
    return DAG.getNode(TinkerISD::NODE_BRANCH_GREATER, SDLoc(Op), MVT::Other,
                       Chain, UncastedCond.getOperand(0),
                       UncastedCond.getOperand(1), Target);
  }
  if (Cond->get() == ISD::CondCode::SETLT) {
    return DAG.getNode(TinkerISD::NODE_BRANCH_GREATER, SDLoc(Op), MVT::Other,
                       Chain, UncastedCond.getOperand(1),
                       UncastedCond.getOperand(0), Target);
  }
  return DAG.getNode(TinkerISD::NODE_BRANCH_NOT_ZERO, SDLoc(Op),
                             MVT::Other, Chain, UncastedCond, Target);
}

SDValue TinkerTargetLowering::LowerSETCC(SDValue Op, SelectionDAG &DAG) const {
  auto *Cond = cast<CondCodeSDNode>(Op.getOperand(2));
  switch (Cond->get()) {
  case ISD::SETEQ:
    return DAG.getNode(
        TinkerISD::LOGICAL_NOT, SDLoc(Op), MVT::i64,
        DAG.getNode(TinkerISD::TO_BOOL, SDLoc(Op), MVT::i64,
                    DAG.getNode(ISD::SUB, SDLoc(Op), MVT::i64, Op.getOperand(0),
                                Op.getOperand(1))));
  case ISD::SETNE:
    return DAG.getNode(TinkerISD::TO_BOOL, SDLoc(Op), MVT::i64,
                       DAG.getNode(ISD::SUB, SDLoc(Op), MVT::i64,
                                   Op.getOperand(0), Op.getOperand(1)));
  case ISD::SETUGT:
  case ISD::SETGT:
    report_fatal_error("setcc operation lower not implemented yet");
  default:
    return Op;
  }
}

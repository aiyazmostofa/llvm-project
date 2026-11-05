#pragma once

#include "TinkerRegisterInfo.h"
#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/TargetLowering.h"
#include "llvm/IR/Type.h"

namespace llvm {

class TinkerSubtarget;

namespace TinkerISD {

enum NodeType : unsigned {
  FIRST_NUMBER = ISD::BUILTIN_OP_END,
  RETURN_GLUE,
  SUBI_FROM_ADDI,
  TO_BOOL,
  LOGICAL_NOT,
  NODE_BRANCH_NOT_ZERO,
  NODE_BRANCH_GREATER,
};

} // namespace TinkerISD

bool RetCC_Tinker_Common(unsigned ValNo, MVT ValVT, MVT LocVT,
                         CCValAssign::LocInfo LocInfo, ISD::ArgFlagsTy ArgFlags,
                         Type *OrigTy, CCState &State);

class TinkerTargetLowering : public TargetLowering {
public:
  explicit TinkerTargetLowering(const TargetMachine &TM,
                                const TinkerSubtarget &STI);

  SDValue LowerFormalArguments(SDValue Chain, CallingConv::ID CallConv,
                               bool IsVarArg,
                               const SmallVectorImpl<ISD::InputArg> &Ins,
                               const SDLoc &DL, SelectionDAG &DAG,
                               SmallVectorImpl<SDValue> &InVals) const override;

  SDValue LowerReturn(SDValue Chain, CallingConv::ID CallConv, bool IsVarArg,
                      const SmallVectorImpl<ISD::OutputArg> &Outs,
                      const SmallVectorImpl<SDValue> &OutVals, const SDLoc &DL,
                      SelectionDAG &DAG) const override;

  SDValue LowerOperation(SDValue Op, SelectionDAG &DAG) const override;

  SDValue LowerADD(SDValue Op, SelectionDAG &DAG) const;
  SDValue LowerBRCOND(SDValue Op, SelectionDAG &DAG) const;
  SDValue LowerSETCC(SDValue Op, SelectionDAG &DAG) const;

  const char *getTargetNodeName(unsigned Opcode) const override;
};

} // namespace llvm

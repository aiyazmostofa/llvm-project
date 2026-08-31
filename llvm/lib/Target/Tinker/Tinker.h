#pragma once

#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"

namespace llvm {

class TinkerTargetMachine;
class PassRegistry;

class TinkerISelDAGToDAGPass : public SelectionDAGISelPass {
public:
  explicit TinkerISelDAGToDAGPass(TinkerTargetMachine &TM);
};

FunctionPass *createTinkerISelDag(TinkerTargetMachine &TM);
void initializeTinkerDAGToDAGISelLegacyPass(PassRegistry &);

} // namespace llvm
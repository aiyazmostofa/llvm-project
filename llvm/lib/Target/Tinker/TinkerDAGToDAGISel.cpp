#include "Tinker.h"
#include "TinkerTargetMachine.h"
#include "MCTargetDesc/TinkerMCTargetDesc.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/InitializePasses.h"
#include "llvm/Pass.h"
#include "llvm/Support/Debug.h"
#include "llvm/Target/TargetMachine.h"

using namespace llvm;

#define DEBUG_TYPE "tinker-isel"
#define PASS_NAME "Tinker DAG->DAG Pattern Instruction Selection"

namespace llvm {

class TinkerDAGToDAGISel : public SelectionDAGISel {
public:
  explicit TinkerDAGToDAGISel(TargetMachine &TM) : SelectionDAGISel(TM) {}

private:
  void Select(SDNode *N) override;

#include "TinkerGenDAGISel.inc"
};

} // namespace llvm

namespace {

class TinkerDAGToDAGISelLegacy : public SelectionDAGISelLegacy {
public:
  static char ID;
  TinkerDAGToDAGISelLegacy(TinkerTargetMachine &TM)
      : SelectionDAGISelLegacy(ID, std::make_unique<TinkerDAGToDAGISel>(TM)) {}
};

} // namespace

char TinkerDAGToDAGISelLegacy::ID = 0;

INITIALIZE_PASS(TinkerDAGToDAGISelLegacy, DEBUG_TYPE, PASS_NAME, false, false)

void TinkerDAGToDAGISel::Select(SDNode *N) {
  if (N->isMachineOpcode()) {
    return;
  }
  SelectCode(N);
}

FunctionPass *llvm::createTinkerISelDag(TinkerTargetMachine &TM) {
  return new TinkerDAGToDAGISelLegacy(TM);
}

TinkerISelDAGToDAGPass::TinkerISelDAGToDAGPass(TinkerTargetMachine &TM)
    : SelectionDAGISelPass(std::make_unique<TinkerDAGToDAGISel>(TM)) {}

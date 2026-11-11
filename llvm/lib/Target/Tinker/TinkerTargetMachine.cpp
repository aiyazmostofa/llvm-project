#include "TinkerTargetMachine.h"
#include "TargetInfo/TinkerTargetInfo.h"
#include "Tinker.h"
#include "TinkerTargetObjectFile.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/InitializePasses.h"

using namespace llvm;

TinkerTargetMachine::TinkerTargetMachine(const Target &T, const Triple &TT,
                                         StringRef CPU, StringRef FS,
                                         const TargetOptions &Options,
                                         std::optional<Reloc::Model> RM,
                                         std::optional<CodeModel::Model> CM,
                                         CodeGenOptLevel OL, bool JIT)
    : CodeGenTargetMachineImpl(T, TT, CPU, FS, Options,
                               RM ? *RM : Reloc::Static,
                               CM ? *CM : CodeModel::Small, OL),
      TLOF(std::make_unique<TinkerTargetObjectFile>()) {
  initAsmInfo();
}
TinkerTargetMachine::~TinkerTargetMachine() = default;

const TinkerSubtarget *
TinkerTargetMachine::getSubtargetImpl(const Function &F) const {
  if (!SubtargetSingleton)
    SubtargetSingleton = std::make_unique<TinkerSubtarget>(
        TargetTriple, TargetCPU, TargetFS, *this);
  return SubtargetSingleton.get();
}

namespace {

class TinkerPassConfig : public TargetPassConfig {
public:
  TinkerPassConfig(TinkerTargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  bool addInstSelector() override {
    addPass(createTinkerISelDag(getTM<TinkerTargetMachine>()));
    return false;
  }
};

} // namespace

TargetPassConfig *TinkerTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new TinkerPassConfig(*this, PM);
}

extern "C" LLVM_C_ABI void LLVMInitializeTinkerTarget() {
  RegisterTargetMachine<TinkerTargetMachine> X(getTheTinkerTarget());
}

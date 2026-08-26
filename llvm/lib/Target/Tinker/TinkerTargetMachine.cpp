#include "TinkerTargetMachine.h"
#include "TargetInfo/TinkerTargetInfo.h"

using namespace llvm;

TinkerTargetMachine::TinkerTargetMachine(const Target &T, const Triple &TT,
                                         StringRef CPU, StringRef FS,
                                         const TargetOptions &Options,
                                         std::optional<Reloc::Model> RM,
                                         std::optional<CodeModel::Model> CM,
                                         CodeGenOptLevel OL, bool JIT)
    : CodeGenTargetMachineImpl(T, TT, CPU, FS, Options,
                               RM ? *RM : Reloc::Static,
                               CM ? *CM : CodeModel::Small, OL) {}
TinkerTargetMachine::~TinkerTargetMachine() = default;

extern "C" LLVM_C_ABI void LLVMInitializeTinkerTarget() {
  RegisterTargetMachine<TinkerTargetMachine> X(getTheTinkerTarget());
}

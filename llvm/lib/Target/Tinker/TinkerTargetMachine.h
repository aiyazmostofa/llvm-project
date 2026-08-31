#include "llvm/CodeGen/CodeGenTargetMachineImpl.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/CodeGen.h"

namespace llvm {
class TinkerTargetMachine final : public CodeGenTargetMachineImpl {
public:
  TinkerTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                      StringRef FS, const TargetOptions &Options,
                      std::optional<Reloc::Model> RM,
                      std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                      bool JIT);
  ~TinkerTargetMachine() override;

  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;
};
} // namespace llvm

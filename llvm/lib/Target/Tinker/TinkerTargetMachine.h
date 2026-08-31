#include "TinkerSubtarget.h"
#include "llvm/CodeGen/CodeGenTargetMachineImpl.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/Target/TargetLoweringObjectFile.h"
#include <memory>

namespace llvm {
class TinkerTargetMachine final : public CodeGenTargetMachineImpl {
  mutable std::unique_ptr<TinkerSubtarget> SubtargetSingleton;
  std::unique_ptr<TargetLoweringObjectFile> TLOF;

public:
  TinkerTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                      StringRef FS, const TargetOptions &Options,
                      std::optional<Reloc::Model> RM,
                      std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                      bool JIT);
  ~TinkerTargetMachine() override;

  const TinkerSubtarget *getSubtargetImpl(const Function &F) const override;

  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }
};
} // namespace llvm

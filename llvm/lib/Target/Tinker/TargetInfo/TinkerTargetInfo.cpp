#include "TargetInfo/TinkerTargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Compiler.h"

using namespace llvm;

Target &llvm::getTheTinkerTarget() {
  static Target TheTinkerTarget;
  return TheTinkerTarget;
}

extern "C" LLVM_ABI void LLVMInitializeTinkerTargetInfo() {
  RegisterTarget<Triple::tinker, /*HasJIT=*/false> X(
      getTheTinkerTarget(), "tinker", "Tinker", "Tinker");
}

#include "TinkerMCTargetDesc.h"
#include "MCTargetDesc/TinkerInstPrinter.h"
#include "TargetInfo/TinkerTargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Compiler.h"

using namespace llvm;

static MCInstPrinter *createTinkerMCInstPrinter(const Triple &T,
                                                unsigned SyntaxVariant,
                                                const MCAsmInfo &MAI,
                                                const MCInstrInfo &MII,
                                                const MCRegisterInfo &MRI) {
  return new TinkerInstPrinter(MAI, MII, MRI);
}

extern "C" LLVM_ABI void LLVMInitializeTinkerTargetMC() {
  TargetRegistry::RegisterMCCodeEmitter(getTheTinkerTarget(), createTinkerMCCodeEmitter);
  TargetRegistry::RegisterMCInstPrinter(getTheTinkerTarget(), createTinkerMCInstPrinter);
}

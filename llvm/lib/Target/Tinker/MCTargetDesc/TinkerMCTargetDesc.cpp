#include "TinkerMCTargetDesc.h"
#include "MCTargetDesc/TinkerInstPrinter.h"
#include "MCTargetDesc/TinkerMCAsmInfo.h"
#include "TargetInfo/TinkerTargetInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/ErrorHandling.h"

#define GET_INSTRINFO_MC_DESC
#include "TinkerGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "TinkerGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "TinkerGenRegisterInfo.inc"

using namespace llvm;

static MCAsmInfo *createTinkerMCAsmInfo(const MCRegisterInfo &MRI,
                                        const Triple &TheTriple,
                                        const MCTargetOptions &Options) {
  if (TheTriple.isOSBinFormatELF())
    return new TinkerMCAsmInfoELF(TheTriple, Options);
  report_fatal_error("binary format not supported");
}

static MCInstrInfo *createTinkerMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitTinkerMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createTinkerMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitTinkerMCRegisterInfo(X, Tinker::NoRegister);
  return X;
}

static MCSubtargetInfo *
createTinkerMCSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS) {
  return createTinkerMCSubtargetInfoImpl(TT, CPU, /*TuneCPU*/ CPU, FS);
}

static MCInstPrinter *createTinkerMCInstPrinter(const Triple &T,
                                                unsigned SyntaxVariant,
                                                const MCAsmInfo &MAI,
                                                const MCInstrInfo &MII,
                                                const MCRegisterInfo &MRI) {
  return new TinkerInstPrinter(MAI, MII, MRI);
}

extern "C" LLVM_ABI void LLVMInitializeTinkerTargetMC() {
  Target &TheTarget = getTheTinkerTarget();
  RegisterMCAsmInfoFn X(TheTarget, createTinkerMCAsmInfo);
  TargetRegistry::RegisterMCInstrInfo(TheTarget, createTinkerMCInstrInfo);
  TargetRegistry::RegisterMCRegInfo(TheTarget, createTinkerMCRegisterInfo);
  TargetRegistry::RegisterMCSubtargetInfo(TheTarget,
                                          createTinkerMCSubtargetInfo);
  TargetRegistry::RegisterMCCodeEmitter(TheTarget, createTinkerMCCodeEmitter);
  TargetRegistry::RegisterMCInstPrinter(TheTarget, createTinkerMCInstPrinter);
}
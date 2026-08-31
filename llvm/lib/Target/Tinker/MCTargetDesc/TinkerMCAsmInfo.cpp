#include "MCTargetDesc/TinkerMCAsmInfo.h"

using namespace llvm;

TinkerMCAsmInfoELF::TinkerMCAsmInfoELF(const Triple &TT,
                                       const MCTargetOptions &Options)
    : MCAsmInfoELF(Options) {
  SupportsDebugInformation = true;
  MinInstAlignment = 4;
  CodePointerSize = 8;
}
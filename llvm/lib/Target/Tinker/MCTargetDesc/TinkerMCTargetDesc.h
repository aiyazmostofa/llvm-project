#pragma once

#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCInstrInfo.h"
namespace llvm {
MCCodeEmitter *createTinkerMCCodeEmitter(const MCInstrInfo &MCII, MCContext &Ctx);
}

#define GET_REGINFO_ENUM
#include "TinkerGenRegisterInfo.inc"

#define GET_INSTRINFO_ENUM
#define GET_INSTRINFO_MC_HELPER_DECLS
#include "TinkerGenInstrInfo.inc"

#include "MCTargetDesc/TinkerMCTargetDesc.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/Support/Endian.h"

using namespace llvm;

class TinkerMCCodeEmitter : public MCCodeEmitter {
  const MCContext &MCCtxt;

public:
  TinkerMCCodeEmitter(const MCInstrInfo &MCII, MCContext &Ctx) : MCCtxt(Ctx) {}

  uint64_t getBinaryCodeForInstr(const MCInst &MI,
                                 SmallVectorImpl<MCFixup> &Fixups,
                                 const MCSubtargetInfo &STI) const;

  unsigned getMachineOpValue(const MCInst &MI, const MCOperand &MO,
                             SmallVectorImpl<MCFixup> &Fixups,
                             const MCSubtargetInfo &STI) const;

  void encodeInstruction(const MCInst &Inst, SmallVectorImpl<char> &CB,
                         SmallVectorImpl<MCFixup> &Fixups,
                         const MCSubtargetInfo &STI) const override;
};

unsigned
TinkerMCCodeEmitter::getMachineOpValue(const MCInst &MI, const MCOperand &MO,
                                       SmallVectorImpl<MCFixup> &Fixups,
                                       const MCSubtargetInfo &STI) const {
  if (MO.isReg())
    return MCCtxt.getRegisterInfo()->getEncodingValue(MO.getReg());
  return static_cast<unsigned>(MO.getImm());
}

void TinkerMCCodeEmitter::encodeInstruction(const MCInst &Inst,
                                            SmallVectorImpl<char> &CB,
                                            SmallVectorImpl<MCFixup> &Fixups,
                                            const MCSubtargetInfo &STI) const {
  uint64_t Encoding = getBinaryCodeForInstr(Inst, Fixups, STI);
  CB.resize(sizeof(uint32_t));
  support::endian::write<uint32_t>(CB.data(), Encoding,
                                   llvm::endianness::little);
}

MCCodeEmitter *llvm::createTinkerMCCodeEmitter(const MCInstrInfo &MCII,
                                               MCContext &Ctx) {
  return new TinkerMCCodeEmitter(MCII, Ctx);
}

#include "TinkerGenMCCodeEmitter.inc"
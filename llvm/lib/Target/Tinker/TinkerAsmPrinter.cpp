#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/TargetRegistry.h"
#include "TargetInfo/TinkerTargetInfo.h"

namespace llvm {
class TinkerAsmPrinter : public AsmPrinter {
  bool lowerOperand(const MachineOperand &MO, MCOperand &MCO);
  MCInst MachineInstrToMCInst(const MachineInstr &MI);

public:
  explicit TinkerAsmPrinter(TargetMachine &TM,
                            std::unique_ptr<MCStreamer> Streamer)
      : AsmPrinter(TM, std::move(Streamer)) {}
  void emitInstruction(const MachineInstr *MI) override;
};

/*
  FIXME: Don't fully understand the code below.
  It was taken from the book.
  After I get more knowledge, come back and see if I do understand it.
*/

bool TinkerAsmPrinter::lowerOperand(const MachineOperand &MO, MCOperand &MCO) {
  switch (MO.getType()) {
  default:
    llvm_unreachable("unknown operand type");
  case MachineOperand::MO_Register:
    if (MO.isImplicit())
      return false;
    MCO = MCOperand::createReg(MO.getReg());
    break;
  case MachineOperand::MO_RegisterMask:
    return false;
  case MachineOperand::MO_Immediate:
    MCO = MCOperand::createImm(MO.getImm());
    break;
  case MachineOperand::MO_GlobalAddress: {
    const GlobalValue *GV = MO.getGlobal();
    MCSymbol *Sym = getSymbol(GV);
    const MCExpr *Expr = MCSymbolRefExpr::create(Sym, OutContext);
    MCO = MCOperand::createExpr(Expr);
    break;
  }
  case MachineOperand::MO_ExternalSymbol: {
    MCSymbol *Sym = GetExternalSymbolSymbol(MO.getSymbolName());
    const MCExpr *Expr = MCSymbolRefExpr::create(Sym, OutContext);
    MCO = MCOperand::createExpr(Expr);
    break;
  }
  case MachineOperand::MO_MachineBasicBlock:
  case MachineOperand::MO_MCSymbol:
  case MachineOperand::MO_JumpTableIndex:
  case MachineOperand::MO_ConstantPoolIndex:
  case MachineOperand::MO_BlockAddress:
    llvm_unreachable("not yet implemented");
  }
  return true;
}

MCInst TinkerAsmPrinter::MachineInstrToMCInst(const MachineInstr &MI) {
  MCInst TmpInst;
  TmpInst.setOpcode(MI.getOpcode());

  for (const MachineOperand &MO : MI.operands()) {
    MCOperand MCOp;
    if (lowerOperand(MO, MCOp))
      TmpInst.addOperand(MCOp);
  }
  return TmpInst;
}

void TinkerAsmPrinter::emitInstruction(const MachineInstr *MI) {
  MCInst TmpInst = MachineInstrToMCInst(*MI);
  EmitToStreamer(*OutStreamer, TmpInst);
}
} // namespace llvm

using namespace llvm;

extern "C" LLVM_ABI void LLVMInitializeTinkerAsmPrinter() {
  RegisterAsmPrinter<TinkerAsmPrinter> Tmp(getTheTinkerTarget());
}

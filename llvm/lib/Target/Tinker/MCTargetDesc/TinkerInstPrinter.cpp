#include "MCTargetDesc/TinkerInstPrinter.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"

using namespace llvm;

#define PRINT_ALIAS_INSTR
#include "TinkerGenAsmWriter.inc"

void TinkerInstPrinter::printInst(const MCInst *MI, uint64_t Address,
                                  StringRef Annot, const MCSubtargetInfo &STI,
                                  raw_ostream &O) {
  if (!PrintAliases || !printAliasInstr(MI, Address, O))
    printInstruction(MI, Address, O);
  printAnnotation(O, Annot);
}

void TinkerInstPrinter::printOperand(const MCInst *MI, unsigned OpNo,
                                     raw_ostream &O) {
  const MCOperand &Op = MI->getOperand(OpNo);
  if (Op.isReg()) {
    unsigned Reg = Op.getReg();
    O << getRegisterName(Reg);
  } else if (Op.isImm()) {
    O << formatImm(Op.getImm());
  } else {
    assert(Op.isExpr() && "unknown operand kind in printOperand");
    MAI.printExpr(O, *Op.getExpr());
  }
}

void TinkerInstPrinter::printBranchTarget(const MCInst *MI, uint64_t Address,
                                          int OpNum, raw_ostream &O) {
  const MCOperand &MC = MI->getOperand(OpNum);
  if (MI->getOperand(OpNum).isImm()) {
    llvm_unreachable("Can't handle this now");
  }
  if (MC.isExpr()) {
    MAI.printExpr(O, *MC.getExpr());
  } else {
    llvm_unreachable("Invalid operand");
  }
}

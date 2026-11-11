#include "llvm/MC/MCInstPrinter.h"

namespace llvm {

class TinkerInstPrinter : public MCInstPrinter {
public:
  TinkerInstPrinter(const MCAsmInfo &MAI, const MCInstrInfo &MII,
                    const MCRegisterInfo &MRI)
      : MCInstPrinter(MAI, MII, MRI) {}

  void printInst(const MCInst *MI, uint64_t Address, StringRef Annot,
                 const MCSubtargetInfo &STI, raw_ostream &O) override;
  void printOperand(const MCInst *MI, unsigned OpNo, raw_ostream &O);
  void printBranchTarget(const MCInst *MI, uint64_t Address, int OpNum,
                         raw_ostream &O);

  std::pair<const char *, uint64_t>
  getMnemonic(const MCInst &MI) const override;
  void printInstruction(const MCInst *MI, uint64_t Address, raw_ostream &O);
  bool printAliasInstr(const MCInst *MI, uint64_t Address, raw_ostream &OS);
  static const char *getRegisterName(MCRegister Reg);
};

} // namespace llvm

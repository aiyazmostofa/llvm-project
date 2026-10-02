class InstrFormat<string n, bits<5> Enc> : Instruction {
  let Namespace = "Tinker";
  bits<32> Inst;
  let Inst{4-0} = Enc;
  let AsmString = n;
  let OutOperandList = (outs);
  let InOperandList = (ins);
}

class InstrFormat2Address<string n, bits<5> Enc> : InstrFormat<n, Enc> {
  bits<5> dst0;
  bits<5> src0;
  let Inst{9-5} = dst0;
  let Inst{14-10} = src0;
  let AsmString = !strconcat(n, " $dst0, $src0");
  let OutOperandList = (outs GPR:$dst0);
  let InOperandList = (ins GPR:$src0);
}

def GPRLenVT : ValueTypeByHwMode<[DefaultMode], [i64]>;

class InstrFormatImm<string n, bits<5> Enc, dag ins> : InstrFormat<n, Enc> {
  bits<5> dst0;
  bits<5> src0;
  bits<12> imm;
  let Inst{9-5} = dst0;
  let Inst{31-20} = imm;
  let AsmString = !strconcat(n, " $dst0, $imm");
  let OutOperandList = (outs GPR:$dst0);
  let InOperandList = ins;
  // FIXME: Ask Moobonbon why the registers are tied.
  let Constraints = "$dst0 = $src0";
}

def uimm12 : Operand<GPRLenVT>, ImmLeaf<GPRLenVT, [{return isUInt<12>(Imm);}]>;
def simm12 : Operand<GPRLenVT>, ImmLeaf<GPRLenVT, [{return isInt<12>(Imm);}]>;

class InstrFormatSImm<string n, bits<5> Enc> : InstrFormatImm<n, Enc, (ins GPR:$src0, simm12:$imm)>;
class InstrFormatUImm<string n, bits<5> Enc> : InstrFormatImm<n, Enc, (ins GPR:$src0, uimm12:$imm)>;

class InstrFormat3Address<string n, bits<5> Enc> : InstrFormat2Address<n, Enc> {
  bits<5> src1;
  let Inst{19-15} = src1;
  let AsmString = !strconcat(n, " $dst0, $src0, $src1");
  let OutOperandList = (outs GPR:$dst0);
  let InOperandList = (ins GPR:$src0, GPR:$src1);
}

class InstrFormat<string n, bits<5> Enc> : Instruction {
  let Namespace = "Tinker";
  bits<32> Inst;
  bits<5> dst0;
  bits<5> src0;
  bits<5> src1;
  let Inst{4-0} = Enc;
  let Inst{9-5} = dst0;
  let Inst{14-10} = src0;
  let Inst{19-15} = src1;
  let AsmString = !strconcat(n, " $dst0, $src0, $src1");
  let OutOperandList = (outs GPR:$dst0);
  let InOperandList = (ins GPR:$src0, GPR:$src1);
}

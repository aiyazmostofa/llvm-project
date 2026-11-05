def SubiFromAddi: SDNode<"TinkerISD::SUBI_FROM_ADDI",
  SDTypeProfile<1, 2, [
    SDTCisInt<0>,
    SDTCisInt<1>,
    SDTCisInt<2>,
  ]>
>;

def ToBool: SDNode<"TinkerISD::TO_BOOL",
  SDTypeProfile<1, 1, [
    SDTCisInt<0>,
    SDTCisInt<1>,
  ]>
>;

def LogicalNot: SDNode<"TinkerISD::LOGICAL_NOT",
  SDTypeProfile<1, 1, [
    SDTCisInt<0>,
    SDTCisInt<1>,
  ]>
>;

def NodeBranchNotZero: SDNode<"TinkerISD::NODE_BRANCH_NOT_ZERO",
  SDTypeProfile<0, 2, [
    SDTCisInt<0>,
    SDTCisVT<1, OtherVT>,
  ]>,
  [SDNPHasChain]
>;

def NodeBranchGreater: SDNode<"TinkerISD::NODE_BRANCH_GREATER",
  SDTypeProfile<0, 3, [
    SDTCisInt<0>,
    SDTCisInt<1>,
    SDTCisVT<2, OtherVT>,
  ]>,
  [SDNPHasChain]
>;

let Pattern = [(set GPR:$dst0, (add GPR:$src0, GPR:$src1))] in
def Add : InstrFormat3Address<"add", 0x18>;

let Pattern = [(set GPR:$dst0, (sub GPR:$src0, GPR:$src1))] in
def Sub : InstrFormat3Address<"sub", 0x1a>;

let Pattern = [(set GPR:$dst0, (mul GPR:$src0, GPR:$src1))] in
def Mul : InstrFormat3Address<"mul", 0x1c>;

let Pattern = [(set GPR:$dst0, (sdiv GPR:$src0, GPR:$src1))] in
def Div : InstrFormat3Address<"div", 0x1d>;

let Pattern = [(set GPR:$dst0, (add GPR:$src0, uimm12:$imm))] in
def Addi : InstrFormatUImm<"addi", 0x19>;

def Subi : InstrFormatUImm<"subi", 0x1b>;
def : Pat<(sub GPR:$src0, uimm12:$imm), (Subi GPR:$src0, uimm12:$imm)>;
def : Pat<(SubiFromAddi GPR:$src0, uimm12:$imm), (Subi GPR:$src0, uimm12:$imm)>;

let Pattern = [(set GPR:$dst0, (fadd GPR:$src0, GPR:$src1))] in
def Addf : InstrFormat3Address<"addf", 0x14>;

let Pattern = [(set GPR:$dst0, (fsub GPR:$src0, GPR:$src1))] in
def Subf : InstrFormat3Address<"subf", 0x15>;

let Pattern = [(set GPR:$dst0, (fmul GPR:$src0, GPR:$src1))] in
def Mulf : InstrFormat3Address<"mulf", 0x16>;

let Pattern = [(set GPR:$dst0, (fdiv GPR:$src0, GPR:$src1))] in
def Divf : InstrFormat3Address<"divf", 0x17>;

let Pattern = [(set GPR:$dst0, (and GPR:$src0, GPR:$src1))] in
def And : InstrFormat3Address<"and", 0x0>;

let Pattern = [(set GPR:$dst0, (or GPR:$src0, GPR:$src1))] in
def Or : InstrFormat3Address<"or", 0x1>;

let Pattern = [(set GPR:$dst0, (xor GPR:$src0, GPR:$src1))] in
def Xor : InstrFormat3Address<"xor", 0x2>;

let Pattern = [(set GPR:$dst0, (not GPR:$src0))] in
def Not : InstrFormat2Address<"not", 0x3>;

let Pattern = [(set GPR:$dst0, (srl GPR:$src0, GPR:$src1))] in
def Shftr : InstrFormat3Address<"shftr", 0x4>;

let Pattern = [(set GPR:$dst0, (srl GPR:$src0, uimm12:$imm))] in
def Shftri : InstrFormatUImm<"shftri", 0x5>;

let Pattern = [(set GPR:$dst0, (shl GPR:$src0, GPR:$src1))] in
def Shftl : InstrFormat3Address<"shftl", 0x6>;

let Pattern = [(set GPR:$dst0, (shl GPR:$src0, uimm12:$imm))] in
def Shftli : InstrFormatUImm<"shftli", 0x7>;

def Copy : InstrFormat2Address<"mov", 0x11>;

def Jump : InstrFormat<"br", 0x8> {
  bits<5> src0;
  let Inst{9-5} = src0;
  let InOperandList = (ins GPR:$src0);
  let isTerminator = 1;
  let isBarrier = 1;
  let isBranch = 1;
  let AsmString = "br $src0";
  // FIXME: This is a hack (kinda), we should lower this nicer
  let isIndirectBranch = 1;
}

def BranchNotZero : InstrFormat<"brnz", 0xb> {
  bits<5> src0;
  bits<5> src1;
  let Inst{9-5} = src0;
  let Inst{14-10} = src1;
  let InOperandList = (ins GPR:$src0, GPR:$src1);
  let isTerminator = 1;
  let isBranch = 1;
  let AsmString = "brnz $src0, $src1";
  let isIndirectBranch = 1;
}

def BranchGreater : InstrFormat<"brgt", 0xe> {
  bits<5> src0;
  bits<5> src1;
  bits<5> src2;
  let Inst{9-5} = src0;
  let Inst{14-10} = src1;
  let Inst{19-15} = src2;
  let InOperandList = (ins GPR:$src0, GPR:$src1, GPR:$src2);
  let isTerminator = 1;
  let isBranch = 1;
  let AsmString = "brgt $src0, $src1, $src2";
  let isIndirectBranch = 1;
}

def LoadConstant : InstrFormat<"ld", 0x00> {
  bits<5> dst0;
  bits<64> src0;
  let InOperandList = (ins uimm64:$src0);
  let OutOperandList = (outs GPR:$dst0);
  let isPseudo = 1;
  let AsmString = "ld $dst0, $src0";
  let Pattern = [(set GPR:$dst0, uimm64:$src0)];
}

def LoadTarget : InstrFormat<"ld", 0x00> {
  bits<5> dst0;
  bits<64> src0;
  let InOperandList = (ins brtarget:$src0);
  let OutOperandList = (outs GPR:$dst0);
  let isPseudo = 1;
  let AsmString = "ld $dst0, $src0";
}

def : Pat<(ToBool GPR:$x), (Shftri (Or (Sub (i64 R0), GPR:$x), GPR:$x), 63)>;
def : Pat<(LogicalNot GPR:$x), (Xor GPR:$x, (i64 R1))>;

def : Pat<(br bb:$src0), (Jump (LoadTarget brtarget:$src0))>;
def : Pat<(NodeBranchNotZero GPR:$src0, bb:$src1), (BranchNotZero (LoadTarget brtarget:$src1), GPR:$src0)>;
def : Pat<(NodeBranchGreater GPR:$src0, GPR:$src1, bb:$src2), (BranchGreater (LoadTarget brtarget:$src2), GPR:$src0, GPR:$src1)>;

def Return : InstrFormat<"return", 0x0d> {
  let Uses = [R10, SP];
  let mayLoad = 1;
  let isReturn = 1;
  let isTerminator = 1;
  let isBarrier = 1;
  let Pattern = [(SDNode<"TinkerISD::RETURN_GLUE", SDTNone,
                        [SDNPHasChain, SDNPOptInGlue, SDNPOutGlue,
                        SDNPVariadic]>)];
}

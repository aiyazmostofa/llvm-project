let Pattern = [(set GPR:$dst0, (add GPR:$src0, GPR:$src1))] in
def Add : InstrFormat3Address<"add", 0x18>;

let Pattern = [(set GPR:$dst0, (sub GPR:$src0, GPR:$src1))] in
def Sub : InstrFormat3Address<"sub", 0x1a>;

let Pattern = [(set GPR:$dst0, (mul GPR:$src0, GPR:$src1))] in
def Mul : InstrFormat3Address<"mul", 0x1c>;

let Pattern = [(set GPR:$dst0, (sdiv GPR:$src0, GPR:$src1))] in
def Div : InstrFormat3Address<"div", 0x1d>;

let Pattern = [(set GPR:$dst0, (fadd GPR:$src0, GPR:$src1))] in
def Addf : InstrFormat3Address<"addf", 0x14>;

let Pattern = [(set GPR:$dst0, (fsub GPR:$src0, GPR:$src1))] in
def Subf : InstrFormat3Address<"subf", 0x15>;

let Pattern = [(set GPR:$dst0, (fmul GPR:$src0, GPR:$src1))] in
def Mulf : InstrFormat3Address<"mulf", 0x16>;

let Pattern = [(set GPR:$dst0, (fdiv GPR:$src0, GPR:$src1))] in
def Divf : InstrFormat3Address<"divf", 0x17>;

def Ret : InstrFormat<"ret", 0x0d> {
  let Uses = [R0, SP];
  let mayLoad = 1;
  let isReturn = 1;
  let isTerminator = 1;
  let isBarrier = 1;
  let Pattern = [(SDNode<"TinkerISD::RETURN_GLUE", SDTNone,
                        [SDNPHasChain, SDNPOptInGlue, SDNPOutGlue,
                        SDNPVariadic]>)];
}

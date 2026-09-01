let Pattern = [(set GPR:$dst0, (add GPR:$src0, GPR:$src1))] in
def Add : InstrFormat3Address<"add", 0x18>;

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

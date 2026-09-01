def CC_Tinker_Common : CallingConv<[
  // Made this up.
  CCIfType<[i64,f64], CCAssignToReg<[R1, R2, R3, R4, R5, R6, R7, R8]>>,
  CCAssignToStack<1, 1>
]>;

let Entry = 1 in
def RetCC_Tinker_Common : CallingConv<[
  CCIfType<[i64,f64], CCAssignToReg<[R0]>>
]>;

def CSR : CalleeSavedRegs<(add R9, R10, R11, R12, R13, R14, R15, R16)>;
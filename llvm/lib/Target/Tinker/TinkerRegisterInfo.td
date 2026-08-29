class TinkerReg<string n, bits<16> Enc> : Register<n> {
  let Namespace = "Tinker";
  let HWEncoding = Enc;
}

// Explicit
def R0  : TinkerReg<"r0",  0>;
def R1  : TinkerReg<"r1",  1>;
def R2  : TinkerReg<"r2",  2>;
def R3  : TinkerReg<"r3",  3>;
def R4  : TinkerReg<"r4",  4>;
def R5  : TinkerReg<"r5",  5>;
def R6  : TinkerReg<"r6",  6>;
def R7  : TinkerReg<"r7",  7>;
def R8  : TinkerReg<"r8",  8>;
def R9  : TinkerReg<"r9",  9>;
def R10 : TinkerReg<"r10", 10>;
def R11 : TinkerReg<"r11", 11>;
def R12 : TinkerReg<"r12", 12>;
def R13 : TinkerReg<"r13", 13>;
def R14 : TinkerReg<"r14", 14>;
def R15 : TinkerReg<"r15", 15>;
def R16 : TinkerReg<"r16", 16>;
def R17 : TinkerReg<"r17", 17>;
def R18 : TinkerReg<"r18", 18>;
def R19 : TinkerReg<"r19", 19>;
def R20 : TinkerReg<"r20", 20>;
def R21 : TinkerReg<"r21", 21>;
def R22 : TinkerReg<"r22", 22>;
def R23 : TinkerReg<"r23", 23>;
def R24 : TinkerReg<"r24", 24>;
def R25 : TinkerReg<"r25", 25>;
def R26 : TinkerReg<"r26", 26>;
def R27 : TinkerReg<"r27", 27>;
def R28 : TinkerReg<"r28", 28>;
def R29 : TinkerReg<"r29", 29>;
def R30 : TinkerReg<"r30", 30>;

// Explicit and Implicit
def SP  : TinkerReg<"sp",  31>;

def GPR : RegisterClass<"Tinker", [i64, f64], 64,
                        (add R0, R1, R2, R3, R4, R5, R6, R7, R8, R9, R10,
                             R11, R12, R13, R14, R15, R16, R17, R18, R19,
                             R20, R21, R22, R23, R24, R25, R26, R27, R28,
                             R29, R30, SP)>;

def StackPointer : RegisterClass<"Tinker", [i64], 64, (add SP)>;

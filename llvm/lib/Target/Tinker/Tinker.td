include "llvm/Target/Target.td"

include "TinkerRegisterInfo.td"
include "TinkerInstrFormat.td"
include "TinkerInstrInfo.td"
include "TinkerCallingConv.td"

defm : RemapAllTargetPseudoPointerOperands<GPR>;

def TinkerInstrInfo : InstrInfo;
def Tinker : Target {
  let InstructionSet = TinkerInstrInfo;
}
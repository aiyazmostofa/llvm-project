add_llvm_component_group(Tinker)

set(LLVM_TARGET_DEFINITIONS Tinker.td)
tablegen(LLVM TinkerGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM TinkerGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM TinkerGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM TinkerGenMCCodeEmitter.inc -gen-emitter)
tablegen(LLVM TinkerGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM TinkerGenDAGISel.inc -gen-dag-isel)

add_llvm_target(TinkerCodeGen
  TinkerTargetMachine.cpp
  TinkerAsmPrinter.cpp
  TinkerDAGToDAGISel.cpp

  LINK_COMPONENTS
  MC
  Support
  CodeGen

  ADD_TO_COMPONENT
  Tinker
)

add_public_tablegen_target(TinkerCommonTableGen)

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)

add_llvm_component_group(Tinker)

set(LLVM_TARGET_DEFINITIONS Tinker.td)
tablegen(LLVM TinkerGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM TinkerGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM TinkerGenMCCodeEmitter.inc -gen-emitter)
tablegen(LLVM TinkerGenAsmWriter.inc -gen-asm-writer)

add_llvm_target(TinkerCodeGen
  TinkerTargetMachine.cpp

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

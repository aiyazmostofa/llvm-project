add_llvm_component_group(Tinker)

add_llvm_target(TinkerCodeGen
  TinkerTargetMachine.cpp

  LINK_COMPONENTS
  MC
  Support
  CodeGen

  ADD_TO_COMPONENT
  Tinker
)

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)

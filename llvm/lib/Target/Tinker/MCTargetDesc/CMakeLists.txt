add_llvm_component_library(LLVMTinkerDesc
  TinkerMCTargetDesc.cpp
  TinkerMCCodeEmitter.cpp
  TinkerInstPrinter.cpp
  TinkerMCAsmInfo.cpp

  LINK_COMPONENTS
  MC
  Support
  TinkerInfo

  ADD_TO_COMPONENT
  Tinker
)

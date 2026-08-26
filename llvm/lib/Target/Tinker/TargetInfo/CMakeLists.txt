add_llvm_component_library(LLVMTinkerInfo
  TinkerTargetInfo.cpp

  LINK_COMPONENTS
  MC
  Support

  ADD_TO_COMPONENT
  Tinker
)

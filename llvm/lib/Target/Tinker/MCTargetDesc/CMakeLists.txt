add_llvm_component_library(LLVMTinkerDesc
  TinkerMCTargetDesc.cpp

  LINK_COMPONENTS
  Support

  ADD_TO_COMPONENT
  Tinker
)

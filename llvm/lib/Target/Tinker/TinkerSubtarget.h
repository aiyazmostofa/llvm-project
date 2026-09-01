#pragma once

#include "TinkerFrameLowering.h"
#include "TinkerISelLowering.h"
#include "TinkerRegisterInfo.h"
#include "llvm/CodeGen/SelectionDAGTargetInfo.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"

#define GET_SUBTARGETINFO_HEADER
#include "TinkerGenSubtargetInfo.inc"

namespace llvm {

class TinkerSubtarget : public TinkerGenSubtargetInfo {
  virtual void anchor();

  TinkerRegisterInfo RegisterInfo;
  TinkerFrameLowering FrameLowering;
  TinkerTargetLowering TLInfo;
  SelectionDAGTargetInfo SDTgtInfo;

public:
  TinkerSubtarget(const Triple &TT, const std::string &CPU,
                  const std::string &FS, const TargetMachine &TM);

  void ParseSubtargetFeatures(StringRef CPU, StringRef TuneCPU, StringRef FS);

  const TinkerFrameLowering *getFrameLowering() const override {
    return &FrameLowering;
  }
  const TinkerRegisterInfo *getRegisterInfo() const override {
    return &RegisterInfo;
  }
  const TinkerTargetLowering *getTargetLowering() const override {
    return &TLInfo;
  }
  const SelectionDAGTargetInfo *getSelectionDAGInfo() const override {
    return &SDTgtInfo;
  }
};

} // namespace llvm
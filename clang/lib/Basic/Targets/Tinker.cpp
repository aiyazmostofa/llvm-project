#include "Tinker.h"

using namespace llvm;
using namespace clang;
using namespace clang::targets;

TinkerTargetInfo::TinkerTargetInfo(const llvm::Triple &Triple,
                                   const TargetOptions &)
    : TargetInfo(Triple) {
  PointerWidth = 64;
  PointerAlign = 8;

  IntWidth = 64;
  IntAlign = 8;

  FloatWidth = 64;
  FloatAlign = 8;
  FloatFormat = &llvm::APFloat::IEEEdouble();

  DoubleWidth = 64;
  DoubleAlign = 8;
  DoubleFormat = &llvm::APFloat::IEEEdouble();

  LongWidth = 64;
  LongAlign = 8;

  LongDoubleWidth = 64;
  LongDoubleAlign = 8;
  LongDoubleFormat = &llvm::APFloat::IEEEdouble();

  LongLongWidth = 64;
  LongLongAlign = 8;

  // Just needed for compilation.
  Int128Align = 8;

  resetDataLayout("e-p:64:8-n64-i64:8-f64:8");
}

void TinkerTargetInfo::getTargetDefines(const LangOptions &Opts,
                                        MacroBuilder &Builder) const {}

llvm::SmallVector<Builtin::InfosShard>
TinkerTargetInfo::getTargetBuiltins() const {
  return {};
}

TinkerTargetInfo::BuiltinVaListKind
TinkerTargetInfo::getBuiltinVaListKind() const {
  return {};
}

bool TinkerTargetInfo::validateAsmConstraint(
    const char *&Name, TargetInfo::ConstraintInfo &info) const {
  return true;
}

std::string_view TinkerTargetInfo::getClobbers() const { return ""; }

ArrayRef<const char *> TinkerTargetInfo::getGCCRegNames() const { return {}; }

ArrayRef<TinkerTargetInfo::GCCRegAlias>
TinkerTargetInfo::getGCCRegAliases() const {
  return {};
}

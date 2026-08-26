#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/TargetOptions.h"
#include "llvm/TargetParser/Triple.h"

namespace clang {
namespace targets {
class TinkerTargetInfo : public TargetInfo {
public:
  TinkerTargetInfo(const llvm::Triple &Triple, const TargetOptions &);

  void getTargetDefines(const LangOptions &Opts,
                        MacroBuilder &Builder) const override;

  llvm::SmallVector<Builtin::InfosShard> getTargetBuiltins() const override;

  BuiltinVaListKind getBuiltinVaListKind() const override;

  bool validateAsmConstraint(const char *&Name,
                             TargetInfo::ConstraintInfo &info) const override;

  std::string_view getClobbers() const override;

  ArrayRef<const char *> getGCCRegNames() const override;

  ArrayRef<GCCRegAlias> getGCCRegAliases() const override;
};
} // namespace targets
} // namespace clang

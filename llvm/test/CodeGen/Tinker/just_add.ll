; RUN: llc < %s -mtriple=tinker | FileCheck %s
define i32 @add(i32 %a, i32 %b) {
entry:
  %sum = add i32 %a, %b
  ret i32 %sum
}
; CHECK: add r0, r1, r2
; CHECK-NEXT: ret

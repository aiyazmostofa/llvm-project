; RUN: llc < %s -mtriple=tinker | FileCheck %s

define i64 @add_i64(i64 %a, i64 %b) {
; CHECK: add r10, r2, r3
; CHECK-NEXT: return
entry:
  %sum = add i64 %a, %b
  ret i64 %sum
}

define i64 @addi_i64(i64 %a) {
; CHECK: addi r2, 1
; CHECK-NEXT: mov r10, r2
; CHECK-NEXT: return
entry:
  %sum = add i64 %a, 1
  ret i64 %sum
}

define i64 @sub_i64(i64 %a, i64 %b) {
; CHECK: sub r10, r2, r3
; CHECK-NEXT: return
entry:
  %sum = sub i64 %a, %b
  ret i64 %sum
}

define i64 @subi_i64(i64 %a) {
; CHECK: subi r2, 1
; CHECK-NEXT: mov r10, r2
; CHECK-NEXT: return
entry:
  %sum = sub i64 %a, 1
  ret i64 %sum
}

define i64 @mul_i64(i64 %a, i64 %b) {
; CHECK: mul r10, r2, r3
; CHECK-NEXT: return
entry:
  %sum = mul i64 %a, %b
  ret i64 %sum
}

define i64 @div_i64(i64 %a, i64 %b) {
; CHECK: div r10, r2, r3
; CHECK-NEXT: return
entry:
  %sum = sdiv i64 %a, %b
  ret i64 %sum
}

define double @add_double(double %a, double %b) {
; CHECK: addf r10, r2, r3
; CHECK-NEXT: return
entry:
  %sum = fadd double %a, %b
  ret double %sum
}

define double @sub_double(double %a, double %b) {
; CHECK: subf r10, r2, r3
; CHECK-NEXT: return
entry:
  %sum = fsub double %a, %b
  ret double %sum
}

define double @mul_double(double %a, double %b) {
; CHECK: mulf r10, r2, r3
; CHECK-NEXT: return
entry:
  %sum = fmul double %a, %b
  ret double %sum
}

define double @div_double(double %a, double %b) {
; CHECK: divf r10, r2, r3
; CHECK-NEXT: return
entry:
  %sum = fdiv double %a, %b
  ret double %sum
}

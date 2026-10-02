; RUN: llc < %s -mtriple=tinker | FileCheck %s

define i64 @add_i64(i64 %a, i64 %b) {
; CHECK: add r0, r1, r2
; CHECK-NEXT: ret
entry:
  %sum = add i64 %a, %b
  ret i64 %sum
}

define i64 @addi_i64(i64 %a) {
; CHECK: mov r0, r1
; CHECK-NEXT: addi r0, 1
; CHECK-NEXT: ret
entry:
  %sum = add i64 %a, 1
  ret i64 %sum
}

define i64 @sub_i64(i64 %a, i64 %b) {
; CHECK: sub r0, r1, r2
; CHECK-NEXT: ret
entry:
  %sum = sub i64 %a, %b
  ret i64 %sum
}

define i64 @subi_i64(i64 %a) {
; CHECK: mov r0, r1
; CHECK-NEXT: subi r0, 1
; CHECK-NEXT: ret
entry:
  %sum = sub i64 %a, 1
  ret i64 %sum
}

define i64 @mul_i64(i64 %a, i64 %b) {
; CHECK: mul r0, r1, r2
; CHECK-NEXT: ret
entry:
  %sum = mul i64 %a, %b
  ret i64 %sum
}

define i64 @div_i64(i64 %a, i64 %b) {
; CHECK: div r0, r1, r2
; CHECK-NEXT: ret
entry:
  %sum = sdiv i64 %a, %b
  ret i64 %sum
}

define double @add_double(double %a, double %b) {
; CHECK: addf r0, r1, r2
; CHECK-NEXT: ret
entry:
  %sum = fadd double %a, %b
  ret double %sum
}

define double @sub_double(double %a, double %b) {
; CHECK: subf r0, r1, r2
; CHECK-NEXT: ret
entry:
  %sum = fsub double %a, %b
  ret double %sum
}

define double @mul_double(double %a, double %b) {
; CHECK: mulf r0, r1, r2
; CHECK-NEXT: ret
entry:
  %sum = fmul double %a, %b
  ret double %sum
}

define double @div_double(double %a, double %b) {
; CHECK: divf r0, r1, r2
; CHECK-NEXT: ret
entry:
  %sum = fdiv double %a, %b
  ret double %sum
}

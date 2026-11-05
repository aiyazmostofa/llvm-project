; RUN: llc < %s -mtriple=tinker | FileCheck %s

define void @jmp() {
; CHECK: ld r2, .LBB0_1
; CHECK-NEXT: br r2
entry:
  br label %loop

loop:
  br label %loop
}

define i64 @if_else(i64 %a, i64 %b) {
; CHECK: sub r4, r0, r2
; CHECK-NEXT: or r2, r4, r2
; CHECK-NEXT: shftri r2, 63
; CHECK-NEXT: xor r2, r2, r1
; CHECK-NEXT: ld r4, .LBB1_2
; CHECK-NEXT: brnz r4, r2
; CHECK-NEXT: ld r2, .LBB1_1
; CHECK-NEXT: br r2
; CHECK: .LBB1_1:
; CHECK-NEXT: addi r3, 1
; CHECK-NEXT: mov r10, r3
; CHECK-NEXT: return
; CHECK: .LBB1_2:
; CHECK-NEXT: subi r3, 1
; CHECK-NEXT: mov r10, r3
; CHECK-NEXT: return
entry:
  %cond = icmp ne i64 %a, 0
  br i1 %cond, label %then, label %else

then:
  %x = add i64 %b, 1
  ret i64 %x

else:
  %y = sub i64 %b, 1
  ret i64 %y
}

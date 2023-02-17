; ModuleID = 'test_instrument.minus200.PGO.bc'
source_filename = "test_instrument.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

$__profc__Z3toyii = comdat nodeduplicate

$__profc_main = comdat nodeduplicate

@__profc__Z3toyii = private global [3 x i64] zeroinitializer, section "__llvm_prf_cnts", comdat, align 8
@__profd__Z3toyii = private global { i64, i64, i64, ptr, ptr, i32, [2 x i16] } { i64 -4308407912059809559, i64 19458807108696, i64 sub (i64 ptrtoint (ptr @__profc__Z3toyii to i64), i64 ptrtoint (ptr @__profd__Z3toyii to i64)), ptr null, ptr null, i32 3, [2 x i16] zeroinitializer }, section "__llvm_prf_data", comdat($__profc__Z3toyii), align 8
@__profc_main = private global [1 x i64] zeroinitializer, section "__llvm_prf_cnts", comdat, align 8
@__profd_main = private global { i64, i64, i64, ptr, ptr, i32, [2 x i16] } { i64 -2624081020897602054, i64 24, i64 sub (i64 ptrtoint (ptr @__profc_main to i64), i64 ptrtoint (ptr @__profd_main to i64)), ptr null, ptr null, i32 1, [2 x i16] zeroinitializer }, section "__llvm_prf_data", comdat($__profc_main), align 8
@__llvm_prf_nm = private constant [23 x i8] c"\0D\15x\DA\8B\8F2.\C9\AF\CC\CCd\CCM\CC\CC\03\00 \F1\04\C1", section "__llvm_prf_names", align 1
@llvm.used = appending global [1 x ptr] [ptr @__llvm_prf_nm], section "llvm.metadata"
@llvm.compiler.used = appending global [2 x ptr] [ptr @__profd__Z3toyii, ptr @__profd_main], section "llvm.metadata"

; Function Attrs: mustprogress nofree noinline norecurse nosync nounwind uwtable
define dso_local noundef i32 @_Z3toyii(i32 noundef %a, i32 noundef %b) local_unnamed_addr #0 {
entry:
  %pgocount = load i64, ptr @__profc__Z3toyii, align 8
  %0 = add i64 %pgocount, 1
  store i64 %0, ptr @__profc__Z3toyii, align 8
  %.promoted = load i64, ptr getelementptr inbounds ([3 x i64], ptr @__profc__Z3toyii, i64 0, i64 1), align 8
  %.promoted12 = load i64, ptr getelementptr inbounds ([3 x i64], ptr @__profc__Z3toyii, i64 0, i64 2), align 8
  br label %for.body

for.cond.cleanup:                                 ; preds = %if.end.2
  %1 = add i32 %b, 236223202
  %2 = add i64 %.promoted, 214748364
  store i64 %2, ptr getelementptr inbounds ([3 x i64], ptr @__profc__Z3toyii, i64 0, i64 1), align 8
  %add3 = add nsw i32 %1, %a.addr.1.2
  ret i32 %add3

for.body:                                         ; preds = %if.end.2, %entry
  %i.015 = phi i32 [ 0, %entry ], [ %inc.2, %if.end.2 ]
  %a.addr.013 = phi i32 [ %a, %entry ], [ %a.addr.1.2, %if.end.2 ]
  %3 = phi i64 [ %.promoted12, %entry ], [ %9, %if.end.2 ]
  %cmp1 = icmp ult i32 %i.015, 214748164
  br i1 %cmp1, label %if.then, label %if.end

if.then:                                          ; preds = %for.body
  %4 = add i64 %3, 1
  store i64 %4, ptr getelementptr inbounds ([3 x i64], ptr @__profc__Z3toyii, i64 0, i64 2), align 8
  %add = add nsw i32 %i.015, %a.addr.013
  br label %if.end

if.end:                                           ; preds = %if.then, %for.body
  %5 = phi i64 [ %4, %if.then ], [ %3, %for.body ]
  %a.addr.1 = phi i32 [ %add, %if.then ], [ %a.addr.013, %for.body ]
  %cmp1.1 = icmp ult i32 %i.015, 214748163
  br i1 %cmp1.1, label %if.then.1, label %if.end.1

if.then.1:                                        ; preds = %if.end
  %inc = add nuw nsw i32 %i.015, 1
  %6 = add i64 %5, 1
  store i64 %6, ptr getelementptr inbounds ([3 x i64], ptr @__profc__Z3toyii, i64 0, i64 2), align 8
  %add.1 = add nsw i32 %inc, %a.addr.1
  br label %if.end.1

if.end.1:                                         ; preds = %if.then.1, %if.end
  %7 = phi i64 [ %6, %if.then.1 ], [ %5, %if.end ]
  %a.addr.1.1 = phi i32 [ %add.1, %if.then.1 ], [ %a.addr.1, %if.end ]
  %cmp1.2 = icmp ult i32 %i.015, 214748162
  br i1 %cmp1.2, label %if.then.2, label %if.end.2

if.then.2:                                        ; preds = %if.end.1
  %inc.1 = add nuw nsw i32 %i.015, 2
  %8 = add i64 %7, 1
  store i64 %8, ptr getelementptr inbounds ([3 x i64], ptr @__profc__Z3toyii, i64 0, i64 2), align 8
  %add.2 = add nsw i32 %inc.1, %a.addr.1.1
  br label %if.end.2

if.end.2:                                         ; preds = %if.then.2, %if.end.1
  %9 = phi i64 [ %8, %if.then.2 ], [ %7, %if.end.1 ]
  %a.addr.1.2 = phi i32 [ %add.2, %if.then.2 ], [ %a.addr.1.1, %if.end.1 ]
  %inc.2 = add nuw nsw i32 %i.015, 3
  %exitcond.not.2 = icmp eq i32 %inc.2, 214748364
  br i1 %exitcond.not.2, label %for.cond.cleanup, label %for.body, !llvm.loop !6
}

; Function Attrs: mustprogress nofree noinline norecurse nosync nounwind uwtable
define dso_local noundef i32 @main() local_unnamed_addr #0 {
entry:
  %pgocount = load i64, ptr @__profc_main, align 8
  %0 = add i64 %pgocount, 1
  store i64 %0, ptr @__profc_main, align 8
  %call = tail call noundef i32 @_Z3toyii(i32 noundef 200, i32 noundef 500)
  ret i32 0
}

attributes #0 = { mustprogress nofree noinline norecurse nosync nounwind uwtable "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 2, !"EnableValueProfiling", i32 0}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"PIE Level", i32 2}
!4 = !{i32 7, !"uwtable", i32 2}
!5 = !{!"clang version 16.0.0 (https://github.com/crispyberry/llvm-project.git cbc378ecb87e3f31dd5aff91f2a621d500640412)"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}

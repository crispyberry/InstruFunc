; ModuleID = 'test_instrument.hack.bc'
source_filename = "test_instrument.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@0 = private unnamed_addr constant [6 x i8] c"entry\00", align 1
@1 = private unnamed_addr constant [9 x i8] c"for.cond\00", align 1
@2 = private unnamed_addr constant [9 x i8] c"for.body\00", align 1
@3 = private unnamed_addr constant [8 x i8] c"if.then\00", align 1
@4 = private unnamed_addr constant [7 x i8] c"if.end\00", align 1
@5 = private unnamed_addr constant [8 x i8] c"for.inc\00", align 1
@6 = private unnamed_addr constant [8 x i8] c"for.end\00", align 1
@7 = private unnamed_addr constant [6 x i8] c"entry\00", align 1

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local noundef i32 @_Z3toyii(i32 noundef %a, i32 noundef %b) #0 {
entry:
  %a.addr = alloca i32, align 4
  %b.addr = alloca i32, align 4
  %i = alloca i32, align 4
  store i32 %a, ptr %a.addr, align 4
  store i32 %b, ptr %b.addr, align 4
  store i32 0, ptr %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, ptr %i, align 4
  %cmp = icmp slt i32 %0, 214748364
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %1 = load i32, ptr %i, align 4
  %cmp1 = icmp slt i32 %1, 200
  br i1 %cmp1, label %if.then, label %if.end

if.then:                                          ; preds = %for.body
  call void @insert_counter(ptr @3)
  %2 = load i32, ptr %i, align 4
  %3 = load i32, ptr %a.addr, align 4
  %add = add nsw i32 %3, %2
  store i32 %add, ptr %a.addr, align 4
  br label %if.end

if.end:                                           ; preds = %if.then, %for.body
  call void @insert_counter(ptr @4)
  %4 = load i32, ptr %i, align 4
  %5 = load i32, ptr %b.addr, align 4
  %add2 = add nsw i32 %5, %4
  store i32 %add2, ptr %b.addr, align 4
  br label %for.inc

for.inc:                                          ; preds = %if.end
  %6 = load i32, ptr %i, align 4
  %inc = add nsw i32 %6, 1
  store i32 %inc, ptr %i, align 4
  br label %for.cond, !llvm.loop !6

for.end:                                          ; preds = %for.cond
  call void @insert_counter(ptr @6)
  %7 = load i32, ptr %a.addr, align 4
  %8 = load i32, ptr %b.addr, align 4
  %add3 = add nsw i32 %7, %8
  ret i32 %add3
}

; Function Attrs: mustprogress noinline norecurse nounwind optnone uwtable
define dso_local noundef i32 @main() #1 {
entry:
  call void @insert_counter(ptr @7)
  %retval = alloca i32, align 4
  %x = alloca i32, align 4
  store i32 0, ptr %retval, align 4
  %call = call noundef i32 @_Z3toyii(i32 noundef 200, i32 noundef 500)
  store i32 %call, ptr %x, align 4
  call void @insert_out()
  ret i32 0
}

declare void @insert_counter(ptr)

declare void @insert_out()

attributes #0 = { mustprogress noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress noinline norecurse nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"clang version 16.0.0 (https://github.com/crispyberry/llvm-project.git cbc378ecb87e3f31dd5aff91f2a621d500640412)"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}

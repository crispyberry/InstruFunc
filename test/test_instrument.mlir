module attributes {dlti.dl_spec = #dlti.dl_spec<#dlti.dl_entry<"dlti.endianness", "little">, #dlti.dl_entry<i64, dense<64> : vector<2xi32>>, #dlti.dl_entry<f80, dense<128> : vector<2xi32>>, #dlti.dl_entry<i1, dense<8> : vector<2xi32>>, #dlti.dl_entry<i8, dense<8> : vector<2xi32>>, #dlti.dl_entry<i16, dense<16> : vector<2xi32>>, #dlti.dl_entry<i32, dense<32> : vector<2xi32>>, #dlti.dl_entry<f16, dense<16> : vector<2xi32>>, #dlti.dl_entry<f64, dense<64> : vector<2xi32>>, #dlti.dl_entry<f128, dense<128> : vector<2xi32>>>, llvm.data_layout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128", llvm.target_triple = "x86_64-unknown-linux-gnu", "polygeist.target-cpu" = "x86-64", "polygeist.target-features" = "+cx8,+fxsr,+mmx,+sse,+sse2,+x87", "polygeist.tune-cpu" = "generic"} {
  func.func @_Z3toyii(%arg0: i32, %arg1: i32) -> i32 attributes {llvm.linkage = #llvm.linkage<external>} {
    %c2147483647 = arith.constant 2147483647 : index
    %c0 = arith.constant 0 : index
    %c1 = arith.constant 1 : index
    %c200_i32 = arith.constant 200 : i32
    %0:2 = scf.for %arg2 = %c0 to %c2147483647 step %c1 iter_args(%arg3 = %arg1, %arg4 = %arg0) -> (i32, i32) {
      %2 = arith.index_cast %arg2 : index to i32
      %3 = arith.cmpi slt, %2, %c200_i32 : i32
      %4 = scf.if %3 -> (i32) {
        %6 = arith.addi %arg4, %2 : i32
        scf.yield %6 : i32
      } else {
        scf.yield %arg4 : i32
      }
      %5 = arith.addi %arg3, %2 : i32
      scf.yield %5, %4 : i32, i32
    }
    %1 = arith.addi %0#1, %0#0 : i32
    return %1 : i32
  }
}

# Have A Try: Dynamic Instrumentation

## ****Prerequisites****

After compiling and installing LLVM 13, the environment needs to have LLVM-related paths.

## The inserted code needs to be compiled as a library

Take inserting a timing function as an example:

In the **libins** fold, we can compile the inserted timing function into a dynamic library:

```bash
gcc inslib.c -I . -shared -fPIC -o libinstrument.so
```

## Build the new pass

`llvm-config` helps us to use flags of LLVM, which means we don't need to recompile the whole LLVM project when compiling a new PASS.

```bash
clang++ -fPIC -c InstruFunc.cpp  -o InstruFunc.o `llvm-config --cxxflags`
clang++ -shared -o InstruFunc.so InstruFunc.o `llvm-config --ldflags`
```

## Test

### Before Instrumentation

Unfortunately, the current method requires at least the instrumentation library to be included in the source code.

```c
//#include "inslib.h" //Need to uncomment.
int M = 100;
int N = 100;
void test(){
  int x = 2;
  int A[M*N];
  for (int i = 0;i < N;i++){
    for(int j = 0;j < M;j++){
      A[i*M+j]+=x;
    }
  }
}
int main()
{
  test();
  return 0;
}
```

### Method1: Using opt and lli (Already OK!)

In the **test** fold:

```bash
clang -S -L ../libins/ -linstrument -emit-llvm -I ../libins test_instrument.c -o test_instrument.ll
opt -load ../InstruFunc.so -instrufunc -enable-new-pm=0 test_instrument.ll -o test_instrument.bc
lli -load ../libins/libinstrument.so test_instrument.bc
```

### Method2: Using Clang -Xclang (Need to be fixed)

In the **test** fold:

```bash
clang -Xclang  -load -Xclang ../InstruFunc.so -L ../libins -linstrument -I ../libins test_instrument.c -o test_instrument
```

```bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(topdir)/InstruFunc/libins
./test_instrument
```
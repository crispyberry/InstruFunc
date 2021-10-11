# 动态插桩WorkFlow

## 1.被插桩代码编辑成库

以插入记时函数为例：

在联想集群上将库放在了/home/wzby/try_pass/libins

头文件：insulin.h

```c
#include "stdio.h"
#include "sys/time.h"
extern long b;
long insert_begin();
void insert_end(char *name, long b);
```

主体：inslib.c

```c
#include "inslib.h"
long insert_begin()
{
  struct timeval star;
  gettimeofday(&star, NULL);
  long b = star.tv_sec * 1000000 + star.tv_usec;
  return b;
}

void insert_end(char *name, long b)
{
  struct timeval end;
  gettimeofday(&end, NULL);
  long e = end.tv_sec * 1000000 + end.tv_usec;
  long t = e - b;
  printf("%s %ld us\n",name, t);
}
```

编译成动态库：

```bash
gcc inslib.c -I . -shared -fPIC -o libinstrument.so
```

## 2.把动态库路径写入环境变量

1.通过ldconfig管理动态库

将动态库路径写入configure

```bash
sudo echo '/home/wzby/try_pass/libins' >> /etc/ld.so.conf
```

2.将动态库的路径添加至环境变量

```bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/wzby/try_pass/libins
```

## 3.编译时调用动态库

1.需要将头文件在测试用例上include进去

测试用例：/home/wzby/try_pass/instrument/test_instrument.c

```c
#include "stdio.h"
#include "sys/time.h"
#include "/home/wzby/try_pass/libins/inslib.h"
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
  //insert_begin();
  test(); 
  //insert_end("main",b);
  return 0;
}

```



2.编译：

```bash
clang -Xclang  -load -Xclang ../../llvm-project/build/lib/LLVMInstruFunc.so -L /home/wzby/try_pass/libins -linstrument test_instrument.c -o test_instrument
```



目前还是因为插不进去callfunc命令导致无法验证动态插桩代码的正确性
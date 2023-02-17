#include "inslib.h"
#define Times 214748364
int toy(int a, int b) {
    for(int i = 0; i < Times; i++){
        if(i < Times - 200){
            a+=i;
        }
        b+=i;
    }
    return a + b;
}

int main(){
    int x = toy(200, 500);
    return 0;
}
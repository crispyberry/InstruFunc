#include "inslib.h"
#define Times1 2147483647
#define Times2 214748364
int toy(int a, int b) {
    for(int i = 0; i < Times2; i++){
        if(i < 200){
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
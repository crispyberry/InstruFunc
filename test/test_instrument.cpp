#define Times1 2147483647
#include "inslib.h"
int toy(int a, int b) {
    for(int i = 0; i < Times1; i++){
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
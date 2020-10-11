#include <stdio.h>

int sum(int * array, int n){
    int i;
    int res = 0;
    for(i = 0; i < n; i++){
        res += array[i];
    }

    return res;
}

#define N 5
int main(){
    int array[N];
    int i;
    for(i = 0; i < N; i++){
        array[i] = i;
    }

    printf("Result: %d\n", sum(array, N));
    return 0;
}
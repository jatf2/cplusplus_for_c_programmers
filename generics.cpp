#include <iostream>
using namespace std;

template <class T>
T sum(T * array, int n){
    T res = 0;
    for(int i = 0; i < n; i++){
        res += array[i];
    }

    return res;
}

int main(){
    const int N = 5;
    int array[N];
    for(int i = 0; i < N; i++){
        array[i] = i;
    }

    cout << "Result: " << sum(array, N) << "\n";

    return 0;
}
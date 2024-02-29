// Problem : 
// code by thanksone
#include <bits/stdc++.h>
#define int long long
#define cpx complex<double>
using namespace std;
const int N = 1 << 19;
const double pi = acos(-1);
array<cpx, 1 << 19> A, B, C, X;
cpx ei(double d){
    return {cos(d), sin(d)};
}
void FFT(array<cpx, 1 << 19> &F){
    cpx x;
    for(int i = 0, k = 0; i < N; i++, k = 0){
        for(int j = 1; j < N; j <<= 1){
            k <<= 1, k |= !!(i & j);
        }
        if(i < k) swap(F[i], F[k]);
    }
    for(int k = 1; k < N; k <<= 1){
        for(int j = 0; j < N; j += k << 1){
            for(int i = j; i < j + k; i++){
                x = X[(i - j) * N / k >> 1] * F[i + k];
                F[i + k] = F[i] - x;
                F[i] += x;
            }
        }
    }
}
int rnd(double x){
    double z = (int)x;
    if(x - z >= 0.5) return (int)z + 1;
    else return (int)z;
}
signed main(){
    int k, n, m, x;
    cin >> k >> n >> m;
    for(int i = 0; i < n; i++){
        cin >> x;
        A[x] += 1;
    }
    for(int i = 0; i < m; i++){
        cin >> x;
        B[x] += 1;
    }
    for(int i = 0; i < N; i++){
        X[i] = ei(2 * pi * i / N);
    }
    FFT(A), FFT(B);
    for(int i = 0; i < N; i++){
        C[i] = A[i] * B[i];
        X[i] = conj(X[i]);
    }
    FFT(C);
    for(int i = 2; i <= k << 1; i++){
        cout << rnd(C[i].real() / (double)N) << " ";
    }
    cout << "\n";
    return 0;

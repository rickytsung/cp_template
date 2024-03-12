// Author : rickytsung
// Problem : 
// Date : 
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
#define i64 long long
#define i128 __int128
#define IOS ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pii pair<int, int>
#define f first
#define s second
#define pb(x) push_back(x)
using namespace std;
mt19937 rng(114514);
const int mod1 = 998244353;
int rnd(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

i64 gcd(i64 a,i64 b){
   if (a%b == 0) return(b);
   else return(gcd(b, a%b));
}

i64 lcm(i64 a, i64 b){
    return a/gcd(a, b) * b;
}

int main() {
    IOS;
    
}

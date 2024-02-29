#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
#define i64 long long
#define i128 __int128
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;

//i128 io template
inline void read(i128 &n){
    i128 x = 0,f = 1;
    char ch = getchar();
    while(ch < '0'||ch > '9'){
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch>='0'&&ch<='9'){
        x = (x<<1)+(x<<3)+(ch^48);
        ch = getchar();
    }
    n = x * f;
}

inline void print(i128 n){
    if(n<0){
        putchar('-');
        n*=-1;
    }
    if(n>9) print(n/10);
    putchar(n % 10 + '0');
}

// fps template by oi wiki
// usage : static poly_t a; ...
// O(nlogn)

//mod (limit : 1048576)
const int mod1 = 469762049; const int mod2 = 998244353; const int mod3 = 1004535809;
//469762049	7 26 3
//998244353	119	23 3 
//1004535809 479 21	3 = 2097152

const int maxn = 524288*2; // 2x
using poly_t = int[maxn];
using poly = int *const;

int rev[maxn];

int qpow(int x, int y, const int mod) {
  int res(1);
  while (y) {
    if (y & 1) res = 1ll * res * x % mod;
    x = 1ll * x * x % mod;
    y >>= 1;
  }
  return res;
}

// opt = -1 -> INTT, else -> NTT
void NTT(int *x, int lim, int opt, const int mod) {
  int i, j, k, m, gn, g, tmp;
  for (i = 0; i < lim; ++i) rev[i] = (i & 1) * (lim >> 1) + (rev[i >> 1] >> 1);
  for (i = 0; i < lim; ++i)
  if (rev[i] < i) swap(x[i], x[rev[i]]);
  for (m = 2; m <= lim; m <<= 1) {
    k = m >> 1;
    gn = qpow(3, (mod - 1) / m, mod);
    for (i = 0; i < lim; i += m) {
      g = 1;
      for (j = 0; j < k; ++j, g = 1ll * g * gn % mod) {
        tmp = 1ll * x[i + j + k] * g % mod;
        x[i + j + k] = (x[i + j] - tmp + mod) % mod;
        x[i + j] = (x[i + j] + tmp) % mod;
      }
    }
  }
  if (opt == -1) {
    reverse(x + 1, x + lim);
    int inv = qpow(lim, mod - 2, mod);
    for (i = 0; i < lim; ++i) x[i] = 1ll * x[i] * inv % mod;
  }
}

void derivative(const poly &h, const int n, poly &f, const int mod) {
  for (int i = 1; i != n; ++i) f[i - 1] = (i64)h[i] * i % mod;
  f[n - 1] = 0;
}

// replace qpow with pre_calcualted mod inverse can be faster
void integrate(const poly &h, const int n, poly &f, const int mod) {
  for (int i = n - 1; i; --i) f[i] = (i64)h[i - 1] * qpow(i, mod-2, mod) % mod;
  f[0] = 0; /* C */
}

//f = 1 / h = f_0 (2 - f_0 h) 
void polyinv(const poly &h, const int n, poly &f, const int mod) {
  static poly_t inv_t;
  std::fill(f, f + n + n, 0);
  f[0] = qpow(h[0], mod - 2, mod);
  for (int t = 2; t <= n; t <<= 1) {
    const int t2 = t << 1;
    std::copy(h, h + t, inv_t);
    std::fill(inv_t + t, inv_t + t2, 0);

    NTT(f, t2, 1, mod);
    NTT(inv_t, t2, 1, mod);
    for (int i = 0; i != t2; ++i)
      f[i] = (i64)f[i] * ((2 + mod - ((i64)f[i] * inv_t[i] % mod)) % mod) % mod;
    NTT(f, t2, -1, mod);

    std::fill(f + t, f + t2, 0);
  }
}

// find ln(F), the constant needs to be 0 , f = ln h = ∫ h' / h dx 
void polyln(const poly &h, const int n, poly &f, const int mod) {
  assert(h[0] == 1);
  static poly_t ln_t;
  const int t = n << 1;
  derivative(h, n, ln_t, mod);
  std::fill(ln_t + n, ln_t + t, 0);
  polyinv(h, n, f, mod);
  NTT(ln_t, t, 1, mod);
  NTT(f, t, 1, mod);
  for (int i = 0; i != t; ++i) ln_t[i] = (i64)ln_t[i] * f[i] % mod;
  NTT(ln_t, t, -1, mod);
    
  integrate(ln_t, n, f, mod);
}

//find e^F, the constant needs to be 1 , f = exp(h) = f_0 (1 - ln f_0 + h)
void polyexp(const poly &h, const int n, poly &f, const int mod) {
  assert(h[0] == 0);
  static poly_t exp_t;
  std::fill(f, f + n + n, 0);
  f[0] = 1;
  for (int t = 2; t <= n; t <<= 1) {
    const int t2 = t << 1;
    polyln(f, t, exp_t, mod);
    exp_t[0] = (mod + ((h[0] + 1) % mod) - exp_t[0]) % mod;
    for (int i = 1; i != t; ++i) exp_t[i] = (mod + h[i] - exp_t[i]) % mod;
    std::fill(exp_t + t, exp_t + t2, 0);

    NTT(f, t2, 1, mod);
    NTT(exp_t, t2, 1, mod);
    for (int i = 0; i != t2; ++i) f[i] = (i64)f[i] * exp_t[i] % mod;
    NTT(f, t2, -1, mod);

    std::fill(f + t, f + t2, 0);
  }
}

// for i64  - 2 int mod, return in i64
// replace qpow for faster speed.
i64 CRT(i64 x, i64 y, const int modx, const int mody){
   return (i64)x + (1ll * (x - y + mody) * qpow(modx, mody-2, mody) % mody) * modx;
}

// CRT 3 int mod, return in a new mod
// replace qpow for faster speed
 
i64 CRT3(i64 x, i64 y, i64 z, const i64 modx, const i64 mody, const i64 modz, const i64 new_mod){
   i64 s = (x + ((y - x + mody) % mody * qpow(modx, mody-2, mody) % mody) * modx);
   return ((z - s % modz + modz) % modz * qpow((int)((modx * mody) % modz), modz-2, modz) % modz * (modx * mody % new_mod) % new_mod + s) % new_mod;
   //return ((s % new_mod) + ((z - (s % modz) + modz) % modz * qpow((int)((modx * mody) % modz), modz-2, modz) % modz * modx % new_mod * mody % new_mod)) % new_mod;
}

int main() {
  
  IOS;
  int n, m, mod, u;
  cin >> n >> m >> mod;
  int lim = 1;
  while(lim <= ((n+m) << 1)){
      lim <<= 1;
  }
  static poly_t a1, b1, a2, b2, a3, b3;
  for(int i = 0; i < n; i++){
      cin >> u;
      a1[i] = a2[i] = a3[i] = u;
  }
  for(int i = 0; i < m; i++){
      cin >> u;
      b1[i] = b2[i] = b3[i] = u;
  }

  NTT(a1, lim, 1, mod1);
  NTT(a2, lim, 1, mod2);
  NTT(a3, lim, 1, mod3);
  NTT(b1, lim, 1, mod1);
  NTT(b2, lim, 1, mod2);
  NTT(b3, lim, 1, mod3);
  for(int i = 0; i < lim; i++){
     a1[i] = 1ll * a1[i] * b1[i] % mod1;
     a2[i] = 1ll * a2[i] * b2[i] % mod2;
     a3[i] = 1ll * a3[i] * b3[i] % mod3;
  }
  NTT(a1, lim, -1, mod1);
  NTT(a2, lim, -1, mod2);
  NTT(a3, lim, -1, mod3);
  for(int i = 0; i <= n + m - 2; i++){
      //cout << a1[i] << ' ' << a2[i] << ' ' << a3[i] << '\n';
      cout << CRT3(a1[i], a2[i], a3[i], mod1, mod2, mod3, mod) << ' ';
  }
}

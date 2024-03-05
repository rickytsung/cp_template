// problem :  https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/description/
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
#define i64 long long
#define i128 __int128
#define pb push_back 
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;

namespace AC {
    // Aho-corasick algorithm template by oi wiki
    // method
    // AC::insert(S) insert a string s
    // AC::build()   build a AC-trie
    // AC::query(S)  query a string s
    // lowercase 
    const int N = 1e6 + 5; // string length sum
    
    int tr[N][26], tot;
    int e[N], fail[N];

    void insert(string s) {
      int u = 0;
      for (int i = 0; i < s.length(); i++) {
        if (!tr[u][s[i] - 'a']) tr[u][s[i] - 'a'] = ++tot;  
        u = tr[u][s[i] - 'a'];                            
      }
      e[u]++; 
    }
    
    queue<int> q;
    
    void build() {
      for (int i = 0; i < 26; i++)
        if (tr[0][i]) q.push(tr[0][i]);
      while (q.size()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
          if (tr[u][i]) {
            fail[tr[u][i]] =
                tr[fail[u]][i]; 
            q.push(tr[u][i]);
          } else
            tr[u][i] = tr[fail[u]][i];
        }
      }
    }
    
    int query(string t) {
      int u = 0, res = 0;
      for (int i = 0; i < t.length(); i++) {
        u = tr[u][t[i] - 'a']; 
        for (int j = u; j && e[j] != -1; j = fail[j]) {
          res += e[j], e[j] = -1;
        }
      }
      return res;
    }
    //namespace AC
}

namespace KMP{
//KMP algorithm
//KMP::find(L,S) find S pos in L (if not return -1)
//KMP::findall(vec,L,S) find all S pos in L (return in vector vec)
    
    //generate the LPS array in O(|S|)
    void LPS(int* arr, const string s){
        const int n = s.length();
        for(int i = 0; i < n; i++) arr[i] = 0;
        int prev = 0, now = 1;
        while(now != n){
            if(s[prev] == s[now]){
                arr[now] = prev + 1;
                now++;
                prev++;
            }
            else if(prev == 0){
                now++;
            }
            else{
                prev = arr[prev-1];
            }
        }
    }
    
    // find S in L in O(|L|+|S|) time
    // if not return -1
    int find(string L, string S) {
        const int n = L.length();
        const int m = S.length();
        int now = 0, prev = 0;
        int lps[m];
        LPS(lps, S);
        while(now != n){
            if(L[now] == S[prev]){
                now++;
                prev++;
            }
            else if(prev == 0){
                now++;
            }
            else{
                prev = lps[prev - 1];
            }
            
            if(prev == m){
                return now - m;
            }        
        }
        return -1;
    }
    
    void findall(vector<int>& V, string L, string S) {
        const int n = L.length();
        const int m = S.length();
        int now = 0, prev = 0;
        int lps[m];
        LPS(lps, S);
        while(now != n){
            if(L[now] == S[prev]){
                now++;
                prev++;
            }
            else if(prev == 0){
                now++;
            }
            else{
                prev = lps[prev - 1];
            }
            
            if(prev == m){
                V.pb(now - m);
                prev = lps[prev - 1];
            }        
        }
    }
    // namespace KMP
}   

namespace SA{
    // Suffix array template by theriseofdavid
    // SA::build(arr, S) return 0-based
    // SA::lcp(arr, sa) *to be added
    const int N = 1048576;
    int sa[N] , rk[N<<1] , oldrk[N<<1] , id[N] , cnt[N] ;
    int n , m , maxn , lenA , lenB;
    
    void build(int* arr, string s){ //build suffix array
        string work = " " + s;
        int i , m , p , w ; 
        n = s.length(); 
        m = max(n , 300); 
        memset(cnt,0,sizeof(cnt)); 
        memset(rk,0,sizeof(rk));
    
        for(i = 1 ; i <= n ; i++) ++cnt[rk[i] = (int)work[i]] ;
        for(i = 1 ; i <= m ; i++) cnt[i] += cnt[i-1] ; 
        for(i = n ; i >= 1 ; i--) sa[cnt[rk[i]]--] = i ;

    
        for(w = 1 ; w < n ; w <<= 1){ 
            memset(cnt,0,sizeof(cnt)); 
            for(i = 1 ; i <= n ; i++) id[i] = sa[i] ;
            for(i = 1 ; i <= n ; i++) ++cnt[rk[id[i]+w]] ;
            for(i = 1 ; i <= m ; i++) cnt[i] += cnt[i-1] ;
            for(i = n ; i >= 1 ; i--) sa[cnt[rk[id[i]+w]]--] = id[i] ;

            memset(cnt, 0 , sizeof(cnt));
            for(i = 1 ; i <= n ; i++) id[i] = sa[i] ;
            for(i = 1 ; i <= n ; i++) ++cnt[rk[id[i]]] ;
            for(i = 1 ; i <= m ; i++) cnt[i] += cnt[i-1] ;
            for(i = n ; i >= 1 ; i--) sa[cnt[rk[id[i]]]--] = id[i] ;

            memcpy(oldrk , rk , sizeof(rk)); 
            for(p = 0 , i = 1 ; i <= n ; i++){ 
                if(oldrk[sa[i]] == oldrk[sa[i-1]] && 
                   oldrk[sa[i] + w] == oldrk[sa[i-1] + w])
                    rk[sa[i]] = p ;
                else
                    rk[sa[i]] = ++p ; 
            }
        }
        for(i = 0; i < n; i++){
            arr[i] = sa[i+1] - 1; // return to 0-based
        }
    }
}

int main(){
    return 0;
}

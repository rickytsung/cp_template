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
    //Aho-corasick algorithm by oi wiki
    
    // AC::insert(S)
    // AC::build()
    // AC::query(S)
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
            V.push_back(now - m);
            prev = lps[prev - 1];
        }        
    }
}
// namespace KMP
}   

int main(){
    int n;
    cin >> n;
    string s;
    while(n--){
        cin >> s;
        AC::insert(s);
    }
    AC::build();
    cin >> s;
    cout << AC::query(s) << '\n';
}

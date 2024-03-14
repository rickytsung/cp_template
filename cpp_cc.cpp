// Author : rickytsung
// Problem : https://cses.fi/problemset/task/1705/
// Date : 2024/3/14
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
#define pp() pop_back()
using namespace std;
mt19937 rng(114514);
const int mod1 = 998244353;
int rnd(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}
int dfs_time = 0;
const int ma = 20, maxn = 200005;
int sp[maxn][ma];
int din[maxn], dout[maxn];
 
namespace CCG{
    int cnt, n, tim;
    vector<vector<int>> E;
    // Warning :　all the returns are in 1 based, so for array size should be n+1
    
    // CCG:SCC(scc_array, graph_2dvector) strongly coneected component
    // CCG:EBCC(bcc_array, graph_2dvector) edge biconnected component
    // CCG:VBCC(bcc_2dvector, graph_2dvector) vertex biconnected component
    // Time Complexity : O(N+M)
    void tarjan_scc(int* scc,vector<vector<int>>& G,int now, vector<int>& st,int* dfs,int* low){
        if(scc[now]) return;
        dfs[now] = low[now] = ++tim;
        st.pb(now);
        for(auto& nxt:G[now]){
            if(!dfs[nxt]){
                tarjan_scc(scc, G, nxt, st, dfs, low);
                low[now] = min(low[now], low[nxt]);
            }
            else if(!scc[nxt]){
                low[now] = min(low[now], dfs[nxt]);
            }
        }
        
        if(low[now] == dfs[now]){
            cnt++;
            int out;
            while(1){
                out = st.back();
                st.pp();
                scc[out] = cnt;
                if(now == out) break;
            }
        }
        
    }
    
    void tarjan_ebcc(int* bcc, vector<vector<int>>& G, int now, int pre, vector<int>& st, int* dfs, int* low){
        if(bcc[now]) return;
        dfs[now] = low[now] = ++tim;
        st.pb(now);
        for(auto& nxt:G[now]){
            if(nxt == pre) continue;
            if(!dfs[nxt]){
                 tarjan_ebcc(bcc, G, nxt, now, st, dfs, low);
                 if(low[nxt] > dfs[now]){
                     int out;
                     cnt++;
                     while(1){
                         out = st.back();
                         st.pp();
                         bcc[out] = cnt;
                         if(out == nxt) break;
                     }
                 }
                 low[now] = min(low[now], low[nxt]);
            }
            else{
                low[now] = min(low[now], dfs[nxt]);
            }
        }
        if(pre == -1){
            int out;
            cnt++;
            while(st.size()){
                out = st.back();
                st.pp();
                bcc[out] = cnt;
            }
        }
    }
    
    void tarjan_vbcc(vector<vector<int>>& bcc, vector<vector<int>>& G, int now, int pre, vector<int>& st, int* dfs, int* low){
        if(dfs[now]) return;
        dfs[now] = low[now] = ++tim;
        st.pb(now);
        for(auto& nxt:G[now]){
            if(nxt == pre) continue;
            if(!dfs[nxt]){
                 tarjan_vbcc(bcc, G, nxt, now, st, dfs, low);
                 if(low[nxt] >= dfs[now]){
                     int out;
                     cnt++;
                     while(1){
                         out = st.back();
                         st.pp();
                         bcc[cnt].pb(out);
                         if(out == nxt) break;
                     }
                     bcc[cnt].pb(now);
                 }
                 low[now] = min(low[now], low[nxt]);
            }
            else{
                low[now] = min(low[now], dfs[nxt]);
            }
        }
    }
    
    void SCC(int* a, vector<vector<int>>& G){
        cnt = tim = 0;
        n = G.size();
        vector<int> st;
        int dfs[n] = {0}, low[n] = {0};
        for(int i = 0; i < n; i++){
            tarjan_scc(a, G, i, st, dfs, low);
        }
    }
    
    void EBCC(int* a, vector<vector<int>>& G){
        cnt = tim = 0;
        n = G.size();
        vector<int> st;
        int dfs[n] = {0}, low[n] = {0};
        for(int i = 0; i < n; i++){
            tarjan_ebcc(a, G, i, -1, st, dfs, low);
        }
    }
    
    void VBCC(vector<vector<int>>& a, vector<vector<int>>& G){
        cnt = tim = 0;
        n = G.size();
        a.resize(n+1);
        vector<int> st;
        int dfs[n] = {0}, low[n] = {0};
        for(int i = 0; i < n; i++){
            tarjan_vbcc(a, G, i, -1, st, dfs, low);
        }
        for(int i = 1; i <= n; i++){
            if(!a[i].size()){
                a.resize(i);
                break;
            }
        }
    }
}; // namespace CCG
 
void findFather(int* pa, vector<vector<int>>& T, int now, int pre){
    if(din[now])return;
    pa[now] = pre;
    din[now] = ++dfs_time;
    for(auto& nxt : T[now]){
        if(nxt == now || nxt == pre) continue;
        findFather(pa, T, nxt, now);
    }
    dout[now] = ++dfs_time;
} 
 
int LCA(int a, int b){
    if(din[a] <= din[b] && dout[a] >= dout[b]) return a;
    if(din[a] >= din[b] && dout[a] <= dout[b]) return b;
    for(int i = ma - 1; i >= 0; i--){
        if(sp[a][i] && !(din[sp[a][i]] <= din[b] && dout[sp[a][i]] >= dout[b])){
            a = sp[a][i];
        }
    }
    return sp[a][0];
}
 
int main() {
    IOS;
    int n, m, q, u, v, w;
    cin >> n >> m >> q;
    vector<vector<int>> G(n+1);
    vector<vector<int>> T(2*n+5);
    for(int i = 0; i < m; i++){
        cin >> u >> v;
        G[u].pb(v);
        G[v].pb(u);
    }
    vector<vector<int>> bcc;
    CCG::VBCC(bcc, G);
    int in[2*n+5] = {0}, id[2*n+5] = {0}, pa[2*n+5] = {0};
    for(int i = 1; i < bcc.size(); i++){
        for(auto& j : bcc[i]){
            in[j]++;
            id[j] = i;
        }
    }
    
    int cnt = bcc.size() - 1;
    
    for(int j = 1; j <= n; j++){
        if(in[j] > 1){
            id[j] = ++cnt;
        }
    }
    
    for(int i = 1; i < bcc.size(); i++){
        for(auto& j : bcc[i]){
            T[i].pb(id[j]);
            T[id[j]].pb(i);
        }
    }
    
    for(int i = 1; i <= n; i++){
        for(auto& j:G[i]){
            if(id[i] != id[j]){
                T[id[i]].pb(id[j]);
                T[id[j]].pb(id[i]);
            }
        }
    }
    
    n = cnt;
    findFather(pa, T, id[1], 0);
    
    for(int i = 0; i <= n; i++){
        sp[i][0] = pa[i];
    }
    
    for(int j = 1; j < ma ;j++){
        for(int i = 1; i <= n; i++){
            sp[i][j] = sp[sp[i][j-1]][j-1];
        }
    }
    
    int nu, nv, nw, nuv;

    while(q--){
        cin >> u >> v >> w;
        nu = id[u];
        nv = id[v];
        nw = id[w];
        if(u == w || v == w){
            cout << "NO\n";
        }
        else if(in[w] == 1){
            cout << "YES\n";
        }
        else{
            if(LCA(nu, nw) == nw || LCA(nv, nw) == nw ){
                nuv = LCA(nu, nv);
                if(din[nw] >= din[nuv] && dout[nw] <= dout[nuv]){
                    cout << "NO\n";
                }
                else{
                    cout << "YES\n";
                }
            }
            else{
              cout << "YES\n"; 
            }
        }
    }
}

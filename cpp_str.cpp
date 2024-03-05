// problem :  https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/description/
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
#define i64 long long
#define i128 __int128
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;

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
int KMP(string L, string S) {
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

int strStr(string haystack, string needle) {
    return KMP(haystack, needle);
}
    
int main(){
    string s = "sadbutsad";
    string t = "sad";
    cout << strStr(s,t) << '\n';
    return 0;
}

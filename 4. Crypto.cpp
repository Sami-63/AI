#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

string s1, s2, sum;
int ok;
vector<char>a;
int vis[10];//, val[26];
map<char, int>mp;

void check(){
    int num1 = 0, num2 = 0, numsum = 0;

    for(auto c : s1){
        num1 *= 10;
        if(c != '#')num1 += mp[c];
    }

    for(auto c : s2){
        num2 *= 10;
        if(c != '#')num2 += mp[c];
    }

    for(auto c : sum){
        numsum *= 10;
        if(c != '#')numsum += mp[c];
    }

    ok = (num1 + num2) == numsum;
}

void f(int id)
{
    if(id == a.size()){
        check();
        return;
    }

    for( int i=0 ; i<10 ; i++ ){
        if(vis[i])continue;

        vis[i] = 1;
        mp[a[id]] = i;
        f(id + 1);

        if(ok)return;
        vis[i] = 0;
    }
}

int32_t main() 
{
    // Simple is BEAST
    
    // cin >> s1 >> s2 >> sum;

    s1 = "two";s2 = "two";sum = "four";
    // s1 = "to";s2 = "go";sum = "out";
    // s1 = "send";s2 = "more";sum = "money";
    // s1 = "eat";s2 = "that";sum = "apple";
    // s1 = "three";s2 = "three";sum = "six";


    int mx = max({s1.size(), s2.size(), sum.size()});
    while(s1.size() != mx)s1 = "#" + s1;
    while(s2.size() != mx)s2 = "#" + s2;
    while(sum.size() != mx)sum = "#" + sum;

    // print(s1, s2, sum);
    set<char>st;
    for(auto c : s1)st.insert(c);
    for(auto c : s2)st.insert(c);
    for(auto c : sum)st.insert(c);
    for(auto c : st)a.push_back(c);

    f(0);

    if(!ok){
        cout << "impossible" << endl;
        return 0;
    }

    for(auto c : s1)if(c != '#') cout << mp[c];else cout << ' '; cout << endl;
    for(auto c : s2)if(c != '#') cout << mp[c];else cout << ' '; cout << endl;
    for(auto c : sum)if(c != '#') cout << mp[c];else cout << ' '; cout << endl;
        
    return 0;
}

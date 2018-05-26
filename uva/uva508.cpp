#include <iostream>
#include <algorithm>
#include <map>
#include <string>
using namespace std;

int num;
string words[105], bigDict[105];
map <char, string> dict;

void readDict()
{
    string key, value;
    cin >> key;
    while(key[0] != '*') {
        cin >> value;
        dict[key[0]] = value;
        cin >> key;
    }
}

void buildBigDict()
{
    while(cin >> words[num++])
    {
        if(words[num-1][0] == '*') break;
        for(int i = 0; i < words[num-1].size(); i++)
            bigDict[num-1] += dict[words[num-1][i]];
    }
    num--;
}

int cmp(string s, string t)
{
    if(s.size() < t.size()) swap(s, t);
    if(s.substr(0, t.size()) == t) 
        return s.size()-t.size();
    else
        return -1;
}

void solve()
{
    string codes;
    while(cin >> codes)
    {
        if(codes[0] == '*') return;
        int pos = -1, status = 1<<25, PRINT = 1;
        for(int i = 0; i < num; i++)
        {
            int t = cmp(codes, bigDict[i]);
            if(t < 0) continue;
            if(!(t+status)) {
                cout << words[pos]+"!" << endl;
                PRINT = 0;
                break;
            }
            if(t < status) status = t, pos = i;
        }
        if(PRINT && pos >= 0) cout << words[pos]+(status?"?":"") << endl;
    }
}

int main()
{
    readDict();
    buildBigDict();
    solve();
    return 0;
}
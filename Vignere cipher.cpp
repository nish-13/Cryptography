#include<bits/stdc++.h>
using namespace std;

string generateKey(string s,string key){
    int l=s.size();
    int k=key.size();
    if(l>key.size()){
        for(int i=k;i<l;i++){
            key.push_back(key[i%k]);
        }
    }
    return key;
}

string encrypt(string s,string key){
    string cipher;
    for(int i=0;i<s.size();i++){
        char x=(s[i]+key[i])%26;
        x+='A';
        cipher.push_back(x);
    }
    return cipher;
}

string decrypt(string s,string key){
    string og;
    for(int i=0;i<s.size();i++){
        char x=(s[i]-key[i]+26)%26;
        x+='A';
        og.push_back(x);
    }
    return og;
}

int main(){
    string s="CRYPTOGRAPHY";
    string key="NISHTHA";
    key=generateKey(s,key);
    cout<<key<<"\n";
    s=encrypt(s,key);
    cout<<s<<"\n";
    s=decrypt(s,key);
    cout<<s;
    return 0;
}
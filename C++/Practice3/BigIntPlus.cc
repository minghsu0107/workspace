#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

string BigNumPlus(string &s1,string &s2){

    string res="";
    string max=(s1.length()>s2.length())? s1:s2;
    if(max==s2){
        s2=s1;
        s1=max;
    }
    vector<int> mat;
    for(int i=0;i<s2.length();i++){
       mat.push_back((s1[s1.length()-1-i]-'0')+(s2[s2.length()-1-i]-'0'));
    }
    for(int i=s1.length()-s2.length()-1;i>=0;i--){
       mat.push_back(s1[i]-'0'); 
    }
    
    int addflag=0;
    for(int i=0;i<mat.size();i++){
        int temp=mat[i]+addflag;
        mat[i]=temp%10;
        addflag=temp/10;
    }
   
    while(addflag!=0){
        int t=addflag%10;
        mat.push_back(t);
        addflag/=10;
    }
    for(int i=0;i<mat.size();i++){
        ostringstream ss;
        ss<<mat[i];
        res=ss.str()+res;
    }
    return res;
}
int main(){
    string str1,str2;
    while(cin>>str1>>str2)
    {   
        cout<<BigNumPlus(str1,str2)<<endl;
    }
}
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

string BigNumMultiply(string &s1,string &s2){

    string res="";
    vector<int> vec(s1.length()+s2.length()-1,0);
    for(int i=0;i<s1.length();++i){
        for(int j=0;j<s2.length();++j){
            vec[i+j]+=(s1[i]-'0')*(s2[j]-'0');
        }
    }
    vector<int> mat;
    for(int i=0;i<vec.size();i++){
        mat.push_back(vec[vec.size()-i-1]);
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
        cout<<BigNumMultiply(str1,str2)<<endl;
    }
}
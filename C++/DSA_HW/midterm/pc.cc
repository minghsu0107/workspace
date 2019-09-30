#include <bits/stdc++.h>
using namespace std;
namespace IO {
        #define BUF_SIZE 5000010
        #define OUT_SIZE 5000010
        #define ll long long
        //fread->read
        bool IOerror=0;
        inline char nc(){
            static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
            if (p1==pend){
                p1=buf; pend=buf+fread(buf,1,BUF_SIZE,stdin);
                if (pend==p1){IOerror=1;return -1;}
            }
            return *p1++;
        }
        inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';}
        inline void read(int &x){
            bool sign=0; char ch=nc(); x=0;
            for (;blank(ch);ch=nc());
            if (IOerror)return;
            if (ch=='-')sign=1,ch=nc();
            for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
            if (sign)x=-x;
        }
        inline void read(ll &x){
            bool sign=0; char ch=nc(); x=0;
            for (;blank(ch);ch=nc());
            if (IOerror)return;
            if (ch=='-')sign=1,ch=nc();
            for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
            if (sign)x=-x;
        }
        inline void read(double &x){
            bool sign=0; char ch=nc(); x=0;
            for (;blank(ch);ch=nc());
            if (IOerror)return;
            if (ch=='-')sign=1,ch=nc();
            for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
            if (ch=='.'){
                double tmp=1; ch=nc();
                for (;ch>='0'&&ch<='9';ch=nc())tmp/=10.0,x+=tmp*(ch-'0');
            }
            if (sign)x=-x;
        }
        inline void read(char *s){
            char ch=nc();
            for (;blank(ch);ch=nc());
            if (IOerror)return;
            for (;!blank(ch)&&!IOerror;ch=nc())*s++=ch;
            *s=0;
        }
        inline void read(char &c){
            for (c=nc();blank(c);c=nc());
            if (IOerror){c=-1;return;}
        }
        //fwrite->write
        struct Ostream_fwrite{
            char *buf,*p1,*pend;
            Ostream_fwrite(){buf=new char[BUF_SIZE];p1=buf;pend=buf+BUF_SIZE;}
            void out(char ch){
                if (p1==pend){
                    fwrite(buf,1,BUF_SIZE,stdout);p1=buf;
                }
                *p1++=ch;
            }
            void print(int x){
                static char s[15],*s1;s1=s;
                if (!x)*s1++='0';if (x<0)out('-'),x=-x;
                while(x)*s1++=x%10+'0',x/=10;
                while(s1--!=s)out(*s1);
            }
            void println(int x){
                static char s[15],*s1;s1=s;
                if (!x)*s1++='0';if (x<0)out('-'),x=-x;
                while(x)*s1++=x%10+'0',x/=10;
                while(s1--!=s)out(*s1); out('\n');
            }
            void print(ll x){
                static char s[25],*s1;s1=s;
                if (!x)*s1++='0';if (x<0)out('-'),x=-x;
                while(x)*s1++=x%10+'0',x/=10;
                while(s1--!=s)out(*s1);
            }
            void println(ll x){
                static char s[25],*s1;s1=s;
                if (!x)*s1++='0';if (x<0)out('-'),x=-x;
                while(x)*s1++=x%10+'0',x/=10;
                while(s1--!=s)out(*s1); out('\n');
            }
            void print(double x,int y){
                static ll mul[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,
                    1000000000,10000000000LL,100000000000LL,1000000000000LL,10000000000000LL,
                    100000000000000LL,1000000000000000LL,10000000000000000LL,100000000000000000LL};
                if (x<-1e-12)out('-'),x=-x;x*=mul[y];
                ll x1=(ll)floor(x); if (x-floor(x)>=0.5)++x1;
                ll x2=x1/mul[y],x3=x1-x2*mul[y]; print(x2);
                if (y>0){out('.'); for (size_t i=1;i<y&&x3*mul[i]<mul[y];out('0'),++i); print(x3);}
            }
            void println(double x,int y){print(x,y);out('\n');}
            void print(char *s){while (*s)out(*s++);}
            void println(char *s){while (*s)out(*s++);out('\n');}
            void flush(){if (p1!=buf){fwrite(buf,1,p1-buf,stdout);p1=buf;}}
            ~Ostream_fwrite(){flush();}
        }Ostream;
        inline void print(int x){Ostream.print(x);}
        inline void println(int x){Ostream.println(x);}
        inline void print(char x){Ostream.out(x);}
        inline void println(char x){Ostream.out(x);Ostream.out('\n');}
        inline void print(ll x){Ostream.print(x);}
        inline void println(ll x){Ostream.println(x);}
        inline void print(double x,int y){Ostream.print(x,y);}
        inline void println(double x,int y){Ostream.println(x,y);}
        inline void print(char *s){Ostream.print(s);}
        inline void println(char *s){Ostream.println(s);}
        inline void println(){Ostream.out('\n');}
        inline void flush(){Ostream.flush();}
        #undef ll
        #undef OUT_SIZE
        #undef BUF_SIZE
};
using namespace IO;
char s[1000005];
int l[1000005]; // cost of changing to left parenthesis
int r[1000005]; // cost of changing to right parenthesis
int t;
int main() {
    read(t);
    while(t--) {
        int flag = 1;
        priority_queue<int> q;
        long long sum = 0;
        read(s);
        int len = strlen(s);
        for (int i = 0; i < len; ++i) {
            if (s[i] == '?') {
                read(l[i]);
                read(r[i]);
                sum += r[i];
                // change all ? to )
                // record the overall cost of changing ? to (     
            }
        }
        int res = 0;
        for (int i = 0; i < len; ++i) {
            if (s[i] == '(') res++;
            else res--;
            // record the change 
            if (s[i] == '?') q.push(r[i]-l[i]);
            if (res < 0) {
                if(q.empty()){
                    flag = 0;
                    break;
                }
                //如果q中有元素，証明此前有？可以换成（
                else {
                    // update cost: sum=sum-r[i]+l[i];
                    sum -= q.top();
                    q.pop();
                    // 之前?時res--, 現在變成(, res = res+1+1
                    res += 2;
                }
            }
        }
        // at the end, the parentheses are illegal
        if(res) flag = 0;
        if(flag)
            printf("%lld\n", sum);
        else puts("-1");
    }
}
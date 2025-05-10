//bigint
#ifndef BIGINT
#define BIGINT
#define BASE 100ll//Due to the precision issues of FFT,more aggressive digit compression cannot be performed.
#include<cstdio>
#include<cstring>
#include<string>
#include"my_algorithm.hpp"
template<const unsigned Size>
class bigint{
private:
    unsigned len;
    int num[Size];
    void init(){
        memset(num,0,sizeof(num));
        len=1;
    }
    bool abs_greater_equal(const bigint &a)const{
        if(len!=a.len)
            return len>a.len;
        for(int i=len;i;i--)
            if(num[i]!=a.num[i])
                return num[i]>a.num[i];
        return 1;
    }
public:
    bigint(){
        init();
    }
    void get_num(std::string s){
        init();
        int f=0;
        unsigned slen=s.length();
        if(s[0]=='-')
            num[0]=f=1;
        len=0;
        unsigned temp=0,w=1;
        for(int i=slen-1;i>=f;i--){
            temp+=(s[i]^48)*w;
            w=(w<<1)+(w<<3);
            if(w==BASE||i==f){
                num[++len]=(int)temp;
                temp=0;
                w=1;
            }
        }
        if(temp||len==0)
            num[++len]=temp;
    }
    bool operator<(const bigint &a)const{
        if(num[0]&&!a.num[0])
            return 1;
        if(!num[0]&&a.num[0])
            return 0;
        if(num[0]){
            if(len!=a.len)
                return len>a.len;
            for(int i=len;i;i--)
                if(num[i]!=a.num[i])
                    return num[i]>a.num[i];
        }
        else{
            if(len!=a.len)
                return len<a.len;
            for(int i=len;i;i--)
                if(num[i]!=a.num[i])
                    return num[i]<a.num[i];
        }
        return 0;
    }
    bigint operator+(const bigint &a)const{
        bigint res;
        if(num[0]==a.num[0]){
            ll temp=0;
            res.len=Max(len,a.len);
            for(unsigned i=1;i<=res.len;i++){
                ll sum=temp;
                if(i<=len)
                    sum+=num[i];
                if(i<=a.len)
                    sum+=a.num[i];
                res.num[i]=(int)(sum%BASE);
                temp=sum/BASE;
            }
            if(temp)
                res.num[++res.len]=temp;
            res.num[0]=num[0];
        }
        else{
            bool this_large=abs_greater_equal(a);
            const bigint &larger=this_large?*this:a;
            const bigint &smaller=this_large?a:*this;
            res.len=larger.len;
            ll temp=0;
            for(unsigned i=1;i<=res.len;i++){
                ll diff=(ll)larger.num[i]-temp;
                if(i<=smaller.len)
                    diff-=smaller.num[i];
                if(diff<0){
                    diff+=BASE;
                    temp=1;
                }
                else
                    temp=0;
                res.num[i]=diff;
            }
            while(res.len>1&&res.num[res.len]==0)
                res.len--;
            if(this_large)
                res.num[0]=num[0];
            else
                res.num[0]=a.num[0];
            if(res.len==1&&res.num[1]==0)
                res.num[0]=0;
        }
        return res;
    }
    bigint operator*(const bigint &a)const{
        bigint res;
        if((len==1&&num[1]==0)||(a.len==1&&a.num[1]==0))
            return res;
        res.num[0]=num[0]^a.num[0];
        unsigned len_sum=1;
        while(len_sum<len+a.len)
            len_sum<<=1;
        comp *fa=new comp[len_sum]();
        comp *fb=new comp[len_sum]();
        for(unsigned i=0;i<len;i++)
            fa[i]={(double)num[i+1],0};
        for(unsigned i=0;i<a.len;i++)
            fb[i]={(double)a.num[i+1],0};
        fft(fa,len_sum,1);
        fft(fb,len_sum,1);
        for(unsigned i=0;i<len_sum;i++)
            fa[i]=fa[i]*fb[i];
        fft(fa,len_sum,-1);
        res.len=len+a.len;
        ll temp=0;
        for(unsigned i=0;i<res.len;i++){
            ll val=(ll)(fa[i].real+0.5)+temp;
            res.num[i+1]=(int)(val%BASE);
            temp=val/BASE;
        }
        if(temp)
            res.num[++res.len]=temp;
        while(res.len>1&&res.num[res.len]==0)
            res.len--;
        return res;
    }
    void read(){
        init();
        std::string s;
        char ch=getchar();
        while(ch<'0'||ch>'9'){
            if(ch=='-')
                s.push_back('-');
            ch=getchar();
        }
        while(ch>='0'&&ch<='9'){
            s.push_back(ch);
            ch=getchar();
        }
        get_num(s);
    }
    void print(){
        if(num[0])
            putchar('-');
        bool leading_zero=1;
        for(int i=len;i;i--){
            if(leading_zero)
                printf("%d",num[i]);
            else
                printf("%02d",num[i]);
            leading_zero=0;
        }
        putchar('\n');
        return;
    }
};
#undef BASE
#endif
//bigint
#ifndef BIGINT
#define BIGINT
#define BASE 100ll
//Due to the precision issues of FFT,more aggressive digit compression cannot be performed.
#include<iostream>
#include<cstring>
#include<iomanip>
#include"my_algorithm.hpp"//Provide FFT
template<const unsigned Size>
class bigint{
private:
    unsigned len;
    int num[Size];
    inline void init(){
        memset(num,0,sizeof(num));
        len=1;
    }
public:
    bigint(){
        init();
    }
    friend std::ostream &operator<<(std::ostream &out,const bigint &x){
        if(x.num[0])
            out<<'-';
        out<<x.num[x.len];
        for(int i=x.len-1;i;i--)
            out<<std::setw(2)<<std::setfill('0')<<x.num[i];
        return out;
    }
    friend std::istream &operator>>(std::istream &in,bigint &x){
        std::string s;
        in>>s;
        x=s;
        return in;
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
    template<typename T>
    bigint &operator=(const T &a){
        T x=a;
        if(x<0)
            num[0]=1,x=~x+1;
        len=0;
        while(x){
            num[++len]=x%BASE;
            x/=BASE;
        }
        return *this;
    }
    bigint &operator=(const std::string &a);
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
    bool operator>(const bigint &a)const{
        if(num[0]&&!a.num[0])
            return 0;
        if(!num[0]&&a.num[0])
            return 1;
        if(num[0]){
            if(len!=a.len)
                return len<a.len;
            for(int i=len;i;i--)
                if(num[i]!=a.num[i])
                    return num[i]<a.num[i];
        }
        else{
            if(len!=a.len)
                return len>a.len;
            for(int i=len;i;i--)
                if(num[i]!=a.num[i])
                    return num[i]>a.num[i];
        }
        return 0;
    }
    bool operator<=(const bigint &a)const{
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
        return 1;
    }
    bool operator>=(const bigint &a)const{
        if(num[0]&&!a.num[0])
            return 0;
        if(!num[0]&&a.num[0])
            return 1;
        if(num[0]){
            if(len!=a.len)
                return len<a.len;
            for(int i=len;i;i--)
                if(num[i]!=a.num[i])
                    return num[i]<a.num[i];
        }
        else{
            if(len!=a.len)
                return len>a.len;
            for(int i=len;i;i--)
                if(num[i]!=a.num[i])
                    return num[i]>a.num[i];
        }
        return 1;
    }
    bool operator==(const bigint &a)const{
        if(len!=a.len||num[0]!=a.num[0])
            return 0;
        for(unsigned i=1;i<=len;i++)
            if(num[i]!=a.num[i])
                return 0;
        return 1;
    }
    bool operator!=(const bigint &a)const{
        if(len!=a.len||num[0]!=a.num[0])
            return 1;
        for(unsigned i=1;i<=len;i++)
            if(num[i]!=a.num[i])
                return 1;
        return 0;
    }
    bigint &operator+=(const bigint &a){
        if(num[0]==a.num[0]){
            ll temp=0;
            unsigned old_len=len;
            len=Max(len,a.len);
            for(unsigned i=1;i<=len;i++){
                ll sum=temp;
                if(i<=old_len)
                    sum+=num[i];
                if(i<=a.len)
                    sum+=a.num[i];
                num[i]=(int)(sum%BASE);
                temp=sum/BASE;
            }
            if(temp)
                num[++len]=temp;
        }
        else{
            bool this_large=this->abs()>=a.abs();
            const bigint &larger=this_large?*this:a;
            const bigint &smaller=this_large?a:*this;
            unsigned new_len=larger.len;
            ll temp=0;
            for(unsigned i=1;i<=new_len;i++){
                ll diff=(ll)larger.num[i]-temp;
                if(i<=smaller.len)
                    diff-=smaller.num[i];
                if(diff<0){
                    diff+=BASE;
                    temp=1;
                }
                else
                    temp=0;
                num[i]=diff;
            }
            len=new_len;
            while(len>1&&num[len]==0)
                len--;
            num[0]=this_large?num[0]:a.num[0];
            if(len==1&&num[1]==0)
                num[0]=0;
        }
        return *this;
    }
    bigint &operator-=(const bigint &a){
        bigint temp=a;
        temp.num[0]^=1;
        return *this+=temp;
    }
    bigint &operator*=(const bigint &a){
        if((len==1&&num[1]==0)||(a.len==1&&a.num[1]==0)){
            init();
            return *this;
        }
        unsigned old_len=len;
        int old_num[Size];
        memcpy(old_num,num,sizeof(num));
        init();
        num[0]=old_num[0]^a.num[0];
        unsigned len_sum=1;
        while(len_sum<old_len+a.len)
            len_sum<<=1;
        comp fa[2*Size]={};
        comp fb[2*Size]={};
        for(unsigned i=0;i<old_len;i++)
            fa[i]={(double)old_num[i+1],0};
        for(unsigned i=0;i<a.len;i++)
            fb[i]={(double)a.num[i+1],0};
        fft(fa,len_sum,1);
        fft(fb,len_sum,1);
        for(unsigned i=0;i<len_sum;i++)
            fa[i]=fa[i]*fb[i];
        fft(fa,len_sum,-1);
        len=old_len+a.len;
        ll temp=0;
        for(unsigned i=0;i<len;i++){
            ll val=(ll)round(fa[i].real)+temp;
            num[i+1]=(int)(val%BASE);
            temp=val/BASE;
        }
        if(temp)
            num[++len]=temp;
        while(len>1&&num[len]==0)
            len--;
        return *this;
    }
    friend bigint operator+(const bigint &a,const bigint &b){
        return bigint(a)+=b;
    }
    friend bigint operator-(const bigint &a,const bigint &b){
        return bigint(a)-=b;
    }
    friend bigint operator*(const bigint &a,const bigint &b){
        return bigint(a)*=b;
    }
    bigint abs()const{
        bigint res=*this;
        res.num[0]=0;
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
        return;
    }
};
template<const unsigned Size>
bigint<Size> &bigint<Size>::operator=(const std::string &a){
    init();
    int f=0;
    unsigned slen=a.length();
    if(slen>0&&a[0]=='-')
        num[0]=f=1;
    len=0;
    unsigned temp=0,w=1;
    for(int i=slen-1;i>=f;i--){
        temp+=(a[i]^48)*w;
        w=(w<<1)+(w<<3);
        if(w==BASE||i==f){
            num[++len]=(int)temp;
            temp=0;
            w=1;
        }
    }
    if(temp||len==0)
        num[++len]=temp;
    return *this;
}
#undef BASE
#endif

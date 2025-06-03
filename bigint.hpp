//bigint
#ifndef BIGINT
#define BIGINT
#define BASE 100ll
//Due to the precision issues of FFT,more aggressive digit compression cannot be performed.
#include<iostream>
#include<cstring>
#include<iomanip>
#include<cmath>
typedef long long ll;
namespace __FFT{
    constexpr double PI2=6.283185307179586231995927;
    struct comp{
        double real,imag;
        comp(double real=0,double imag=0):real(real),imag(imag){}
        comp operator+(const comp &x)const{
            return comp(real+x.real,imag+x.imag);
        }
        comp operator-(const comp &x)const{
            return comp(real-x.real,imag-x.imag);
        }
        comp operator*(const comp &x)const{
            return comp(real*x.real-imag*x.imag,real*x.imag+x.real*imag);
        }
    };
    inline void fft(comp *f,unsigned n,int rev){
        for(unsigned i=1,j=n>>1;i<n-1;i++){
            if(i<j)
                std::swap(f[i],f[j]);
            unsigned k=n>>1;
            while(j>=k){
                j-=k;
                k>>=1;
            }
            j+=k;
        }
        for(unsigned l=2;l<=n;l<<=1){
            double arg=PI2*rev/l;
            comp wn(cos(arg),sin(arg));
            for(unsigned i=0;i<n;i+=l){
                comp w(1,0);
                for(unsigned j=0;j<(l>>1);j++){
                    comp f1=f[i+j],f2=f[i+j+(l>>1)]*w;
                    f[i+j]=f1+f2;
                    f[i+j+(l>>1)]=f1-f2;
                    w=w*wn;
                }
            }
        }
        if(!~rev)
            for(unsigned i=0;i<n;i++)
                f[i].real/=n;
        return;
    }
}
template<const unsigned Size>
class bigint{
private:
    unsigned len;
    int num[Size];
    inline void init(){
        memset(num,0,sizeof(int)*(len+2));
        len=1;
    }
public:
    bigint(){
        init();
    }
    template<typename T>
    bigint(const T &x){
        *this=x;
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
    template<typename T>
    bigint &operator=(const T &a){
        init();
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
            len=std::max(len,a.len);
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
        using namespace __FFT;
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
    bigint &operator++(){
        *this+=bigint(1);
        return *this;
    }
    bigint &operator--(){
        *this-=1;
        return *this;
    }
    template<typename T>
    bigint operator++(T){
        bigint res=*this;
        ++*this;
        return res;
    }
    template<typename T>
    bigint operator--(T){
        bigint res=*this;
        --*this;
        return res;
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

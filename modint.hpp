//modint
#ifndef MODINT
#define MODINT
template<unsigned m>
class modint{
private:
    unsigned _v;
public:
    modint():_v(0){}
    unsigned int val()const{
        return _v;
    }
    template<typename T>
    modint(T v){
        long long x=v%m;
        if(x<0)
            x+=m;
        _v=(unsigned)x;
    }
    modint &operator++(){
        _v++;
        if(_v==m)
            _v=0;
        return *this;
    }
    modint &operator--(){
        if(_v==0)
            _v=m;
        _v--;
        return *this;
    }
    modint operator++(int){
        modint res=*this;
        ++*this;
        return res;
    }
    modint operator--(int){
        modint res=*this;
        --*this;
        return res;
    }
    modint &operator+=(const modint &x){
        _v+=x._v;
        if(_v>=m)
            _v-=m;
        return *this;
    }
    modint &operator-=(const modint &x){
        _v+=m-x._v;
        if(_v>=m)
            _v-=m;
        return *this;
    }
    modint &operator*=(const modint &x){
        unsigned long long res=_v;
        res*=x._v;
        _v=(unsigned)(res%m);
        return *this;
    }
    modint &operator/=(const modint &x){
        return *this*=x.inv();
    }
    modint pow(long long n)const{
        modint a=*this,res=1;
        while(n){
            if(n&1)
                res*=a;
            a*=a;
            n>>=1;
        }
        return res;
    }
    modint inv()const{
        return pow(m-2);
    }
    friend modint operator+(const modint &a,const modint &b){
        return modint(a)+=b;
    }
    friend modint operator-(const modint &a,const modint &b){
        return modint(a)-=b;
    }
    friend modint operator*(const modint &a,const modint &b){
        return modint(a)*=b;
    }
    friend modint operator/(const modint &a,const modint &b){
        return modint(a)/=b;
    }
    friend bool operator==(const modint &a,const modint &b){
        return a._v==b._v;
    }
    friend bool operator!=(const modint &a,const modint &b){
        return a._v!=b._v;
    }
};
typedef modint<998244353> modint998244353;
typedef modint<1000000007> modint1000000007;
#endif

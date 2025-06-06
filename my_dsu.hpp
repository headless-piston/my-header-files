//disjoint_set_union
#ifndef MY_DSU
#define MY_DSU
template<const unsigned siz_of_set>
class dsu{
private:
    unsigned fa[siz_of_set+1],siz[siz_of_set+1];
public:
    dsu(){
        for(unsigned i=1;i<=siz_of_set;i++)
            fa[i]=i,siz[i]=1;
        return;
    }
    unsigned find(unsigned x){
        if(fa[x]==x)
            return x;
        return fa[x]=find(fa[x]);
    }
    void merge(unsigned x,unsigned y){
        x=find(x),y=find(y);
        if(x==y)
            return;
        if(siz[y]<siz[x])
            x^=y^=x^=y;//swap(x,y)
        fa[x]=y;
        siz[y]+=siz[x];
        return;
    }
    unsigned size(unsigned x){
        x=find(x);
        return siz[x];
    }
};
#endif

//red black tree
#ifndef RED_BLACK_TREE
#define RED_BLACK_TREE
#include<vector>
#include<cassert>
//define color enumeration
enum class Color {RED,BLACK};
template<typename Key,typename Val,const unsigned Size>
class RBTree{
private:
    struct node{
        Key key;
        Val val;
        Color color;
        node *ls,*rs,*pt;//left/right son,parent
        node():color(Color::BLACK),ls(nullptr),rs(nullptr),pt(nullptr){}
        node(Key k,Val v):key(k),val(v),color(Color::RED),ls(nullptr),rs(nullptr),pt(nullptr){}
    };
    node tree[Size+1];
    node* root;
    node* NIL;//sentinel node,represents null
    std::vector<node*> free_list;//free node list
    void init_NIL(){
        NIL=&tree[0];
        NIL->key=Key();
        NIL->val=Val();
        NIL->color=Color::BLACK;//sentinel is black
        NIL->ls=NIL->rs=NIL->pt=NIL;
        root=NIL;
        free_list.clear();
        for(unsigned i=1;i<=Size;i++)
            free_list.push_back(tree+i);
        return;
    }
    node* new_node(Key k,Val v){
        assert(!free_list.empty());//node array is full
        node* u=free_list.back();//take last free index
        free_list.pop_back();
        *u=node(k,v);
        u->ls=u->rs=NIL;
        return u;
    }
    void fix_insert(node* z){//fix red-black tree properties after insertion
        //while parent is red,may violate properties
        while(z->pt->color==Color::RED){
            if(z->pt==z->pt->pt->ls){//parent is left son
                node* y=z->pt->pt->rs;//uncle node
                if(y->color==Color::RED){//uncle is red
                    z->pt->color=Color::BLACK;//parent to black
                    y->color=Color::BLACK;//uncle to black
                    z->pt->pt->color=Color::RED;//grandparent to red
                    z=z->pt->pt;//move to grandparent
                }
                else{//uncle is black
                    if(z==z->pt->rs){//z is right son
                        z=z->pt;
                        left_rotate(z);
                    }
                    //z is left son
                    z->pt->color=Color::BLACK;//parent to black
                    z->pt->pt->color=Color::RED;//grandparent to red
                    right_rotate(z->pt->pt);
                }
            }
            else{//parent is right son
                node* y=z->pt->pt->ls;//uncle node
                if(y->color==Color::RED){//uncle is red
                    z->pt->color=Color::BLACK;
                    y->color=Color::BLACK;
                    z->pt->pt->color=Color::RED;
                    z=z->pt->pt;
                }
                else{//uncle is black
                    if(z==z->pt->ls){//z is left son
                        z=z->pt;
                        right_rotate(z);
                    }
                    //z is right child
                    z->pt->color=Color::BLACK;
                    z->pt->pt->color=Color::RED;
                    left_rotate(z->pt->pt);
                }
            }
        }
        root->color=Color::BLACK;//root is black
        return;
    }
    void left_rotate(node* n){
        /*
        **      |                     |
        **      N                     S
        **     / \    l-rotate(N)    / \
        **    L   S   ==========>   N   R
        **       / \               / \
        **      M   R             L   M
        */
        node* s=n->rs;
        n->rs=s->ls;
        if(s->ls!=NIL)
            s->ls->pt=n;
        s->pt=n->pt;
        if(n->pt==NIL)//n is root
            root=s;
        else if(n==n->pt->ls)//n is left son
            n->pt->ls=s;
        else//n is right son
            n->pt->rs=s;
        s->ls=n;
        n->pt=s;
        return;
    }
    void right_rotate(node* n){
        /*
        **      |                     |
        **      N                     S
        **     / \    r-rotate(N)    / \
        **    S   R   ==========>   L   N
        **   / \                       / \
        **  L   M                     M   R
        */
        node* s=n->ls;
        n->ls=s->rs;
        if(s->rs!=NIL)
            s->rs->pt=n;
        s->pt=n->pt;
        if(n->pt==NIL)//n is root
            root=s;
        else if(n==n->pt->rs)//n is right son
            n->pt->rs=s;
        else//n is left son
            n->pt->ls=s;
        s->rs=n;
        n->pt=s;
        return;
    }
    void destroy(node* u){//free node memory
        if(u==NIL)
            return;
        destroy(u->ls);
        destroy(u->rs);
        unsigned idx=u-tree;
        if(idx>=1&&idx<=Size)
            free_list.push_back(u);//recycle node
        return;
    }
    public:
    RBTree(){
        init_NIL();
    }
    ~RBTree(){
        destroy(root);
    }
    void insert(Key k,Val v){//insert key-value pair
        node* x=root;//start from root
        node* y=NIL;//track parent
        while(x!=NIL){
            y=x;
            if(k==x->key){
                x->val=v;
                return;
            }
            if(k<x->key)
                x=x->ls;
            else
                x=x->rs;
        }
        node* z=new_node(k,v);
        z->pt=y;
        if(y==NIL)
            root=z;//tree is empty
        else if(z->key<y->key)
            y->ls=z;//z as left son
        else
            y->rs=z;//z as right son
        fix_insert(z);
        return;
    }
    Val* find(Key k){//find value by key
        node* x=root;
        while(x!=NIL){
            if(k<x->key)
                x=x->ls;
            else if(k>x->key)
                x=x->rs;
            else
                return &(x->val);
        }
        return nullptr;//not found
    }
};
#endif

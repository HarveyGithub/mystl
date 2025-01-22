//no finish
#include<iostream>
#ifndef	_TIME_H
#include<time.h>
#endif
using namespace std;
template<typename T>
struct Less{bool operator()(const T &x,const T &y){return x<y;}};
template<typename T>
struct Greater{bool operator()(const T &x,const T &y){return x>y;}};
template<typename T,typename Compare=Less<T>>
class FHQ_Treap{
public:
    Compare cmp;
    struct Node{
        int pri;
        size_t size;
        T key;
        Node* left, *right;
    }*nil,*root;
    FHQ_Treap(){
        seed=time(0);
        nil=new Node();
        nil->key=T();
        nil->left=nil->right=nil;
        nil->pri=0;
        nil->size=0;
        root=nil;
    }
    Node* newnode(const T &key){
        Node* node=new Node();
        node->left=nil;
        node->right=nil;
        node->key=key;
        node->pri=rand_seed();
        return node;
    }
    Node* merge(Node* left,Node* right){
        if(left==nil) return right;
        if(right==nil) return left;
        if(left->pri>right->pri){
            left->right=merge(left->right,right);
            update(left);
            return left;
        }else{
            right->left=merge(left,right->left);
            update(right);
            return right;
        }
    }
    void split(Node* node,const T &key,Node*& left,Node*& right){
        if(node==nil){
            left=right=nil;
            return;
        }
        if(!cmp(key,node->key)){
            left=node;
            split(node->right,key,node->right,right);
        }else{
            right=node;
            split(node->left,key,left,node->left);
        }
        update(node);
    }
    Node *insert(const T &key){
        Node *left,*right,*p;
        split(root,key,left,right);
        p=newnode(key);
        root=merge(merge(left,p),right);
        return p;
    }
    void inorder(Node* node){
        if(node!=nil){
            inorder(node->left);
            cout<<node->key<<" ";
            inorder(node->right);
        }
    }
    void erase(const T &key){
        if(find(root,key)==nil) return;
        Erase(root,key);
    }
    Node *find(Node* node,const T &key){
        if(node==nil) return nil;
        if(key==node->key) return node;
        if(cmp(key,node->key)) return find(node->left,key);
        else return find(node->right,key);
    }
    Node *kth(Node* node,size_t k){
        if(k==node->left->size+1) return node;

    }
private:
    int seed;
    int rand_seed(){return seed=seed*1103515245+12345;}
    void update(Node* node){
        node->size=1+node->left->size+node->right->size;
    }
    void Erase(Node*& node,const T &key){
        if(node==nil) return;
        --node->size;
        if(key==node->key){
            Node *temp=node;
            node=merge(node->left,node->right);
            delete temp;
        }else if(cmp(key,node->key)) Erase(node->left,key);
        else Erase(node->right,key);
    }
};
FHQ_Treap<int,Greater<int>> fhq;
int main(){
    fhq.insert(1);
    fhq.insert(2);
    fhq.insert(3);
    fhq.insert(4);
    fhq.insert(5);
    fhq.insert(6);
    fhq.insert(7);
    fhq.insert(8);
    fhq.insert(9);
    fhq.insert(10);
    fhq.inorder(fhq.root);
    cout<<endl;
    fhq.erase(5);
    fhq.inorder(fhq.root);
    // cout<<endl;
}
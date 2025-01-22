#include<iostream>
#ifndef	_TIME_H
#include<time.h>
#endif
using namespace std;
template<typename T>
class FHQ_Treap{
private:
    int seed;
    int rand_seed(){return seed=seed*1103515245+12345;}
    void Earse(Node* node,T key){
        if(node==nil) return;
        if()
    }
public:
    struct Node{
        int pri;
        T key;
        Node* left, *right;
    }*nil,*root;
    FHQ_Treap(){
        seed=time(0);
        nil=new Node();
        nil->key=T();
        nil->left=nil->right=nil;
        nil->pri=0;
        root=nil;
    }
    Node* newnode(T key){
        Node* node=new Node();
        node->key=key;
        node->left=nil;
        node->right=nil;
        node->pri=rand_seed();
        return node;
    }
    Node* merge(Node* left,Node* right){
        if(left==nil) return right;
        if(right==nil) return left;
        if(left->pri>right->pri){
            left->right=merge(left->right,right);
            return left;
        }else{
            right->left=merge(left,right->left);
            return right;
        }
    }
    void split(Node* node,T key,Node*& left,Node*& right){
        if(node==nil){
            left=right=nil;
            return;
        }
        if(node->key<=key){
            left=node;
            split(node->right,key,node->right,right);
        }else{
            right=node;
            split(node->left,key,left,node->left);
        }
    }
    Node *insert(T key){
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
    void erase(T key){
        
    }
};
FHQ_Treap<int> fhq;
int main(){
    clock_t start,end;
    start=clock();
    for(int i=1;i<=1000000;i++) fhq.insert(i);
    end=clock();
    cout<<"Time used: "<<(double)(end-start)/CLOCKS_PER_SEC*1000<<"ms"<<endl;
    fhq.inorder(fhq.root);
    // for(int i=1;i<=1000000;i++) fhq.insert(i);
}
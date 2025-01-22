#include<iostream>
#ifndef	_TIME_H
#include<time.h>
#endif
using namespace std;
template<typename T>
class FHQ_Treap{
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
    Node* newnode(const T &key){
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
    void split(Node* node,const T &key,Node*& left,Node*& right){
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
        Erase(root,key);
    }
private:
    int seed;
    int rand_seed(){return seed=seed*1103515245+12345;}
    void Erase(Node*& node,const T &key){
        if(node==nil) return;
        if(key==node->key){
            Node *temp=node;
            node=merge(node->left,node->right);
            delete temp;
        }else if(key<node->key) Erase(node->left,key);
        else Erase(node->right,key);
    }
};
FHQ_Treap<int> fhq;
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
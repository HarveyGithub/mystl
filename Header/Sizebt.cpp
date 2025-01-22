//Don't finish
#include<iostream>
#include<time.h>
using namespace std;

template<typename Type>
class SBT{
public:
    struct Node{
        Type key;
        Node* left,*right;
        size_t size;
    }*nil,*root;
    SBT(){
        nil=new Node;
        nil->left=nil->right=nil;
        nil->size=0;
        root=nil;
    }
    void Right_Rotate(Node *&T){
        Node *k=T->left;
        T->left=k->right;
        k->right=T;
        k->size=T->size;
        T->size=1+T->left->size+T->right->size;
        T=k;
    }
    void Left_Rotate(Node *&T){
        Node *k=T->right;
        T->right=k->left;
        k->left=T;
        k->size=T->size;
        T->size=1+T->left->size+T->right->size;
        T=k;
    }
    void Maintain(Node *&T,bool flag){
        if(T==nil) return;
        if(flag==false){
            if(T->left->left->size>T->right->size) Right_Rotate(T);
            else{
                if(T->left->right->size>T->right->size){
                    Left_Rotate(T->left);
                    Right_Rotate(T);
                }else return;
            }
        }else{
            if(T->right->right->size>T->left->size) Left_Rotate(T);
            else{
                if(T->right->left->size>T->left->size){
                    Right_Rotate(T->right);
                    Left_Rotate(T);
                }else return;
            }
        }
        if(flag==0) Maintain(T->left,flag);
        else Maintain(T->right,flag);
        Maintain(T,flag);
    }
    void Insert(Node *&T,Type key){
        if(T==nil) T=newnode(key);
        else{
            ++T->size;
            if(key<T->key) Insert(T->left,key);
            else Insert(T->right,key);
            Maintain(T,key>=T->key);
        }
    }
    void inorder(Node *T){
        if(T!=nil){
            inorder(T->left);
            cout<<T->key<<" ";
            inorder(T->right);
        }
    }
private:
    Node* newnode(Type key){
        Node *p=new Node;
        p->key=key;
        p->left=nil;
        p->right=nil;
        p->size=1;
        return p;
    }
};
SBT<int> st;
int main(){
    clock_t start,end;
    start=clock();
    for(int i=0;i<1000000;i++) st.Insert(st.root,i);
    end=clock();
    cout<<"Time taken for insertion: "<<(double)(end-start)/CLOCKS_PER_SEC*1000<<" milliseconds"<<endl;
}
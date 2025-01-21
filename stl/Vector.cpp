#include<iostream>
#include<cassert>
#include<algorithm>
using namespace std;
template<typename T>
class Vector{
private:
    size_t Size,Able;
    T* Data;
public:
    struct Iterator{
        T* ptr;
        Iterator(T* ptr_):ptr(ptr_){}
        using value_type=T;
        using difference_type=std::ptrdiff_t;
        using pointer=T*;
        using reference=T&;
        using iterator_category=std::random_access_iterator_tag;
        T& operator*(){
            return*ptr;
        }
        Iterator& operator++(){
            ++ptr;
            return*this;
        }
        Iterator& operator--(){
            --ptr;
            return*this;
        }
        Iterator operator+(int n){
            return Iterator(ptr+n);
        }
        Iterator operator-(int n){
            return Iterator(ptr-n);
        }
        int operator-(Iterator other){
            return ptr-other.ptr;
        }
        Iterator& operator+=(int n){
            ptr+=n;
            return*this;
        }
        Iterator& operator-=(int n){
            ptr-=n;
            return*this;
        }
        bool operator!=(const Iterator& other){
            return ptr!=other.ptr;
        }
        bool operator==(const Iterator& other){
            return ptr==other.ptr;
        }
        bool operator<(const Iterator& other){
            return ptr<other.ptr;
        }
        bool operator>(const Iterator& other){
            return ptr>other.ptr;
        }
        bool operator<=(const Iterator& other){
            return ptr<=other.ptr;
        }
        bool operator>=(const Iterator& other){
            return ptr>=other.ptr;
        }
    };
    bool Out_Assert;
    Vector(){
        Size=0;
        Able=1;
        Data=new T[1];
        Out_Assert=true;
    }
    void push_back(T value){
        if(Size==Able){
            T* NewData=new T[Able*2];
            for(size_t i=0;i<Size;++i){
                NewData[i]=Data[i];
            }
            delete[] Data;
            Data=NewData;
            Able*=2;
        }
        Data[Size++]=value;
    }
    void pop_back(){
        if(Size==0)assert(0);
        --Size;
    }
    size_t size(){
        return Size;
    }
    T& operator[](const size_t& index){
        return Data[index];
    }
    T& at(const size_t& index){
        if(index>=Size){
            assert(0);
        }
        return Data[index];
    }
    Iterator begin(){
        return Iterator(Data);
    }
    Iterator end(){
        return Iterator(Data+Size);
    }
    void Out_Assert_Set(bool value){
        Out_Assert=value;
    }
    ~Vector(){
        delete[] Data;
    }
};
int main(){
    Vector<int> v;
    v.push_back(2);
    v.push_back(12);
    v.push_back(15);
    v.push_back(4);
    v.push_back(17);
    sort(v.begin(),v.end());
    for(auto it=v.begin();it!=v.end();++it){
        cout<<*it<<" ";
    }
    cout<<endl;
}

//Finish Debug
#pragma once
#include<cassert>
#include<cstddef>
using namespace std;
template<typename T>
class Vector{
private:
    size_t Size,Able;
    T* Data;
public:
    struct iterator{
        T* ptr;
<<<<<<< HEAD:Header/vector.h
        iterator(T* PTR):ptr(PTR){};
        T& operator*(){
            return *ptr;;
=======
        using value_type=T;
        using difference_type=ptrdiff_t;
        using reference=T&;
        using pointer=T*;
        using iterator_category=std::random_access_iterator_tag;
        iterator(T* PTR):ptr(PTR){}
        reference operator*(){
            return*ptr;
>>>>>>> 7baf4bdb7c94ae23a95fc8961be6d4bfcd4fceb7:Header/vector.hpp
        }
        iterator& operator++(){
            ++ptr;
            return*this;
        }
        const iterator operator++(int){
            iterator temp=*this;
            ++ptr;
            return temp;
        }
        iterator& operator--(){
            --ptr;
            return*this;
        }
        const iterator operator--(int){
            iterator temp=*this;
            --ptr;
            return temp;
        }
        int operator-(const iterator& other){
            return ptr-other.ptr;
        }
        iterator operator+(const int& n)const{
            return ptr+n;
        }
        iterator& operator+=(int n){
            ptr+=n;
            return*this;
        }
        iterator operator-(const int& n)const{
            return ptr-n;
        }
        iterator& operator-=(int n){
            ptr-=n;
            return*this;
        }
        iterator& next(){
            return++(*this);
        }
        iterator& prev(){
            return--(*this);
        }
        bool operator==(const iterator& other)const{
            return ptr==other.ptr;
        }
        bool operator!=(const iterator& other)const{
            return ptr!=other.ptr;
        }
        bool operator<(const iterator& other)const{
            return ptr<other.ptr;
        }
        bool operator<=(const iterator& other)const{
            return ptr<=other.ptr;
        }
        bool operator>(const iterator& other)const{
            return ptr>other.ptr;
        }
        bool operator>=(const iterator& other)const{
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
            for(size_t i=0;i<Size;i++){
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
    iterator begin(){
        return iterator(Data);
    }
    iterator end(){
        return iterator(Data+Size);
    }
    void Out_Assert_Set(bool value){
        Out_Assert=value;
    }
    ~Vector(){
        delete[] Data;
    }
};
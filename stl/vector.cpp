#include<iostream>
#include<cassert>
using namespace std;
template<typename T>
class Vector{
private:
    size_t Size,Able;
    T* Data;
public:
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
        if(Size==0) return;
        Size--;
    }
    size_t size(){
        return Size;
    }
    T operator[](const size_t &index){
        if(index>=Size){
            if(Out_Assert)assert(0);
            else return 0;
        }
        return Data[index];
    }
    T at(const size_t &index){
        if(index>=Size) return "No";
        return Data[index];
    }
};
Vector<int> v;
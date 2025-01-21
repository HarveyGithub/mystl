#pragma once
template<class T>
class _queue{ //循环队列
    public:
    int head,tail,size,ts;
    T *data;       //数组指针
    
    // _queue(int);   构造函数(默认容量为1005)
    // void push(T);  入队
    // T pop();       出队
    // bool empty();  判空
    // ~_queue();     析构函数
    // T& front();    队首元素
    // void clear();  清空队列

    _queue(int n=1005){  //自定义容量（默认1005）
        head=tail=size=0;
        ts=n;
        data=new T[n];
    }
    inline void push(T x){
        data[tail++]=x;
        if (tail>=ts) tail=0;
        size++;
    }
    inline T pop(){
        T x=data[head++];
        if (head>=ts) head=0;
        size--;
        return x;
    }
    inline bool empty(){
        return size==0;
    }
    ~_queue(){
        delete[] data;
    }
    inline T& front(){
        return data[head];
    }
    inline void clear()
	{
    	tail=head;
    	size=0;
	}
};
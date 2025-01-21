#pragma once
template<class t> struct Stack
{
	t a[100005];
	int stop=0;
	inline void push(t x)
	{
		a[++stop]=x;
	}
	inline t top()
	{
		return a[stop];
	}
	inline void pop()
	{
		stop--;
	}
	inline size_t size()
	{
		return stop;
	}
	inline t* begin()
	{
		return a+1;
	}
	inline t* end()
	{
		return a+1+stop;
	}
};
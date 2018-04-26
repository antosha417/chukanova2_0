#pragma once

#include <cstring>
template<class T>
class CVector
{
public:
	
	CVector()
	{
	  BufferSize = 2;
	  Size = 0;
	  Buffer = new T [BufferSize]; 	
	}
	~CVector()
	{
		delete[] Buffer;
	}
	void Push_back(T item)
	{
		if(Size >= BufferSize)
		{
			grow();
		}
		if(Size < BufferSize)
		{
			
			Buffer[Size] = item;
			Size++;
		}
		
	}
	T Pop_back()
	{

		Size--;
		T temp = Buffer[Size];
		if(Size+1<=BufferSize/4 ){
			decrease();
		}
		return temp;
	}
	T& operator [] (int ind)
	{
		if(ind < Size)
		{
			return Buffer[ind];
		}
	}
	int size()
	{
		return Size;
	}

private:

	int Size;
	int BufferSize;
	
	void grow()
	{
		T* TempBuffer = new T[BufferSize*2];
		memcpy(TempBuffer,Buffer,BufferSize*sizeof(T));
		delete[] Buffer;
		Buffer = TempBuffer;
		BufferSize *= 2;
	}
	void decrease()
	{
		T* TempBuffer = new T[BufferSize/2];
		memcpy(TempBuffer,Buffer,(BufferSize/2)*sizeof(T));
		delete[] Buffer;
		Buffer = TempBuffer;
		BufferSize /= 2;
	}	
	T* Buffer;
};
template<class T>
class CQueue
{
public:

	CQueue()
	{
		Size = 0;
	}
	~CQueue()
	{

	}
	T pop_front()
	{
		if(stackFront.size() <= 0)
		{
			Repush();
		} 
		Size--;
		return stackFront.Pop_back();
	}
	bool IsEmpty()
	{
		return Size == 0;
	}
	void push_back(T item)
	{
		++Size;
		stackBack.Push_back(item);
		if(stackBack.size()>=stackFront.size()*4)
		{
			Repush();
		}
	}

private:

	int Size;
	void Repush()
	{
		if(stackFront.size()==0)
		{
			while(stackBack.size() !=0)
			{
				stackFront.Push_back(stackBack.Pop_back());
			}
		}
		 else
		{
			CVector<T> temp;
			while(stackFront.size() !=0)
			{
				temp.Push_back(stackFront.Pop_back());
			}
			while(stackBack.size() !=0)
			{
				stackFront.Push_back(stackBack.Pop_back());
			}
			while(temp.size() !=0)
			{
				stackFront.Push_back(temp.Pop_back());
			}
	}
	}
	CVector<T> stackFront;
	CVector<T> stackBack;
};
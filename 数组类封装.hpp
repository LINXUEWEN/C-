#pragma once
#include <iostream>
#include <string>
using namespace std;


template < class T >
class myArray{
public:
	myArray(int capacity)
	{
		//cout << "myArray有参构造函数调用" << endl;
		this->m_Capacity = capacity;
		this->m_Size = 0;
		this->pAddress = new T[this->m_Capacity];
	}

	myArray(const myArray& arr)
	{
		//cout << "myArray拷贝构造函数调用" << endl;
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		this->pAddress = new T[this->m_Capacity];
		for (int i = 0; i < this->m_Size; i++)
		{
			this->pAddress[i] = arr.pAddress[i];
		}
	}

	//防止浅拷贝问题
	myArray& operator=(const myArray& arr)
	{
		//cout << "myArray的operator=调用" << endl;
		if (this->pAddress)
		{
			delete[] this->pAddress;
			this->pAddress = NULL;
			this->m_Capacity = 0;
			this->m_Size = 0;
		}

		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		this->pAddress = new T[m_Capacity];
		for (int i = 0; i < this->m_Size; i++)
		{
			this->pAddress[i] = arr.pAddress[i];
		}
		return *this;
	}

	void push_back(const T& val)
	{
		if (this->m_Capacity == this->m_Size)
		{
			return;
		}
		this->pAddress[this->m_Size] = val;
		this->m_Size++;
	}

	void pop_back()
	{
		if (!this->m_Size)
		{
			return;
		}
		this->m_Size--;
	}

	T& operator[](int index)
	{
		return this->pAddress[index];
	}

	int get_capacity()
	{
		return this->m_Capacity;
	}

	int get_size()
	{
		return this->m_Size;
	}
	~myArray()
	{
		//cout << "myArray析构函数调用" << endl;
		if (this->pAddress)
		{
			delete[] this->pAddress;
			this->pAddress = NULL;
		}
	}

private:
	T *pAddress;
	int m_Capacity;//容量
	int m_Size;
};


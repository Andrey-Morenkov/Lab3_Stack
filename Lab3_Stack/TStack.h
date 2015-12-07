#pragma once
// Динамические структуры данных - стек

// |   | 4
// |   | 3
// |   | 2
// |   | 1 
// |___| 0
//      -1

const int MaxStackSize = 1000;


template <class T>
class TStack
{
private:
	int MaxSize;           // размер стека
	int Index;             // индекс верхнего элемента
	T* mas;                // сам стек в виде массива
public:
	TStack(int len = 10)
	{
		if ((len <= 0) || (len > MaxStackSize))
		    throw len;
	    else
	    {
		    MaxSize = len;
		    Index = -1;
		    mas = new T [MaxSize];
	    }
	}
	TStack(const TStack& s)
	{
		MaxSize = s.MaxSize;
     	Index   = s.Index;
    	mas     = new T [MaxSize];
        for (int i=0; i < (Index+1); i++)
	        mas[i] = s.mas[i];
	}
	~TStack()
	{
		delete[] mas;
	}
	TStack& operator=(const TStack& s);

	// Проверка на полноту и пустоту стека
	bool IsEmpty();
	bool IsFull();

	// Операции со стеком
	T Top ();              // Подсмотреть верхний элемент стека
	T Pop ();              // Вытолкнуть верхний элемент стека
	void Push(const T n);  // Положить элемент в стек
	void Clear();          // Очистить стек
};//-----------------------------------------------------------------------------------------------

template <class T>
TStack<T>& TStack<T>:: operator=(const TStack& s)
{
	if (MaxSize != s.MaxSize)
	{
		delete[] mas;
		MaxSize = s.MaxSize;
		mas = new T [MaxSize];
	}
	Index = s.Index;
	for (int i=0; i < (MaxSize+1); i++)
	    mas[i] = s.mas[i];
	return *this;
}/*-------------------------------------------------------------------------*/

template <class T>
bool TStack<T>:: IsEmpty()
{
	if (Index == -1)
        return true;
	return false;
}/*-------------------------------------------------------------------------*/

template <class T>
bool TStack<T>:: IsFull()
{
	if (Index == (MaxSize -1))
	    return true;
	return false;
}/*-------------------------------------------------------------------------*/

template <class T>
T TStack<T>:: Top ()               
{
	return mas[Index];
}/*-------------------------------------------------------------------------*/

template <class T>
T TStack<T>:: Pop ()               
{
	if (IsEmpty())
	    throw Index;
    else
		return mas[Index --];
}/*-------------------------------------------------------------------------*/

template <class T>
void TStack<T>:: Push(const T n)  
{
	if (IsFull())
	    throw Index;
	else
	{
	    Index++;
	    mas[Index] = n;
	}
}/*-------------------------------------------------------------------------*/

template <class T>
void TStack<T>:: Clear()           
{
	Index = -1;
}/*-------------------------------------------------------------------------*/
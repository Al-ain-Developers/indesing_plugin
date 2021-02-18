#ifndef __WRHybridVector__
#define __WRHybridVector__

template <class T,WRInt32 maxStaticSize> class WRHybridVector
 {
 public:
	WRHybridVector() : allocated(false), size(0) ,data(NULL){}
	T* Init(WRInt32 len, T* userStorage = NULL)
	{
		allocated = 0;
		size = len;
		if (userStorage)
			data = userStorage;
		else if (len <= maxStaticSize)
			data = staticData;
		else
		{	
			data = (T*) WRMalloc(len * sizeof(T));
			allocated = len;
		}
		return data;
	}
	virtual ~WRHybridVector()
	{
		if (allocated != 0)
			WRFree(data);
	}
	T* PeekArray(void) { return data; }
	WRInt32 Size(void) const { return size; }
	T*  Resize(WRInt32 len) // not preserving old content!
	{
		if (len > size)
		{
			if (allocated > 0)
			{
				T* newData = (T*) WRMalloc(len * sizeof(T));
				WRFree(data);
				data = newData;
				allocated = len;
			}
			else if (len > maxStaticSize)
			{
				data = (T*) WRMalloc(len * sizeof(T));
				allocated = len;
			}
			else
				data = staticData;
		}
		size = len;
		return data;
	}
	T& operator[](WRInt32 i) { return data[i]; }
	WRInt32	allocated;
	WRInt32 size;
	T* data;
	T  staticData[maxStaticSize];
 };

#endif

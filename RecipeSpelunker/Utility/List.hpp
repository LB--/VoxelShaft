
#ifndef __RecipeSpelunker_Utility_List_HeaderPlusPlus__
#define __RecipeSpelunker_Utility_List_HeaderPlusPlus__

#include "Types.hpp"

namespace RecipeSpelunker
{
	namespace Utility
	{
		template<typename T>
		struct List
		{
			List(unsigned size = 0) : arr(new T[size]), size(size)
			{
			}
			List(const List &from) : arr(new T[from.size]), size(from.size)
			{
				for(unsigned i = 0; i < size; ++i)
				{
					arr[i] = from.arr[i];
				}
			}
			List(List &&from) : arr(from.arr), size(from.size)
			{
				from.arr = nullptr;
				from.size = 0;
			}
			~List()
			{
				delete[] arr;
			}
			List &operator=(List from)
			{
				Swap(arr, from.arr);
				Swap(size, from.size);
				return *this;
			}
			List &operator=(List &&from)
			{
				Swap(arr, from.arr);
				Swap(size, from.size);
				return *this;
			}

			unsigned Size() const
			{
				return size;
			}

			void Add(const T &t)
			{
				List tl (size+1);
				for(unsigned i = 0; i < size; ++i)
				{
					tl.arr[i] = arr[i];
				}
				tl.arr[size] = t;
				*this = tl;
			}
			void Insert(const T &t, unsigned before)
			{
				List tl (size+1);
				for(unsigned i = 0; i < before; ++i)
				{
					tl.arr[i] = arr[i];
				}
				tl.arr[before] = t;
				for(unsigned i = before; i < size; ++i)
				{
					tl.arr[i+1] = arr[i];
				}
				*this = tl;
			}
			T Remove(unsigned index)
			{
				List tl (size-1);
				for(unsigned i = 0; i < index; ++i)
				{
					tl.arr[i] = arr[i];
				}
				for(unsigned i = index; i < size-1; ++i)
				{
					tl.arr[i] = arr[i+1];
				}
				T t (arr[index]);
				*this = tl;
				return t;
			}
			T &operator[](unsigned index)
			{
				return arr[index];
			}
			T operator[](unsigned index) const
			{
				return arr[index];
			}
		private:
			T *arr;
			unsigned size;
		};
	}
}

#endif

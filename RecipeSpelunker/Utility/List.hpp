/* Copyright (C) 2012 Nicholas "LB" Braden.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Modified distributions of source code must be made as public forks of
 *    the original or a fork and must link to the original repository owned
 *    by the above copyright holder, where "repository" and "fork" refer to
 *    those maintained on http://github.com/
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

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


#ifndef __RecipeSpelunker_Utility_Types_HeaderPlusPlus__
#define __RecipeSpelunker_Utility_Types_HeaderPlusPlus__

#include <typeinfo>

namespace RecipeSpelunker
{
	namespace Utility
	{
		template<typename T, typename U> bool operator!=(const T &a, const U &b)
		{
			return !(a == b);
		}
		template<typename T, typename U> bool operator>(const T &a, const U &b)
		{
			return b < a;
		}
		template<typename T, typename U> bool operator<=(const T &a, const U &b)
		{
			return !(b < a);
		}
		template<typename T, typename U> bool operator>=(const T &a, const U &b)
		{
			return !(a < b);
		}

		template<typename T>
		void Swap(T &a, T &b)
		{
			T t (a);
			a = b;
			b = t;
		}
	}
}

#endif

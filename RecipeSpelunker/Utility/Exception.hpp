
#ifndef __RecipeSpelunker_Utility_Exception_HeaderPlusPlus__
#define __RecipeSpelunker_Utility_Exception_HeaderPlusPlus__

#include "String.hpp"

namespace RecipeSpelunker
{
	namespace Utility
	{
		struct Exception
		{
			Exception(){}
			Exception(const String &msg) : msg(msg) {}
			Exception(const Exception &from) : msg(from.msg) {}
			Exception(Exception &&from) : msg(from.msg) {}
			Exception &operator=(const Exception &) = delete;
			Exception &operator=(Exception &&) = delete;
			virtual ~Exception(){}

			virtual operator String() const
			{
				return msg;
			}

		private:
			String msg;
		};
	}
}

#endif

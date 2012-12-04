
#ifndef __RecipeSpelunker_Manager_HeaderPlusPlus__
#define __RecipeSpelunker_Manager_HeaderPlusPlus__

#include "Utility/List.hpp"
#include "Utility/Cloneable.hpp"

namespace RecipeSpelunker
{
	struct Manager
	{
		Manager(){}
		Manager(const Manager &) = delete;
		Manager(Manager &&) = delete;
		Manager &operator=(const Manager &) = delete;
		Manager &operator=(Manager &&) = delete;
		virtual ~Manager(){}

		virtual void Manage() = 0;
		virtual Utility::List<Utility::Cloneable *> ManagedObjects() const = 0;
	};
}

#endif

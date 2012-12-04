
#ifndef __RecipeSpelunker_Plugin_HeaderPlusPlus__
#define __RecipeSpelunker_Plugin_HeaderPlusPlus__

#include "Manager.hpp"

namespace RecipeSpelunker
{
	struct Plugin
	{
		Plugin(){}
		Plugin(const Plugin &) = delete;
		Plugin(Plugin &&) = delete;
		Plugin &operator=(const Plugin &) = delete;
		Plugin &operator=(Plugin &&) = delete;
		virtual ~Plugin(){}

		virtual unsigned APIVersion() const = 0;
		virtual unsigned PluginVersion() const = 0;

		struct Dependency
		{
			Dependency(){}
			Dependency(const Dependency &) = delete;
			Dependency(Dependency &&) = delete;
			Dependency &operator=(const Dependency &) = delete;
			Dependency &operator=(Dependency &&) = delete;
			~Dependency(){}

			virtual bool Required() const
			{
				return true;
			}
			virtual bool Resolve(/**/) = 0;
		};

		virtual Utility::List<Dependency *> Dependencies() = 0;
		virtual Utility::List<Manager *> Managers() = 0;
	};
}

#endif

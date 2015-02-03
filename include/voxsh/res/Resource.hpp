#ifndef voxsh_res_Resource_HeaderPlusPlus
#define voxsh_res_Resource_HeaderPlusPlus

#include "resplunk/util/Cloneable.hpp"
#include "resplunk/event/Event.hpp"

#include <iostream>

namespace voxsh
{
	namespace res
	{
		struct Resource
		: resplunk::util::CloneImplementor<Resource>
		{
			Resource() = default;
			Resource &operator=(Resource const &) = delete;
			virtual ~Resource() = default;

			struct ChangeEvent
			: resplunk::event::Implementor<ChangeEvent, resplunk::event::Event>
			{
				virtual Resource const &instance() noexcept = 0;
				virtual Resource &instance() const noexcept = 0;
			};

		protected:
			Resource(Resource const &) noexcept
			{
			}

		private:
			virtual std::ostream &serialize(std::ostream &) const noexcept = 0;
			friend std::ostream &operator<<(std::ostream &o, Resource const &r) noexcept
			{
				return r.serialize(o);
			}

			virtual Resource *clone() const noexcept override = 0;
		};
	}
}

#endif

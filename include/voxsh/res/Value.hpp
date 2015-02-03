#ifndef voxsh_res_Value_HeaderPlusPlus
#define voxsh_res_Value_HeaderPlusPlus

#include "voxsh/res/Resource.hpp"
#include "voxsh/util/TMP.hpp"

#include <string>
#include <cstdint>

namespace voxsh
{
	namespace res
	{
		template<typename T>
		struct Value final
		: resplunk::util::CloneImplementor<Value>
		{
			Value(util::const_autoref<T> s = T{})
			: val{s}
			{
			}

			operator T() const noexcept
			{
				return val;
			}
			auto value() const noexcept
			-> util::const_autoref<T>
			{
				return val;
			}

			struct ChangeEvent
			: resplunk::event::Implementor<ChangeEvent, Resource::ChangeEvent>
			{
				ChangeEvent(Value &v, util::const_autoref<T> change) noexcept
				: inst(v)
				, val{change}
				{
				}

				virtual Value const &instance() noexcept override
				{
					return inst;
				}
				virtual Value &instance() const noexcept override
				{
					return inst;
				}

				auto value() const noexcept
				-> util::const_autoref<T>
				{
					return val;
				}
				void value(util::const_autoref<T> value) noexcept
				{
					val = value;
				}

			private:
				Value &inst;
				T val;
			};

		protected:
			Value(Value const &from) noexcept
			: Resource{from}
			, val{from.val}
			{
			}

		private:
			T val;

			virtual std::ostream &serialize(std::ostream &o) const noexcept override
			{
				return o << val;
			}

			virtual Resource *clone() const noexcept override
			{
				return new Value(*this);
			}
		};

		using String = Value<std::string>;
		using Integer = Value<std::int64_t>;
		using Float = Value<long double>;
	}
}

#endif

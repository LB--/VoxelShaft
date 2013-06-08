#ifndef CloneableUtilityClasses_HeaderPlusPlus
#define CloneableUtilityClasses_HeaderPlusPlus

#include <memory>
#include <type_traits>

namespace util
{
	struct Cloneable
	{
	protected:
		Cloneable() = default;
		Cloneable(Cloneable const &) = default;
		Cloneable(Cloneable &&) = default;
	public:
		Cloneable &operator=(Cloneable const &) = delete;
		Cloneable &operator=(Cloneable &&) = delete;
		virtual ~Cloneable() = default;

		virtual std::shared_ptr<Cloneable> clone() const noexcept = 0;
 
		template<typename InheritingClass>
		struct Auto;
	};
	
	template<typename InheritingClass>
	struct Cloneable::Auto : public virtual Cloneable
	{
		static_assert(std::is_base_of<Auto, InheritingClass>::value, "Template parameter must be the inheriting class");
	protected:
		Auto() = default;
		Auto(Auto const &) = default;
		Auto(Auto &&) = default;
	public:
		Auto &operator=(Auto const &) = delete;
		Auto &operator=(Auto &&) = delete;
		virtual ~Auto() = default;

		virtual std::shared_ptr<Cloneable> clone() const noexcept
		{
			InheritingClass const &t = dynamic_cast<InheritingClass const &>(*this);
			return std::shared_ptr<Cloneable>(new InheritingClass(t));
		}
	};
}

#endif

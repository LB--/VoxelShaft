#ifndef voxsh_util_TMP_HeaderPlusPlus
#defnne voxsh_util_TMP_HeaderPlusPlus

#include <type_traits>

namespace voxsh
{
	namespace util
	{
		template<typename T>
		using autoref = typename std::conditional
		<
			std::is_fundamental<T>::value,
			T,
			T &
		>::type;
		template<typename T>
		using const_autoref = typename std::conditional
		<
			std::is_fundamental<T>::value,
			T,
			T const &
		>::type;
	}
}

#endif

#ifndef RecipeSpelunker_Common_Util_OptimalSize_HeaderPlusPlus
#define RecipeSpelunker_Common_Util_OptimalSize_HeaderPlusPlus

#include <cstdint>
#include <type_traits>
#include <climits>
#include <limits>
#include <vector>
#include <iostream>
#include <cmath>
#include <stdexcept>

namespace rs
{
	namespace util
	{
		//C++14: replace with variable template
		template<typename T, T b, std::uintmax_t e>
		struct constexpr_pow : std::integral_constant<decltype(b*1), b*constexpr_pow<T, b, e-1>::value>
		{
		};
		template<typename T, T b>
		struct constexpr_pow<T, b, 0> : std::integral_constant<decltype(b*1), (decltype(b*1))(1)>
		{
		};

		template<std::size_t Base, std::size_t... Sizes>
		struct optimal_size
		{
			static_assert(Base < sizeof(std::uintmax_t), "Base is too large");
			//TODO: Above check for each of Sizes
			static_assert(sizeof...(Sizes) < constexpr_pow<std::size_t, 2, Base*CHAR_BIT>::value, "Too many Sizes for Base to support");
			static constexpr std::size_t border = std::numeric_limits<std::uint8_t>::max()+1 - sizeof...(Sizes);

			static std::vector<size_t> const &vec()
			{
				static std::vector<size_t> const v {Sizes...};
				return v;
			}

			std::uintmax_t size = 0;
			optimal_size() = default;
			optimal_size(std::uintmax_t size_)
			: size(size_)
			{
			}

			friend std::ostream &operator<<(std::ostream &os, optimal_size const &s)
			{
				if(s.size < border)
				{
					return os.write(reinterpret_cast<std::ostream::char_type const *>(&s.size), Base);
				}
				auto const &v = vec();
				for(std::size_t i = 0; i < v.size(); ++i)
				{
					if(s.size < std::pow(2, v[i]*CHAR_BIT))
					{
						std::uint8_t base = border + i;
						os.write(reinterpret_cast<std::ostream::char_type const *>(&base), 1);
						return os.write(reinterpret_cast<std::ostream::char_type const *>(&s.size), v[i]);
					}
				}
				throw std::out_of_range(std::to_string(s.size));
			}
			friend std::istream &operator>>(std::istream &is, optimal_size &s)
			{
				std::uint8_t base;
				is.read(reinterpret_cast<std::istream::char_type *>(&base), 1);
				if(base < border)
				{
					s.size = base;
					return is;
				}
				auto const &v = vec();
				return is.read(reinterpret_cast<std::istream::char_type *>(&s.size), v[base-border]);
			}
		};
	}
}

#endif

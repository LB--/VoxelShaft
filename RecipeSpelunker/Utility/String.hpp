
#ifndef __RecipeSpelunker_Utility_String_HeaderPlusPlus__
#define __RecipeSpelunker_Utility_String_HeaderPlusPlus__

#include "Types.hpp"

namespace RecipeSpelunker
{
	namespace Utility
	{
		namespace
		{
			inline unsigned len(const char *str)
			{
				unsigned len = 0;
				while(*(str++)) ++len;
				return len;
			}
			inline unsigned len(const wchar_t *str)
			{
				unsigned len = 0;
				while(*(str++)) ++len;
				return len;
			}
			inline wchar_t *copy(const char *str)
			{
				wchar_t *ns = new wchar_t[len(str)+1];
				while(*str) *ns = *(str++), ++ns;
				*ns = L'\0';
				return ns;
			}
			inline wchar_t *copy(const wchar_t *str)
			{
				wchar_t *ns = new wchar_t[len(str)+1];
				while(*str) *ns = *(str++), ++ns;
				*ns = L'\0';
				return ns;
			}
		}
		struct String
		{
			String() : str(copy(L""))
			{
			}
			String(const String &from) : str(copy(from.str))
			{
			}
			String(String &&from) : str(from.str)
			{
				from.str = nullptr;
			}
			String(const char *c_style_string) : str(copy(c_style_string))
			{
			}
			String(const wchar_t *c_style_string) : str(copy(c_style_string))
			{
			}
			String(signed number);
			String(unsigned number);
			String(bool truefalse) : str(truefalse ? copy(L"true") : copy(L"false"))
			{
			}
			~String()
			{
				delete[] str;
			}

			String &operator=(String from)
			{
				Swap(str, from.str);
				return *this;
			}
			String &operator=(String &&from)
			{
				Swap(str, from.str);
				return *this;
			}
			String &operator=(signed number);
			String &operator=(unsigned number);
			String &operator=(bool truefalse)
			{
				(delete[] str), str = truefalse ? copy(L"true") : copy(L"false");
				return *this;
			}

			String &operator+=(const String &from)
			{
				const unsigned la = Length(), lb = from.Length();
				wchar_t *ns = new wchar_t[la+lb+1];
				for(unsigned i = 0; i < la; ++i) ns[i] = str[i];
				for(unsigned i = 0; i < lb; ++i) ns[la+i] = from[i];
				ns[la+lb] = L'\0';
				return *this;
			}
			String operator+(const String &with) const
			{
				return String(*this) += with;
			}

			struct SCS
			{
				SCS() = delete;
				SCS(const wchar_t *p)
				{
					s = new char[len(p)+1];
					while(*p) *s = static_cast<char>(*(p++)), ++s;
					*s = '\0';
				}
				SCS(const SCS &) = delete;
				SCS(SCS &&from) : s(from.s)
				{
					from.s = nullptr;
				}
				SCS &operator=(const SCS &) = delete;
				SCS &operator=(SCS &&) = delete;
				~SCS()
				{
					delete[] s;
				}

				operator const char *() const
				{
					return s;
				}
			private:
				char *s;
			};
			SCS ScopedCStr() const
			{
				return SCS(str);
			}
			const wchar_t *ScopedWCStr() const
			{
				return str;
			}
			operator signed() const;
			operator unsigned() const;
			operator bool() const
			{
				return EqualsCI(L"true");
			}

			bool operator==(const String &other) const;
			bool EqualsCI(const String &other) const;
			friend bool operator==(const char *c_style_string, const String &str);
			friend bool operator==(const wchar_t *c_style_string, const String &str);

			bool operator<(const String &other) const;
			friend bool operator<(const char *c_style_string, const String &str);
			friend bool operator<(const wchar_t *c_style_string, const String &str);

			unsigned Length() const
			{
				return len(str);
			}

			wchar_t &operator[](unsigned index)
			{
				return str[index];
			}
			wchar_t operator[](unsigned index) const
			{
				return str[index];
			}

			String SubStr(unsigned start) const
			{
				return String(str + start);
			}
			String SubStr(unsigned start, unsigned end) const
			{
				if(start > end) Swap(start, end);
				String t (str + start);
				t.str[start - (end - 1)] = L'\0';
				return t;
			}
		private:
			wchar_t *str;
		};
	}
}

#endif

/* Copyright (C) 2012 Nicholas "LB" Braden.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Modified distributions of source code must be made as public forks of
 *    the original or a fork and must link to the original repository owned
 *    by the above copyright holder, where "repository" and "fork" refer to
 *    those maintained on http://github.com/
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

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

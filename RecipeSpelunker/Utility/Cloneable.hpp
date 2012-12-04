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

#ifndef __RecipeSpelunker_Utility_Cloneable_HeaderPlusPlus__
#define __RecipeSpelunker_Utility_Cloneable_HeaderPlusPlus__

#include "Exception.hpp"

namespace RecipeSpelunker
{
	namespace Utility
	{
		struct Cloneable
		{
		protected:
			Cloneable(){}
			Cloneable(const Cloneable &){}
			Cloneable(Cloneable &&){}
		public:
			Cloneable &operator=(const Cloneable &) = delete;
			Cloneable &operator=(Cloneable &&) = delete;
			virtual ~Cloneable(){}

			virtual Cloneable *Clone() const = 0;
			template<typename T_extends_Cloneable>
			static void ReleaseClone(T_extends_Cloneable *&clone)
			{
				Cloneable *c = dynamic_cast<Cloneable *>(clone);
				if(!c)
				{
					throw CloningException("Object not instance of Cloneable, cannot release", clone);
				}
				clone = nullptr;
				c->ReleaseClone(), c = nullptr;
			}
		protected:
			virtual void ReleaseClone() = 0;
		public:
			struct CloningException : public virtual Exception
			{
				CloningException(void *instance) : inst(instance) {}
				CloningException(const String &msg, void *instance) : Exception(msg), inst(instance) {}
				CloningException(const CloningException &){}
				CloningException(CloningException &&){}
				CloningException &operator=(const CloningException &) = delete;
				CloningException &operator=(CloningException &&) = delete;
				virtual ~CloningException()
				{
					inst = nullptr;
				}

				void *Instance() const
				{
					return inst;
				}

			private:
				void *inst;
			};
	 
			template<typename InheritingClass>
			struct Auto;
		};
		
		template<typename InheritingClass>
		struct Cloneable::Auto : public virtual Cloneable
		{
		protected:
			Auto(){}
			Auto(const Auto &){}
			Auto(Auto &&){}
		public:
			Auto &operator=(const Auto &) = delete;
			Auto &operator=(Auto &&) = delete;
			virtual ~Auto(){}

			virtual InheritingClass *Clone() const
			{
				const InheritingClass *t = dynamic_cast<const InheritingClass *>(this);
				if(!t)
				{
					throw CloningException("dynamic_cast failed", this);
				}
				return new InheritingClass(*t);
			}
		protected:
			virtual void ReleaseClone()
			{
				if(!dynamic_cast<const InheritingClass *>(this))
				{
					throw CloningException("dynamic_cast failed", this);
				}
				delete this;
			}
		};
	}
}

#endif

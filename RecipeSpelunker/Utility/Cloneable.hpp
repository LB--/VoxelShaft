
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

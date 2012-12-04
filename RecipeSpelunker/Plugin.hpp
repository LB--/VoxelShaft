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

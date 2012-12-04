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

#include "RecipeSpelunker/Utility/Cloneable.hpp"
#include "RecipeSpelunker/Utility/Exception.hpp"
#include "RecipeSpelunker/Utility/String.hpp"
#include "RecipeSpelunker/Plugin.hpp"

#include <iostream>
using std::wcout;
using std::wclog;
using std::wcerr;
using std::wcin;
using std::endl;
#include <limits>
#include <typeinfo>
#include <exception>

//MinGW bugfix - undefined reference to ignore(int, int) for wide istreams
#define wcin cin
using std::cin;

//Windows bugfix - definition of min/max macros interferes with calling std::numeric_limits<>::max()
#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

int main(int NArgs, char **Args)
{
	using RecipeSpelunker::Utility::Exception;
	using RecipeSpelunker::Utility::String;

	try
	{
		throw std::exception();
	}
	catch(Exception &e)
	{
		wcerr << L"Uncaught Recipe-Spelunker Exception: "
		      << typeid(e).name() << endl
		      << L'\t' << String(e).ScopedWCStr() << endl;
		wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	catch(std::exception &e)
	{
		wcerr << L"Uncaught Standard Library Exception: "
		      << typeid(e).name() << endl
		      << L'\t' << e.what() << endl;
		wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	catch(...)
	{
		wcerr << L"Uncaught Unknown Exception" << endl;
		wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

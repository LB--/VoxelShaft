
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

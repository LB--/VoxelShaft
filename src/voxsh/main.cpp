#include <string>
#include <vector>

int main(int, char const *const *plain_args)
{
	std::basic_string<char const *> const temp {plain_args};
	std::vector<std::string> const args {std::begin(temp), std::end(temp)};
	//
}

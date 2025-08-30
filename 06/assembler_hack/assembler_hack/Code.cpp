#include "Code.h"
#include "const.h"

std::string Code::dest(std::string dest)
{
	if (dest.empty()) return "";
	return dests.at(dest);
}

std::string Code::comp(std::string comp)
{
	if (comp.empty()) return "";

	return comps.at(comp);
}

std::string	Code::jump(std::string jump)
{
	if (jump.empty()) return "";
	return jumps.at(jump);
}

#include "Code.h"
#include "const.h"

std::string Code::dest(std::string dest)
{
	if (dest.empty()) return "000";
	return dests.at(dest);
}

std::string Code::comp(std::string comp)
{
	if (comp.empty()) return "0000000";

	return comps.at(comp);
}

std::string	Code::jump(std::string jump)
{
	if (jump.empty()) return "000";
	return jumps.at(jump);
}

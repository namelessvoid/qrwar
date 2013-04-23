#include "tostring.hpp"
#include <sstream>

std::string intToString(int number)
{
	std::ostringstream ssIn;
	ssIn << number;
	return ssIn.str();
}
std::string floatToString(float number)
{
	std::ostringstream ssIn;
	ssIn << number;
	return ssIn.str();
}
std::string floatToString(double number)
{
	std::ostringstream ssIn;
	ssIn << number;
	return ssIn.str();
}

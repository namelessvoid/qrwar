#include "config/xmlhelper.hpp"

#include <tinyxml2.h>
#include <iostream>

namespace qrw
{
	void XMLHelper::setParsingErrorMsg(std::string parsingerrormsg)
	{
		this->parsingerrormsg = parsingerrormsg;
	}

	std::string XMLHelper::getParsingErrorMsg()
	{
		return parsingerrormsg;
	}
	
	void XMLHelper::printAttributeError(int error, std::string attributename)
	{
		if(error == tinyxml2::XML_NO_ATTRIBUTE)
		{
			std::cerr << getParsingErrorMsg() << "attribute '" << attributename
				<< "'' in 'tile' does not exist!\n";
		}
		else if(error == tinyxml2::XML_WRONG_ATTRIBUTE_TYPE)
		{
			std::cerr << getParsingErrorMsg() << "attribute '" << attributename
				<< "' in 'tile' has wrong type!\n";
		}
	}
}
#include "config/xmlhelper.hpp"

#include <iostream>

namespace qrw
{
	void XMLHelper::setParsingErrorMsg(std::string parsingerrormsg)
	{
		this->_parsingerrormsg = parsingerrormsg;
	}

	std::string XMLHelper::getParsingErrorMsg()
	{
		return _parsingerrormsg;
	}
	
	void XMLHelper::printDocumentLoadError(std::string filepath)
	{
		std::cerr << getParsingErrorMsg() << "error loading file '" << filepath << "'.\n";
	}

	void XMLHelper::printTagMissingError(std::string tagname)
	{
		std::cerr << getParsingErrorMsg() << "no such tag '" << tagname << "'.\n";
	}

	void XMLHelper::printAttributeError(tinyxml2::XMLError error, std::string attributename)
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

#ifndef QRW_XMLHELPER_HPP
#define QRW_XMLHELPER_HPP

#include <string>
#include <tinyxml2.h>

namespace qrw
{
	class XMLHelper
	{
		public:
			void setParsingErrorMsg(std::string parsingerrormsg);
			std::string getParsingErrorMsg();

		protected:
			void printAttributeError(tinyxml2::XMLError error, std::string attributename);

		private:
			std::string parsingerrormsg;
	};
}

#endif
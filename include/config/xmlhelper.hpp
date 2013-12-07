#ifndef QRW_XMLHELPER_HPP
#define QRW_XMLHELPER_HPP

#include <string>

namespace qrw
{
	class XMLHelper
	{
		public:
			void setParsingErrorMsg(std::string parsingerrormsg);
			std::string getParsingErrorMsg();

		protected:
			void printAttributeError(int error, std::string attributename);

		private:
			std::string parsingerrormsg;
	};
}

#endif
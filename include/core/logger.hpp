#ifndef QRW_LOGGER_HPP
#define QRW_LOGGER_HPP

#include <string>

namespace qrw {

class Logger
{
public:
	Logger();

	Logger(std::ostream& informationStream, std::ostream& warningStream, std::ostream& errorStream);

	~Logger();

	void logInformation(const std::string& message) const;

	void logWarning(const std::string& message) const;

	void logError(const std::string& message) const;

	void setPrefix(const std::string& prefix);

private:
	std::string prefix_;

	std::ostream& informationStream_;
	std::ostream& warningStream_;
	std::ostream& errorStream_;

	Logger(const Logger& rhs) = delete;

	Logger& operator=(const Logger& rhs) = delete;
};


} // namespace qrw

#endif // QRW_LOGGER_HPP

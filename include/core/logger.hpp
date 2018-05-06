#ifndef QRW_LOGGER_HPP
#define QRW_LOGGER_HPP

#include <string>

namespace qrw {

class Logger
{
public:
	Logger();

	~Logger();

	void Information(const std::string& message) const;

	void Waring(const std::string& message) const;

	void Error(const std::string& message) const;

private:
	Logger(const Logger& rhs) = delete;

	Logger& operator=(const Logger& rhs) = delete;
};


} // namespace qrw

#endif // QRW_LOGGER_HPP

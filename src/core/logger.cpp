#include "core/logger.hpp"

#include <iostream>

namespace qrw
{

Logger::Logger()
  : Logger(std::cout, std::cerr, std::cerr)
{
}

Logger::Logger(std::ostream& informationStream, std::ostream& warningStream, std::ostream& errorStream)
  : prefix_("DefaultLogger"),
    informationStream_(informationStream),
    warningStream_(warningStream),
    errorStream_(errorStream)
{
}

Logger::~Logger()
{
}

void Logger::logInformation(const std::string& message) const
{
    informationStream_ << "(info) " << prefix_ << ": " << message << std::endl;
}

void Logger::logWarning(const std::string& message) const
{
    warningStream_ << "(warn) " << prefix_ << ": " << message << std::endl;
}

void Logger::logError(const std::string& message) const
{
    errorStream_ << "(err) " << prefix_ << ": " << message << std::endl << std::flush;
}

void Logger::setPrefix(const std::string& prefix)
{
    prefix_ = prefix;
}

} // namespace qrw

#include "core/logger.hpp"

#include <iostream>

namespace qrw
{

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::Information(const std::string& message) const
{
    std::cout << message << std::endl;
}

void Logger::Waring(const std::string& message) const
{
    std::cerr << message << std::endl;
}

void Logger::Error(const std::string& message) const
{
    std::cerr << message << std::endl << std::flush;
}

} // namespace qrw

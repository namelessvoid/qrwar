#ifndef QRW_MAPVALIDATOR_HPP
#define QRW_MAPVALIDATOR_HPP

#include <yaml-cpp/yaml.h>

#include "core/logger.hpp"

namespace qrw {

class MapValidator
{
public:
	MapValidator(Logger* logger = nullptr);

	~MapValidator();

	bool validate(const std::vector<YAML::Node>& mapContent) const;

private:
	bool validateObjectsDocument(const YAML::Node& objects) const;

	std::unique_ptr<Logger> logger_;

	MapValidator(const MapValidator& rhs) = delete;

	MapValidator& operator=(const MapValidator& rhs) = delete;
};


} // namespace qrw

#endif // QRW_MAPVALIDATOR_HPP

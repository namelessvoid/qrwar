#include "game/skirmish/mapvalidator.hpp"

#include <iostream>

namespace qrw
{

MapValidator::MapValidator(Logger* logger)
    : logger_(logger)
{
    if(logger_ == nullptr)
        logger_.reset(new Logger());
        
    logger_->setPrefix("MapValidator");
}

MapValidator::~MapValidator()
{
}

bool MapValidator::validate(const std::vector<YAML::Node>& mapContent) const
{
    if(mapContent.size() != 2)
    {
        logger_->logWarning("Map must contain exactly 2 yaml documents (description and content)");
        return false;
    }

    if(!validateObjectsDocument(mapContent[1]))
        return false;

    return true;
}

bool MapValidator::validateObjectsDocument(const YAML::Node& objects) const
{
    size_t boardCount = 0;
    size_t deploymentZoneCount = 0;

    for(auto& object : objects)
    {
        if(!object["type"])
        {
            logger_->logWarning("Object does not contain mandatory \"type\" key");
            return false;
        }

        std::string type = object["type"].as<std::string>();
        if(type == "qrw::Board")
            ++boardCount;
        else if(type == "qrw::DeploymentZone")
            ++deploymentZoneCount;
        else
        {
            logger_->logWarning("Object has invalid \"type\": \"" + type + "\"");
            return false;
        }
    }

    if(boardCount != 1)
    {
        logger_->logWarning("Map must contain exactly one \"qrw::Board\"");
        return false;
    }

    if(deploymentZoneCount < 2)
    {
        logger_->logWarning("Map must contain at least two \"qrw::DeploymentZone\"s");
        return false;
    }

    return true;
}

} // namespace qrw

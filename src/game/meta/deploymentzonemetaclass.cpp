#include "game/meta/deploymentzonemetaclass.hpp"

#include <string>

#include "game/deploymentzone.hpp"

namespace qrw
{

DeploymentZoneMetaClass::DeploymentZoneMetaClass(const MetaManager& metaManager)
    : MetaClass(metaManager)
{
}

DeploymentZoneMetaClass::~DeploymentZoneMetaClass()
{
}

void DeploymentZoneMetaClass::serialize(const Reflectable* object, YAML::Emitter& out) const
{
    const DeploymentZone* deploymentZone = dynamic_cast<const DeploymentZone*>(object);
    assert(deploymentZone != nullptr);

    out << YAML::BeginMap;
    out << YAML::Key << "type" << YAML::Value << DeploymentZone::typeName.getStringId()
        << YAML::Key << "playerId" << YAML::Value << deploymentZone->getPlayerId()
        << YAML::Key << "zone_"
        << YAML::Value
            << YAML::BeginSeq;

                for(auto& square : deploymentZone->zone_)
                {
                    out << YAML::BeginMap
                            << YAML::Key << "x" << YAML::Value << square.getX()
                            << YAML::Key << "y" << YAML::Value << square.getY()
                        << YAML::EndMap;
                }

            out << YAML::EndSeq;
    out << YAML::EndMap;
}

void DeploymentZoneMetaClass::deserialize(Reflectable* gameObject, const YAML::Node& in) const
{
    assert(in["type"].as<std::string>() == DeploymentZone::typeName.getStringId());
    assert(dynamic_cast<DeploymentZone*>(gameObject) != nullptr);

    auto typedObject = static_cast<DeploymentZone*>(gameObject);

    YAML::Node squareNodes = in["zone_"];
    for(auto squareNode : squareNodes)
    {
        typedObject->addSquare({squareNode["x"].as<int>(), squareNode["y"].as<int>()});
    }
    typedObject->setPlayerId(in["playerId"].as<int>());
}

std::type_index DeploymentZoneMetaClass::getTypeIndex() const
{
    throw std::runtime_error("Not implemented");
}

} // namespace qrw

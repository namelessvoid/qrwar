#include "game/skirmish/meta/deploymentzonemetaclass.hpp"

#include <string>

#include "game/deploymentzone.hpp"

namespace qrw
{

DeploymentZoneMetaClass::DeploymentZoneMetaClass(const MetaManager& metaManager)
    : MetaClass(metaManager)
{
}

void DeploymentZoneMetaClass::serialize(const Reflectable* object, YAML::Emitter& out) const
{
    const DeploymentZone* deploymentZone = dynamic_cast<const DeploymentZone*>(object);
    assert(deploymentZone != nullptr);

    out << YAML::BeginMap;
    serializeTypeName(DeploymentZone::typeName.getStringId(), out);

    out << YAML::Key << "playerId" << YAML::Value << deploymentZone->getPlayerId()
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

Reflectable* DeploymentZoneMetaClass::deserialize(const YAML::Node& in) const
{
    auto deploymentZone = new DeploymentZone();

    YAML::Node squareNodes = in["zone_"];
    for(auto squareNode : squareNodes)
    {
        deploymentZone->addSquare({squareNode["x"].as<int>(), squareNode["y"].as<int>()});
    }
    deploymentZone->setPlayerId(in["playerId"].as<int>());

    return deploymentZone;
}

std::type_index DeploymentZoneMetaClass::getTypeIndex() const
{
    throw std::runtime_error("Not implemented");
}

} // namespace qrw

#include "game/meta/terrainmetaclass.hpp"

#include "engine/terrain.hpp"

namespace qrw
{

TerrainMetaClass::TerrainMetaClass()
{
}

TerrainMetaClass::~TerrainMetaClass()
{
}

void TerrainMetaClass::serialize(const GameObject* object, YAML::Emitter& out) const
{
	const Terrain* terrain = dynamic_cast<const Terrain*>(object);
	assert(terrain != nullptr);

	out << YAML::BeginMap
			<< YAML::Key << "type" << YAML::Value << terrain->getType()
			<< YAML::Key << "position"
			<< YAML::BeginMap
				<< YAML::Key << "x" << YAML::Value << terrain->getPosition().getX()
				<< YAML::Key << "y" << YAML::Value << terrain->getPosition().getY()
			<< YAML::EndMap
			<< YAML::EndMap;
}

GameObject* TerrainMetaClass::deserialize(const YAML::Node& in) const
{
	Terrain* terrain = Terrain::createTerrain(static_cast<TERRAINTYPES>(in["type"].as<int>()));
	terrain->setPosition({in["position"]["x"].as<int>(), in["position"]["y"].as<int>()});
	return terrain;
}

std::type_index TerrainMetaClass::getTypeIndex() const
{
	Terrain tmpInstance;
	return typeid(tmpInstance);
}

} // namespace qrw



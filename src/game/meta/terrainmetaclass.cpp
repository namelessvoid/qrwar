#include "game/meta/terrainmetaclass.hpp"

#include "engine/terrain.hpp"

namespace qrw
{

TerrainMetaClass::TerrainMetaClass(const MetaManager& metaManager)
	: MetaClass(metaManager)
{
}

TerrainMetaClass::~TerrainMetaClass()
{
}

void TerrainMetaClass::serialize(const Reflectable* object, YAML::Emitter& out) const
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

void TerrainMetaClass::deserialize(Reflectable* gameObject, const YAML::Node& in) const
{
	assert(dynamic_cast<Terrain*>(gameObject)!=nullptr);

	Terrain* terrain = static_cast<Terrain*>(gameObject);
	terrain->setPosition({in["position"]["x"].as<int>(), in["position"]["y"].as<int>()});
}

std::type_index TerrainMetaClass::getTypeIndex() const
{
	Terrain tmpInstance;
	return typeid(tmpInstance);
}

} // namespace qrw



#include "game/skirmish/meta/terrainmetaclass.hpp"

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
			<< YAML::Key << "type_" << YAML::Value << static_cast<int>(terrain->_type)
			<< YAML::Key << "position_"
			<< YAML::BeginMap
				<< YAML::Key << "x_" << YAML::Value << terrain->_position.getX()
				<< YAML::Key << "y_" << YAML::Value << terrain->_position.getY()
			<< YAML::EndMap
		<< YAML::EndMap;
}

Reflectable* TerrainMetaClass::deserialize(const YAML::Node& in) const
{
	Terrain* terrain = new Terrain();
	terrain->setPosition({in["position_"]["x_"].as<int>(), in["position_"]["y_"].as<int>()});
	terrain->_type = static_cast<TERRAINTYPES>(in["type_"].as<int>());
	return terrain;
}

std::type_index TerrainMetaClass::getTypeIndex() const
{
	Terrain tmpInstance;
	return typeid(tmpInstance);
}

} // namespace qrw



#include "game/meta/boardmetaclass.hpp"

#include "meta/metamanager.hpp"

#include "engine/terrain.hpp"

#include <iostream>

namespace qrw
{

void BoardMetaClass::serialize(const GameObject* object, YAML::Emitter& out) const
{
	const Board* board = dynamic_cast<const Board*>(object);
	assert(board != nullptr);

	const MetaClass* terrainMetaClass = MetaManager::getMetaClassFor<Terrain>();

	out << YAML::BeginMap
		<< YAML::Key << Board::typeName.getStringId()
		<< YAML::Value
		<< YAML::BeginMap
			<< YAML::Key << "size" << YAML::BeginMap
				<< YAML::Key << "width" << YAML::Value << board->getWidth()
				<< YAML::Key << "height" << YAML::Value << board->getHeight()
			<< YAML::EndMap
			<< YAML::Key << "terrains"
			<< YAML::Value << YAML::BeginSeq;

				for(auto& terrainIter : board->getTerrains())
				{
					terrainMetaClass->serialize(terrainIter.second, out);
				}

			out << YAML::EndSeq;
		out << YAML::EndMap;
		out << YAML::EndMap;
}

GameObject* BoardMetaClass::deserialize(const YAML::Node& in) const
{
	Board* board = new Board();

	board->setWidth(in["size"]["width"].as<unsigned int>());
	board->setHeight(in["size"]["height"].as<unsigned int>());

	return board;
}

std::type_index BoardMetaClass::getTypeIndex() const
{
	Board tmpInstance;
	return typeid(tmpInstance);
}

} // namespace qrw





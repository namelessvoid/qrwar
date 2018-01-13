#include "game/meta/boardmetaclass.hpp"

#include "meta/metamanager.hpp"

#include "engine/terrain.hpp"

#include <iostream>

namespace qrw
{

void BoardMetaClass::serialze(GameObject* object, YAML::Emitter& out) const
{
	Board* board = dynamic_cast<Board*>(object);
	assert(board != nullptr);

	const MetaClass* terrainMetaClass = MetaManager::getMetaClassFor<Terrain>();

	out << YAML::BeginMap;
	out << YAML::Key << "terrains";
	out << YAML::Value << YAML::BeginSeq;

	for(auto& terrainIter : board->getTerrains())
	{
		terrainMetaClass->serialze(terrainIter.second, out);
	}

	out << YAML::EndSeq;
	out << YAML::EndMap;
}

std::type_index BoardMetaClass::getTypeIndex() const
{
	Board tmpInstance;
	return typeid(tmpInstance);
}

} // namespace qrw





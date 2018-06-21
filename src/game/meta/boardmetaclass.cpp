#include "game/meta/boardmetaclass.hpp"

#include "meta/metamanager.hpp"
#include "meta/properties/tproperty.hpp"

#include "engine/terrain.hpp"

#include <iostream>

namespace qrw
{

BoardMetaClass::BoardMetaClass()
{
	properties_[0].reset(new TProperty<Board,unsigned int>(&Board::_width, "_width"));
	properties_[1].reset(new TProperty<Board,unsigned int>(&Board::_height, "_height"));
}

void BoardMetaClass::serialize(const Reflectable* object, YAML::Emitter& out) const
{
	const Board* board = dynamic_cast<const Board*>(object);
	assert(board != nullptr);

	const MetaClass* terrainMetaClass = MetaManager::getMetaClassFor<Terrain>();

	out << YAML::BeginMap
		<< YAML::Key << "type" << YAML::Value << Board::typeName.getStringId();
		properties_[0]->serialize(object, out);
		properties_[1]->serialize(object, out);
	out << YAML::Key << "terrains"
		<< YAML::Value
			<< YAML::BeginSeq;

				for(auto& terrainIter : board->getTerrains())
				{
					terrainMetaClass->serialize(terrainIter.second, out);
				}

			out << YAML::EndSeq;
		out << YAML::EndMap;
}

void BoardMetaClass::deserialize(Reflectable* gameObject, const YAML::Node& in) const
{
	const MetaClass* terrainMetaClass = MetaManager::getMetaClassFor<Terrain>();

	Board* board = new Board();

	properties_[0]->deserialize(gameObject, in);
	properties_[1]->deserialize(gameObject, in);

	YAML::Node terrains = in["terrains"];

	for(size_t i = 0; i < terrains.size(); ++i)
	{
		Terrain* terrain = new Terrain();
		terrainMetaClass->deserialize(terrain, terrains[i]);
		board->setTerrain(terrain->getPosition(), terrain);
	}
}

std::type_index BoardMetaClass::getTypeIndex() const
{
	Board tmpInstance;
	return typeid(tmpInstance);
}

} // namespace qrw





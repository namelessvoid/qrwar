#include "game/meta/boardmetaclass.hpp"

namespace qrw
{

void BoardMetaClass::serialze(YAML::Emitter &out)
{
}

std::type_index BoardMetaClass::getTypeIndex() const
{
	Board tmpInstance;
	return typeid(tmpInstance);
}

} // namespace qrw





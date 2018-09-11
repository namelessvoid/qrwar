#ifndef QRW_WALLMETACLASS_HPP
#define QRW_WALLMETACLASS_HPP

#include "structuremetaclass.hpp"

#include "game/skirmish/wall.hpp"

namespace qrw
{

class WallMetaClass : public StructureMetaClass
{
public:
	WallMetaClass(MetaManager& metaManager) : StructureMetaClass(metaManager) {}

protected:
	Reflectable* createInstance() const { return new Wall(); }
};

} // namespace qrw

#endif //QRW_WALLMETACLASS_HPP

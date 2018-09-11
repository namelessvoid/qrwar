#include "structuremetaclass.hpp"

#include "game/skirmish/stairs.hpp"

#ifndef QRW_STAIRSMETACLASS_HPP
#define QRW_STAIRSMETACLASS_HPP

namespace qrw
{

class StairsMetaClass : public StructureMetaClass
{
public:
	StairsMetaClass(MetaManager& metaManager) : StructureMetaClass(metaManager) {}

protected:
	Reflectable* createInstance() const override { return new Stairs(); }
};

}

#endif //QRW__STAIRSMETACLASS_HPP

#include "structuremetaclass.hpp"

#include "game/skirmish/stairs.hpp"

#include "meta/properties/tclassproperty.hpp"

#ifndef QRW_STAIRSMETACLASS_HPP
#define QRW_STAIRSMETACLASS_HPP

namespace qrw
{

class StairsMetaClass : public StructureMetaClass
{
public:
	StairsMetaClass(MetaManager& metaManager) : StructureMetaClass(metaManager)
	{
		properties_.push_back(std::make_unique<TClassProperty<Stairs,Coordinates>>(&Stairs::face_, "face_", metaManager));
	}

protected:
	Reflectable* createInstance() const override { return new Stairs(); }
};

}

#endif //QRW__STAIRSMETACLASS_HPP

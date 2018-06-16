#ifndef QRW_TERRAINMETACLASS_HPP
#define QRW_TERRAINMETACLASS_HPP

#include "meta/reflectable.hpp"
#include "meta/metaclass.hpp"

namespace qrw {

class TerrainMetaClass : public MetaClass
{
public:
    TerrainMetaClass();

    ~TerrainMetaClass();

	virtual void serialize(const Reflectable* object, YAML::Emitter& out) const final override;

	virtual void deserialize(Reflectable* gameObject, const YAML::Node& in) const final override;

    virtual std::type_index getTypeIndex() const override;

private:
    TerrainMetaClass(const TerrainMetaClass& rhs) = delete;

    TerrainMetaClass& operator=(const TerrainMetaClass& rhs) = delete;
};


} // namespace qrw

#endif // QRW_TERRAINMETACLASS_HPP

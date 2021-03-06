#ifndef QRW_BOARDMETACLASS_HPP
#define QRW_BOARDMETACLASS_HPP

#include "meta/metaclass.hpp"
#include "meta/properties/iproperty.hpp"

#include "engine/board.hpp"

namespace qrw {

class BoardMetaClass final : public MetaClass
{
public:
    BoardMetaClass(const MetaManager& metaManager);

    ~BoardMetaClass() override = default;

	virtual void serialize(const Reflectable* object, YAML::Emitter& out) const final override;

	virtual Reflectable* deserialize(const YAML::Node& in) const final override;

private:
    std::array<std::unique_ptr<IProperty>,4> properties_;
};


} // namespace qrw

#endif // QRW_BOARDMETACLASS_HPP

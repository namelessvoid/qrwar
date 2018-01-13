#ifndef QRW_BOARDMETACLASS_HPP
#define QRW_BOARDMETACLASS_HPP

#include "meta/metaclass.hpp"

#include "engine/board.hpp"

namespace qrw {

class BoardMetaClass final : public MetaClass
{
public:
    BoardMetaClass()
    {}

    ~BoardMetaClass()
    {}

    virtual void serialze(GameObject* object, YAML::Emitter &out) const final override;

    virtual std::type_index getTypeIndex() const override;

private:
    BoardMetaClass(const BoardMetaClass& rhs) = delete;

    BoardMetaClass& operator=(const BoardMetaClass& rhs) = delete;
};


} // namespace qrw

#endif // QRW_BOARDMETACLASS_HPP

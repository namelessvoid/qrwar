#ifndef QRW_METAMANAGER_HPP
#define QRW_METAMANAGER_HPP

#include <map>
#include <memory>
#include <cassert>

#include "metaclass.hpp"

#include "core/sid.hpp"

namespace qrw {

class MetaManager
{
public:
    MetaManager();
    ~MetaManager();

    template<class TMetaClass>
    void registerMetaClass(const SID& typeName);

    template<class TClass>
    const MetaClass* getMetaClassFor() const;

private:
    typedef std::map<SID,std::unique_ptr<MetaClass> > MetaClassMap;
    MetaClassMap metaClasses_;

    MetaManager(const MetaManager& rhs) = delete;
    MetaManager& operator=(const MetaManager& rhs) = delete;
};

template<class TMetaClass>
void MetaManager::registerMetaClass(const SID& typeName)
{
    assert(metaClasses_.find(typeName) == metaClasses_.end());

    metaClasses_[typeName] = std::unique_ptr<TMetaClass>(new TMetaClass(*this));
}

template<class TClass>
const MetaClass* MetaManager::getMetaClassFor() const
{
    assert(metaClasses_.find(TClass::typeName) != metaClasses_.end());

    return metaClasses_.find(TClass::typeName)->second.get();
}


} // namespace qrw

#endif // QRW_METAMANAGER_HPP

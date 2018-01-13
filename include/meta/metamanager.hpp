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
    template<class TMetaClass>
    static void registerMetaClass(const SID& typeName);

    template<class TClass>
    static const MetaClass* getMetaClassFor();

private:
    typedef std::map<SID,std::unique_ptr<MetaClass> > MetaClassMap;
    static MetaClassMap metaClasses_;

    // Pure static class
    MetaManager();
    ~MetaManager();
    MetaManager(const MetaManager& rhs) = delete;
    MetaManager& operator=(const MetaManager& rhs) = delete;
};

template<class TMetaClass>
void MetaManager::registerMetaClass(const SID& typeName)
{
    assert(metaClasses_.find(typeName) == metaClasses_.end());

    metaClasses_[typeName] = std::unique_ptr<TMetaClass>(new TMetaClass());
}

template<class TClass>
const MetaClass* MetaManager::getMetaClassFor()
{
    assert(metaClasses_.find(TClass::typeName) != metaClasses_.end());

    return metaClasses_[TClass::typeName].get();
}


} // namespace qrw

#endif // QRW_METAMANAGER_HPP

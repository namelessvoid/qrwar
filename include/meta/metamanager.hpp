#ifndef QRW_METAMANAGER_HPP
#define QRW_METAMANAGER_HPP

#include <map>
#include <typeindex>
#include <memory>
#include <cassert>

#include <iostream>

#include "metaclass.hpp"

namespace qrw {

class MetaManager
{
public:
    template<class TMetaClass>
    static void registerMetaClass();

    template<class TClass>
    static const MetaClass* getMetaClassFor(const TClass& object);

private:
    typedef std::map<std::type_index,std::unique_ptr<MetaClass> > MetaClassMap;
    static MetaClassMap metaClasses_;

    // Pure static class
    MetaManager();
    ~MetaManager();
    MetaManager(const MetaManager& rhs) = delete;
    MetaManager& operator=(const MetaManager& rhs) = delete;
};

template<class TMetaClass>
void MetaManager::registerMetaClass()
{
    std::cout << "Registering meta class." << std::endl << std::flush;
    MetaClass* metaClass = new TMetaClass();
    std::type_index type = metaClass->getTypeIndex();

    assert(metaClasses_.find(type) == metaClasses_.end());

    metaClasses_[type] = std::unique_ptr<MetaClass>(metaClass);
}

template<class TClass>
const MetaClass* MetaManager::getMetaClassFor(const TClass& object)
{
    std::type_index type = typeid(object);

    assert(metaClasses_.find(type) != metaClasses_.end());

    return metaClasses_[type].get();
}


} // namespace qrw

#endif // QRW_METAMANAGER_HPP

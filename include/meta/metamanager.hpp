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
    MetaManager();

    ~MetaManager();

    template<class TMetaClass>
    static void registerMetaClass();

private:
    typedef std::map<std::type_index,std::unique_ptr<MetaClass> > MetaClassMap;
    static MetaClassMap metaClasses_;

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


} // namespace qrw

#endif // QRW_METAMANAGER_HPP

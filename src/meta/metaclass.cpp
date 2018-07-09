#include "meta/metaclass.hpp"

#include "meta/metamanager.hpp"

namespace qrw
{

MetaClass::MetaClass(const MetaManager& metaManager)
	: metaManager_(metaManager)
{
}

MetaClass::~MetaClass()
{
}

} // namespace qrw

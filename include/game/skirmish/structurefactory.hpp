#ifndef QRW_STRUCTUREFACTORY_HPP
#define QRW_STRUCTUREFACTORY_HPP

#include "structure.hpp"

namespace qrw
{
class Structure;

class StructureFactory
{
public:
	Structure* createStructure(Structure::Type type);
};

} // namespace qrw

#endif //QRW_STRUCTUREFACTORY_HPP

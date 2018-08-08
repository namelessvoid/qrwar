#ifndef QRW_STRUCTUREFACTORY_HPP
#define QRW_STRUCTUREFACTORY_HPP

namespace qrw
{
class Structure;

class StructureFactory
{
public:
	Structure* createStructure(unsigned int type);
};

} // namespace qrw

#endif //QRW_STRUCTUREFACTORY_HPP

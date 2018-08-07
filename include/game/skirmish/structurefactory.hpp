#ifndef QRW_STRUCTUREFACTORY_HPP
#define QRW_STRUCTUREFACTORY_HPP

namespace qrw
{
class Structure;

class StructureFactory
{
public:
	Structure* createStructure(int type);
};

} // namespace qrw

#endif //QRW_STRUCTUREFACTORY_HPP

#ifndef QRW_IWORLDADAPTER_HPP
#define QRW_IWORLDADAPTER_HPP

#include <vector>

namespace qrw
{

template<class TSpatialRepresentation>
class IWorldAdapter
{
public:
	virtual ~IWorldAdapter() = default;

	virtual bool isAccessibleFrom(const TSpatialRepresentation& source, const TSpatialRepresentation& destination) const = 0;
	virtual std::vector<TSpatialRepresentation> getNeighborLocationsFor(const TSpatialRepresentation& location) const = 0;
};

} // namespace qrw


#endif // QRW_IWORLDADAPTER_HPP

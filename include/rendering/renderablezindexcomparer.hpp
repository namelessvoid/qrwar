#ifndef QRW_RENDERABLEZINDEXCOMPARER_HPP
#define QRW_RENDERABLEZINDEXCOMPARER_HPP

#include "renderable.hpp"

namespace qrw
{

struct RenderableZIndexComparer
{
	bool operator()(const Renderable* a, const Renderable* b) const
	{
		return a->getZIndex() < b->getZIndex();
	}
};

}

#endif //QRW_RENDERABLEZINDEXCOMPARER_HPP

#ifndef QRW_RENDERABLEZINDEXCOMPARER_HPP
#define QRW_RENDERABLEZINDEXCOMPARER_HPP

#include "renderable.hpp"

namespace qrw
{

struct RenderableZIndexComparerLess
{
	bool operator()(const Renderable* a, const Renderable* b) const
	{
		return a->getZIndex() < b->getZIndex();
	}
};

struct
{
	bool operator()(const Renderable* a, const Renderable* b) const
	{
		return a->getZIndex() > b->getZIndex();
	}
} RenderableZIndexComparerGreater;

}

#endif //QRW_RENDERABLEZINDEXCOMPARER_HPP

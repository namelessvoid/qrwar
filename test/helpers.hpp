#ifndef QRW_TEST_HELPERS_HPP
#define QRW_TEST_HELPERS_HPP

#include "gui/scene.hpp"

void clearScene()
{
	qrw::g_scene.reset();
	qrw::g_scene.update(0);
}

#endif //QRW_TEST_HELPERS_HPP

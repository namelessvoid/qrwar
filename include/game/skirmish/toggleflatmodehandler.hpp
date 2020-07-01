//
// Created by pommes on 08.07.19.
//

#ifndef QUADRULEDWAR_TOGGLEFLATMODEHANDLER_HPP
#define QUADRULEDWAR_TOGGLEFLATMODEHANDLER_HPP


#include <eventsystem/eventhandler.hpp>
#include "gui/scene.hpp"

namespace qrw
{

class ToggleFlatModeHandler : public EventHandler
{
public:
	ToggleFlatModeHandler();

	bool handleEvent(const IEvent& event) override;

	bool isFlatMode() const { return isFlatMode_; }

private:
	void toggleFlatMode();

	bool isFlatMode_ = false;
};

}


#endif //QUADRULEDWAR_TOGGLEFLATMODEHANDLER_HPP

#include "gui/ng/signal.hpp"

namespace namelessgui
{
	Signal::Signal()
	{}
	Signal::~Signal()
	{}

	void Signal::connect(std::function<void()> function)
	{
		slots.push_back(function);
	}

	void Signal::disconnectAll()
	{
		slots.clear();
	}

	void Signal::emit()
	{

		std::vector<std::function<void()>>::iterator it;
		for(it = slots.begin(); it != slots.end(); ++it)
			(*it)();
	}
}
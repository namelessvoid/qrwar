#ifndef NAMELESSGUI_SIGNAL_HPP
#define NAMELESSGUI_SIGNAL_HPP

#include <functional>
#include <vector>

namespace namelessgui
{
	class Signal
	{
		public:
			Signal();
			~Signal();

			void connect(std::function<void()> function);
			void disconnectAll();
			void emit();

		private:
			std::vector<std::function<void()>> slots ;
	};
}

#endif
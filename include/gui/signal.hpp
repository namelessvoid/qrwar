#ifndef QRW_SIGNAL_HPP
#define QRW_SIGNAL_HPP

#include <functional>
#include <vector>

namespace qrw
{
	class Signal
	{
		public:
			Signal();
			~Signal();

			void connect(std::function<void()> function);
			void emit();

		private:
			std::vector<std::function<void()>> slots ;
	};
}

#endif
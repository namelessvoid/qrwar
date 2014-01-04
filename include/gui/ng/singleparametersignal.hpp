#ifndef NAMELESSGUI_SINGLEPARAMETERSIGNAL_HPP
#define NAMELESSGUI_SINGLEPARAMETERSIGNAL_HPP

#include <functional>
#include <vector>

namespace namelessgui
{
	template <class P>
	class SingleParameterSignal
	{
		public:
			SingleParameterSignal();
			~SingleParameterSignal();

			/**
			 * @brief Connect a slot function to this signal.
			 *
			 * You can use something like this to set the parameter when invoking the emit() method:
			 * signalkeypressed.connect(std::bind(&Widget::fooCallback, this, std::placeholders::_1));
			 */
			void connect(std::function<void(P)> function);
			void disconnectAll();
			void emit(P);

		private:
			std::vector<std::function<void(P)>> slots;
	};

	template <class P>
	SingleParameterSignal<P>::SingleParameterSignal()
	{}

	template <class P>
	SingleParameterSignal<P>::~SingleParameterSignal()
	{}

	template <class P>
	void SingleParameterSignal<P>::connect(std::function<void(P)> function)
	{
		slots.push_back(function);
	}

	template <class P>
	void SingleParameterSignal<P>::disconnectAll()
	{
		slots.clear();
	}

	template <class P>
	void SingleParameterSignal<P>::emit(P p)
	{
		typename std::vector<std::function<void(P)>>::iterator it;
		for(it = slots.begin(); it != slots.end(); ++it)
			(*it)(p);
	}
}
#endif
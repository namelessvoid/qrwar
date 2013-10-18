#ifndef QRW_SINGLEPARAMETERSIGNAL_HPP
#define QRW_SINGLEPARAMETERSIGNAL_HPP

#include <functional>
#include <vector>

namespace qrw
{
	template <class P>
	class SingleParameterSignal
	{
		public:
			SingleParameterSignal();
			~SingleParameterSignal();

			void connect(std::function<void(P)> function);
			void disconnectAll();
			void emit();

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
	void SingleParameterSignal<P>::emit()
	{
		typename std::vector<std::function<void(P)>>::iterator it;
		for(it = slots.begin(); it != slots.end(); ++it)
			(*it)();
	}
}
#endif
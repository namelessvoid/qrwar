#ifndef NAMELESSGUI_SIGNAL_HPP
#define NAMELESSGUI_SIGNAL_HPP

#include <functional>
#include <vector>

namespace namelessgui
{

/**
 * A generic Signal class.
 *
 * A Signal can be used to register callback methods which are notified
 * when the Signal is emitted using emit(). The parameters that are passed
 * are specified by the variadic template Params. Registered methods
 * have to match this interface.
 *
 * Example: To declare a Signal that passes an integer and a float to its registered
 * callbacks,
 *
 * @code
 * Signal<int, float> mySignal;
 * @endcode
 *
 * can be used.
 *
 * @tparam Params A set of parameters which are passed to the registered callback
 *                methods.
 */
template<typename... Params>
class Signal
{
public:
	/**
	 * Convenience typedef for a slot.
	 *
	 * A slot basically is a std::function object
	 * which maches the Signal interface of Params.
	 */
	typedef std::function<void(Params... parameters)> slot;

	/**
	 * Connect a new function to the Signal.
	 *
	 * This adds an new callback function to the Signal. On emit(), this function is
	 * called together with all the other registered functions. Note, that the interface
	 * (Signal::slot) of the function has to match the Signal interface Params.
	 *
	 * @param function The function to connect to this Signal.
	 */
	void connect(slot function);

	/**
	 * Disconnect all callbacks.
	 *
	 * This method disconnects all callbacks previously added via Signal::connect().
	 */
	void disconnectAll();

	/**
	 * Emit the signal with a set of parameters.
	 *
	 * This emits the Signal with given parameters. For example, to emit
	 *
	 * @code
	 * Signal<int, float> mySignal;
	 * @endcode
	 *
	 * you can use
	 *
	 * @code
	 * mySignal.emit(100, 2.3);
	 * @endcode
	 *
	 * @param parameters The parameters that are passed to the registered callback functions.
	 */
	void emit(Params... parameters) const;


private:
	/**
	 * Vector that contains all slots registered to this Signal.
	 */
	std::vector<slot> mSlots;
};

template<typename... Params>
void Signal<Params...>::connect(slot function)
{
	mSlots.push_back(function);
}

template<typename... Params>
void Signal<Params...>::disconnectAll()
{
	mSlots.clear();
}

template<typename... Params>
void Signal<Params...>::emit(Params... parameters) const
{
	for(auto iter = mSlots.begin(); iter != mSlots.end(); ++iter)
		(*iter)(parameters...);
}

} // namespace namelessgui

#endif // NAMELESSGUI_SIGNAL_HPP


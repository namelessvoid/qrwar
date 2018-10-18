#ifndef QRW_SKIRMISHPREPARATIONPLAYEROPTIONS_HPP
#define QRW_SKIRMISHPREPARATIONPLAYEROPTIONS_HPP

#include <string>

#include "gui/ng/window.hpp"

namespace namelessgui
{
class LineInput;
}

namespace qrw
{

class SkirmishPreparationPlayerOptions : public namelessgui::Window
{
public:
	SkirmishPreparationPlayerOptions();

	SkirmishPreparationPlayerOptions(const SkirmishPreparationPlayerOptions&) = delete;
	SkirmishPreparationPlayerOptions& operator=(const SkirmishPreparationPlayerOptions&) = delete;

	const std::string& getPlayerName();
	void setPlayerName(const std::string& name);

private:
	namelessgui::LineInput* playerNameInput_;
};

} // namespace qrw

#endif //QRW_SKIRMISHPREPARATIONPLAYEROPTIONS_HPP

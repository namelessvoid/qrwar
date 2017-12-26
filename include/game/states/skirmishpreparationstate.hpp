#ifndef QRW_SKIRMISHPREPARATIONSTATE_HPP
#define QRW_SKIRMISHPREPARATIONSTATE_HPP

namespace qrw {

class SkirmishPreparationState
{
public:
	SkirmishPreparationState();

	~SkirmishPreparationState();

private:
	SkirmishPreparationState(const SkirmishPreparationState& rhs) = delete;

	SkirmishPreparationState& operator=(const SkirmishPreparationState& rhs) = delete;
};


} // namespace qrw

#endif // QRW_SKIRMISHPREPARATIONSTATE_HPP

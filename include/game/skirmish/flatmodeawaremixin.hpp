#ifndef QRW_FLATMODEAWAREMIXIN_HPP
#define QRW_FLATMODEAWAREMIXIN_HPP

namespace qrw {

class FlatModeAwareMixin
{
public:
	FlatModeAwareMixin()
		: isFlatMode_(false)
	{}

	virtual ~FlatModeAwareMixin() = default;

	inline void setFlatMode(bool isFlatMode) {
		isFlatMode_ = isFlatMode;
		flatModeChanged();
	}
	inline bool isFlatMode() const { return isFlatMode_; }

protected:
	virtual void flatModeChanged() = 0;

private:
	bool isFlatMode_;
};

} // namespace qrw

#endif //QRW_FLATMODEAWAREMIXIN_HPP

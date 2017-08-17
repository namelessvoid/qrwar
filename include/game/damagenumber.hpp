#ifndef QRW_DAMAGENUMBER_HPP
#define QRW_DAMAGENUMBER_HPP

#include "foundation/gameobject.hpp"

namespace qrw
{

class DamageNumber : public GameObject
{
public:
    DamageNumber(int inflictedDamage);
};

} // namespace qrw

#endif // QRW_DAMAGENUMBER_HPP

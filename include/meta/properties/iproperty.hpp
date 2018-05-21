#ifndef QRW_IPROPERTY_HPP
#define QRW_IPROPERTY_HPP

#include <string>

namespace YAML
{
class Emitter;
class Node;
}

namespace qrw {

class Reflectable;

class IProperty
{
public:
	virtual void serialize(const Reflectable* object, YAML::Emitter& out) const = 0;

	virtual void deserialize(Reflectable* object, const YAML::Node& in) const = 0;

	const std::string& getName() const { return name_; }

protected:
	IProperty(const std::string& name) { name_ = name; }

	virtual ~IProperty() {};

private:
	IProperty(const IProperty& rhs) = delete;

	IProperty& operator=(const IProperty& rhs) = delete;

	std::string name_;
};


} // namespace qrw

#endif // QRW_IPROPERTY_HPP

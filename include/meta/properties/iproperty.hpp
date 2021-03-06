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
class MetaManager;

class IProperty
{
public:
	IProperty(const IProperty& rhs) = delete;
	IProperty& operator=(const IProperty& rhs) = delete;

	virtual ~IProperty() = default;

	virtual void serialize(const Reflectable* object, YAML::Emitter& out) const = 0;

	virtual void deserialize(Reflectable* object, const YAML::Node& in) const = 0;

	const std::string& getName() const { return name_; }

	const MetaManager& getMetaManager() const { return metaManager_; }

protected:
	explicit IProperty(const std::string& name, const MetaManager& metaManager)
		: name_(name),
		  metaManager_(metaManager)
	{}

private:
	std::string name_;

	const MetaManager& metaManager_;
};


} // namespace qrw

#endif // QRW_IPROPERTY_HPP

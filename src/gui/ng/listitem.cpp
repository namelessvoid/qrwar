#include "gui/ng/listitem.hpp"

namespace namelessgui
{

ListItem::ListItem()
{
	text_ = new Text();
	addWidget(text_);
}

ListItem::~ListItem()
{
}

} // namespace namelessgui

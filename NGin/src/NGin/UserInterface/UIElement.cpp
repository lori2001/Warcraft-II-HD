#include "UIElement.h"

namespace ng
{
	std::vector<size_t> UIElement::elements_;
	int UIElement::blockingException_ = -1;
}
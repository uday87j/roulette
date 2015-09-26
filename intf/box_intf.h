#ifndef BOX_INTF_H_
#define BOX_INTF_H_

#include <cstdint>

// box_intf.h
namespace rt	{
	class box_intf	{
	public:
		virtual std::uint32_t id() const = 0;
	};
}
#endif

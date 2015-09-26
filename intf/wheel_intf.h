#ifndef WHEEL_INTF_H_
#define WHEEL_INTF_H_

#include <cstdint>

// wheel_intf.h
namespace rt	{
	class wheel_intf	{
	public:

		virtual void spin() = 0;

		virtual void halt() = 0;

		virtual void place_ball_into_bin(const std::uint32_t id) = 0;

		virtual std::uint32_t resulting_bin_id() = 0;

		virtual ~wheel_intf()	{}
	};
}
#endif

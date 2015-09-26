#ifndef PAYOUT_INTF_H_
#define PAYOUT_INTF_H_

#include <cstdint>

// payout_intf.h
namespace rt	{
	class payout_intf	{
	public:

		virtual std::int32_t value() const = 0;
	};
}
#endif

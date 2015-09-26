#ifndef STRATEGY_INTF_H_
#define STRATEGY_INTF_H_

#include "bet_intf.h"

// strategy_intf.h
namespace rt	{

	class strategy_intf	{
	public:

		/*template <typename T>
		bet_intf* provide_bet(const T& required_info)	{}*/
		virtual bet_intf* provide_bet() = 0;

		virtual void set_bet_value(std::uint32_t low, std::uint32_t high) = 0;
	};

}
#endif
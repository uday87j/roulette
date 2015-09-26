#ifndef PLAYER_INTF_H_
#define PLAYER_INTF_H_

#include <cstdint>
#include <string>

#include "bet_intf.h"
#include "strategy_intf.h"

// player_intf.h
namespace rt	{
	class player_intf	{
	public:

		virtual std::string name() const = 0;

		virtual std::uint32_t uid() const = 0;

		virtual bet_intf* place_bet() = 0;

		virtual void handle_result(const payout_intf* payout) = 0;

		virtual std::int32_t show_balance() const = 0;

		virtual void set_strategy(strategy_intf*) = 0;

		virtual ~player_intf()	{}

	};
}
#endif

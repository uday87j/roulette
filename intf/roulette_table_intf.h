#ifndef ROULETTE_TABLE_INTF_H_
#define ROULETTE_TABLE_INTF_H_

#include <cstdint>

#include "player_intf.h"

// roulette_table_intf.h
namespace rt	{
	class roulette_table_intf	{
	public:

		virtual std::uint32_t spin_wheel_and_read_result() = 0;

		virtual void add_player(player_intf*) = 0;

		virtual void delete_player(player_intf*) = 0;

		virtual void accept_bets_from_players() = 0;

		virtual void convey_result_to_players() = 0;

		virtual void table_limit(std::uint32_t& low, std::uint32_t& high) = 0;

		virtual void clear_table() = 0;

	};
}
#endif

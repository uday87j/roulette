#ifndef ROULETTE_TABLE_H_
#define ROULETTE_TABLE_H_

#include <vector>

#include "roulette_table_intf.h"
#include "wheel_intf.h"
#include "table_intf.h"
#include "player_intf.h"
#include "payout.h"

// roulette_table.h
namespace rt	{

	class roulette_table_t : public roulette_table_intf	{
	public:

		roulette_table_t(const payout_t& seed_money);

		virtual std::uint32_t spin_wheel_and_read_result();

		virtual void add_player(player_intf*);

		virtual void delete_player(player_intf*);

		virtual void accept_bets_from_players();

		virtual void convey_result_to_players();
		
		virtual void table_limit(std::uint32_t& low, std::uint32_t& high);

		virtual void clear_table();

		payout_t balance() const;

		virtual ~roulette_table_t();

	private:

		roulette_table_t();

		wheel_intf* mh_wheel;

		table_intf* mh_table;

		std::vector<player_intf*> mh_players;

		std::vector<bet_intf*> mh_bets;	// Corresponding to mh_players

		payout_t m_balance;

	};
}
#endif

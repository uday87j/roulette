#include "roulette_table.h"
#include "bet.h"
#include "wheel.h"
#include "table.h"
#include "player.h"

#include <algorithm>

using namespace rt;

roulette_table_t::roulette_table_t(const payout_t& p)
	: mh_wheel(new wheel_t<>),
	mh_table(new table_t<coloured_box_t>)
{
	mh_players.reserve(5);	// Assumption
	mh_bets.reserve(5);	// Assumption
	m_balance.change_value(p.value());
}

roulette_table_t::~roulette_table_t()	{

	delete mh_wheel;

	delete mh_table;

	/*for (auto &i : mh_bets)	{
		delete i;
	}*/
}

void roulette_table_t::add_player(player_intf* p)	{
	mh_players.push_back(p);
	mh_bets.push_back(new straight_bet_t);
}

void roulette_table_t::delete_player(player_intf* p)	{
	auto itr = mh_players.begin();
	auto i = 0;
	for (; itr != mh_players.end(); ++itr, ++i)	{
		if ((*itr)->uid() == p->uid())	{
			break;
		}
	}
	if (itr != mh_players.end())	{
		mh_players.erase(itr);
		mh_bets.erase(mh_bets.begin() + i);
	}
}


void roulette_table_t::accept_bets_from_players()	{
	auto i	= 0;
	//TODO: Check if a player is eligible for betting
	for (auto& itr : mh_players)	{
		mh_bets[i++] = itr->place_bet();
	}
}

std::uint32_t roulette_table_t::spin_wheel_and_read_result()	{
	mh_wheel->spin();
	mh_wheel->place_ball_into_bin(0);
	mh_wheel->halt();
	return mh_wheel->resulting_bin_id();
}

void roulette_table_t::convey_result_to_players()	{
	//TODO: Consult referee & then convey the payouts
	//For now, do the calc here
	auto res = mh_wheel->resulting_bin_id();
	auto p = 0;
	for (auto& itr : mh_bets)	{
		payout_t pay(itr->calc_payout(res, mh_table->get_box_colour(res)));
		mh_players[p]->handle_result(&pay);
		m_balance -= pay;
		++p;
	}
}

void roulette_table_t::table_limit(std::uint32_t& low, std::uint32_t& high)	{
	low = 10;
	high = 1000;
}

void roulette_table_t::clear_table()	{
	//TODO
}

payout_t roulette_table_t::balance() const	{
	return m_balance;
}
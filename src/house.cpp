#include "house.h"
#include "player.h"
#include "strategy.h"

#include <iostream>

using namespace rt;
using namespace std;

house_t::house_t()
{
	
	payout_t p(1000);
	
	mh_rt = new roulette_table_t(p);
	uint32_t tab_l = 0;
	uint32_t tab_h = 0;
	mh_rt->table_limit(tab_l, tab_h);
	
	mh_players.push_back(new player_t("P1", 413213, 1000, mh_rt));	mh_players[0]->set_strategy(strategy_pool_t::instance().make_strategy_and_seed<straight_bet_strategy_t>());
	
	mh_players.push_back(new player_t("P2", 976769, 1000, mh_rt));	mh_players[1]->set_strategy(strategy_pool_t::instance().make_strategy_and_seed<street_bet_strategy_t>());
	
	mh_players.push_back(new player_t("P3", 107408, 1000, mh_rt));	mh_players[2]->set_strategy(strategy_pool_t::instance().make_strategy_and_seed<line_bet_strategy_t>());
	
	mh_players.push_back(new player_t("P4", 901408, 1000, mh_rt));	mh_players[3]->set_strategy(strategy_pool_t::instance().make_martingale_strategy(tab_l, tab_h));
	
	mh_players.push_back(new player_t("P5", 612408, 1000, mh_rt));	mh_players[4]->set_strategy(strategy_pool_t::instance().make_low_high_1326_strategy(tab_l));
}

house_t::~house_t()	{
	for (auto& itr : mh_players)	{
		delete itr;
	}
	delete mh_rt;
}

void house_t::setup()	{
	for (auto& itr : mh_players)	{
		mh_rt->add_player(itr);
	}
}

void house_t::play()	{
	for (auto i = 0; i < 10000; ++i)	{
		mh_rt->accept_bets_from_players();
		
		mh_rt->spin_wheel_and_read_result();
		
		mh_rt->convey_result_to_players();
	}

	print_rt_payouts(mh_rt);
	print_players_payouts(mh_players);
}

void house_t::shutdown()	{
	mh_rt->clear_table();
}

house_t* house_factory_t::make_house()	{
	auto h = new house_t;
	mh_houses.push_back(h);
	return h;
}

house_factory_t::~house_factory_t()	{
	for (auto& itr : mh_houses)	{
		delete itr;
	}
}

namespace rt	{
	void print_players_payouts(const std::vector<player_intf*>& mh_players)	{
		for (auto& itr : mh_players)	{
			cout << itr->name() << ": " << itr->show_balance() << endl;
		}
	}

	void print_rt_payouts(const roulette_table_t* rt)	{
		cout << "\nRT: " << rt->balance().value() << endl;
	}
}

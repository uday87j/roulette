#ifndef HOUSE_H_
#define HOUSE_H_

//#include "house_intf.h"

#include "roulette_table.h"

// house.h
namespace rt	{

	class house_t	{
	public:

		house_t();

		~house_t();

		void setup();

		void play();

		void shutdown();

	private:

		roulette_table_t* mh_rt;	// Have multiple in future, use std::vector
		std::vector<player_intf*> mh_players;
	};

	class house_factory_t	{

	public:

		static house_factory_t& instance()	{
			static house_factory_t hf;
			return hf;
		}

		~house_factory_t();

		house_t* make_house();

	private:
		house_factory_t()	{}

		std::vector<house_t*> mh_houses;
	};

	extern void print_players_payouts(const std::vector<player_intf*>& mh_players);
	extern void print_rt_payouts(const roulette_table_t* rt);
}
#endif

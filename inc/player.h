#ifndef PLAYER_H_
#define PLAYER_H_

#include <random>

#include "player_intf.h"
#include "roulette_table_intf.h"
#include "bet.h"

// player.h
namespace rt	{

	class player_t : public player_intf	{
	public:

		player_t(const std::string nm, std::uint32_t uid, std::uint32_t init_money, roulette_table_intf* rt)
			: m_name(nm),
			m_uid(uid),
			m_avail_money(init_money),
			m_rt(rt)
		{
		}

		virtual std::string name() const	{
			return m_name;
		}

		virtual std::uint32_t uid() const	{
			return m_uid;
		}

		virtual bet_intf* place_bet()	{
			return mh_strategy->provide_bet();
		}

		virtual void handle_result(const payout_intf* pay)	{
			m_avail_money += pay->value();	// TODO: House/RT should do this calc
		}

		virtual void change_rt(roulette_table_intf* rt)	{
			m_rt = rt;
		}

		virtual std::int32_t show_balance() const	{
			return m_avail_money;
		}

		void set_strategy(strategy_intf* s)	{
			mh_strategy = s;
		}

		virtual ~player_t()	{
		}

	private:

		std::string m_name;
		std::uint32_t m_uid;
		std::int32_t m_avail_money;

		roulette_table_intf* m_rt;

		strategy_intf* mh_strategy;
	};
}
#endif

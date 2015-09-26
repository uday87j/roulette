#include "strategy.h"
using namespace rt;

martingale_strategy_t::martingale_strategy_t(std::uint32_t wager_min, std::uint32_t wager_max, std::uint32_t sd)
	//: m_bet_target(0, 2),
	//m_bet_value(wager_min, wager_max),
	: m_wager_min(wager_min),
	m_wager_max(wager_max),
	m_current_wager(0),
	m_losses(0),
	m_mul_factor(1),
	m_prev_bet(nullptr),
	m_rem_bet(static_cast<remainder_bet_t*>(bet_factory::instance().make_bet<remainder_bet_t>()),
		wager_min, wager_max, sd)
{
	//m_generator.seed(sd);
}

bet_intf* martingale_strategy_t::provide_bet()	{
	
	// Assess latest outcome
	if (nullptr != m_prev_bet)	{
		if (WIN == m_prev_bet->recent_bet_outcome())	{
			m_losses = 0;
			m_mul_factor = 1;
			m_current_wager = m_wager_min;
		}
		else	{
			++m_losses;
			m_mul_factor *= 2;
		}
	}

	auto b = m_rem_bet();

	auto w = m_current_wager * m_mul_factor;
	// TODO: Some imposition required here
	if (w > m_wager_max)	{
		w = m_wager_min;
	}
	
	b->set_bet_val(w);
	m_current_wager = w;
	
	m_prev_bet = b;

	return b;
}

void martingale_strategy_t::set_bet_value(std::uint32_t l, std::uint32_t h)	{
	m_wager_min = l;
	m_wager_max = h;
	m_current_wager = l;
}

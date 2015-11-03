#ifndef STRATEGY_H_
#define STRATEGY_H_

#include "strategy_intf.h"
#include "bet.h"

#include <vector>
#include <random>

// strategy.h
namespace rt	{

	class strategy_base_t : public strategy_intf	{
	public:

		bet_intf* provide_bet()	{
			return nullptr;
		}

	};

	class straight_bet_strategy_t : public strategy_base_t	{
	public:

		straight_bet_strategy_t(std::uint32_t sd = 0)
			: m_bet_target(0, 37),
			m_bet_value(10, 50)
		{
			m_generator.seed(sd);
		}

		bet_intf* provide_bet()	{
			auto b = static_cast<straight_bet_t*>(bet_factory::instance().make_bet<straight_bet_t>());
			b->set_bet_val(m_bet_value(m_generator));
			b->set_target_id(m_bet_target(m_generator));
			return b;
		}

		void set_bet_value(std::uint32_t l, std::uint32_t h)	{
			std::uniform_int_distribution<int>::param_type p(l, h);
			m_bet_value.param(p);
		}

		void set_seed(std::uint32_t s)	{
			m_generator.seed(s);
		}

	private:

		std::default_random_engine m_generator;
		std::uniform_int_distribution<int> m_bet_target;
		std::uniform_int_distribution<int> m_bet_value;
	};

	class street_bet_strategy_t : public strategy_base_t	{
	public:

		street_bet_strategy_t(std::uint32_t sd = 0)
			: m_bet_target(1, 12),
			m_bet_value(10, 50)
		{
			m_generator.seed(sd);
		}

		bet_intf* provide_bet()	{
			auto b = static_cast<street_bet_t*>(bet_factory::instance().make_bet<street_bet_t>());
			b->set_bet_val(m_bet_value(m_generator));
			b->set_target_row(m_bet_target(m_generator));
			return b;
		}

		void set_bet_value(std::uint32_t l, std::uint32_t h)	{
			std::uniform_int_distribution<int>::param_type p(l, h);
			m_bet_value.param(p);
		}

		void set_seed(std::uint32_t s)	{
			m_generator.seed(s);
		}

	private:

		std::default_random_engine m_generator;
		std::uniform_int_distribution<int> m_bet_target;
		std::uniform_int_distribution<int> m_bet_value;
	};

	class line_bet_strategy_t : public strategy_base_t	{
	public:

		line_bet_strategy_t(std::uint32_t sd = 0)
			: m_bet_target(1, 11),
			m_bet_value(10, 50)
		{
			m_generator.seed(sd);
		}

		bet_intf* provide_bet()	{
			auto b = static_cast<line_bet_t*>(bet_factory::instance().make_bet<line_bet_t>());
			b->set_bet_val(m_bet_value(m_generator));
			b->set_target_row(m_bet_target(m_generator));
			return b;
		}

		void set_bet_value(std::uint32_t l, std::uint32_t h)	{
			std::uniform_int_distribution<int>::param_type p(l, h);
			m_bet_value.param(p);
		}

		void set_seed(std::uint32_t s)	{
			m_generator.seed(s);
		}

	private:

		std::default_random_engine m_generator;
		std::uniform_int_distribution<int> m_bet_target;
		std::uniform_int_distribution<int> m_bet_value;
	};

class low_high_strategy_t: public strategy_base_t	{
	public:

		low_high_strategy_t(std::uint32_t sd = 0)
		: m_bet_target(0, 1),
		m_bet_value(10, 50)
	{
		m_generator.seed(sd);
	}

		bet_intf* provide_bet()	{
			auto b = static_cast<low_high_bet_t*>(bet_factory::instance().make_bet<low_high_bet_t>());
			b->set_bet_val(m_bet_value(m_generator));
			b->set_target_range(m_bet_target(m_generator));
			return b;
		}

		void set_bet_value(std::uint32_t l, std::uint32_t h)	{
			std::uniform_int_distribution<int>::param_type p(l, h);
			m_bet_value.param(p);
		}

		void set_seed(std::uint32_t s)	{
			m_generator.seed(s);
		}

private:

	//low_high_bet_t* mh_bet;   //Not needed

	std::default_random_engine m_generator;
	std::uniform_int_distribution<int> m_bet_target;
	std::uniform_int_distribution<int> m_bet_value;
};

	class martingale_strategy_t : public strategy_base_t	{
	public:

		martingale_strategy_t(std::uint32_t wager_min = 0, std::uint32_t wager_max = 0, std::uint32_t sd = 0);

		virtual bet_intf* provide_bet();

		virtual void set_bet_value(std::uint32_t l, std::uint32_t h);

		void set_seed(std::uint32_t s)	{
			//m_generator.seed(s);
		}

	private:

		/*std::default_random_engine m_generator;
		std::uniform_int_distribution<int> m_bet_target;
		std::uniform_int_distribution<int> m_bet_value;*/

		std::uint32_t m_wager_min;
		std::uint32_t m_wager_max;
		std::uint32_t m_current_wager;
		std::uint32_t m_losses;
		std::uint32_t m_mul_factor;	// To avoid pow(2, m_losses)
		
		bet_intf* m_prev_bet;
		bet_randomizer_t<remainder_bet_t> m_rem_bet;

	};

	template<typename INTEGER>
	struct cirucuar_number_wheel_t	{

		cirucuar_number_wheel_t(const std::uint32_t count)
			: m_num_vec(count),
			m_count(count),
			m_index(0)	{
		}

		cirucuar_number_wheel_t(const std::vector<INTEGER>& vec)
			: m_num_vec(vec),
			m_count(vec.size()),
			m_index(0)	{

		}

		cirucuar_number_wheel_t()
		: cirucuar_number_wheel_t(0)    {}

		void set_val(const std::uint32_t index, const INTEGER val)	{
			assert(index < m_count);
			m_num_vec[m_index] = val;
		}

		void get_val(std::uint32_t index, INTEGER& val) const	{
			assert(index < m_count);
			val	= m_num_vec[m_index];
		}

		void set_index(const std::uint32_t index)	{
			assert(index < m_count);
			m_index = index;
		}

		void get_index(std::uint32_t& index) const	{
			assert(index < m_count);
			index	= m_index;
		}

		void advance()	{
			++m_index;
			m_index	= ((m_index == m_count) ? 0 : m_index);
		}

		INTEGER current() const	{
			return m_num_vec[m_index];
		}

		INTEGER next()	{
			++m_index;
			m_index == m_count ? 0 : m_index;

			return m_num_vec[m_index];
		}

	private:

		std::vector<INTEGER> m_num_vec;
		std::uint32_t m_count;
		std::uint32_t m_index;
	};


	// T should provide following API:
	//bet_intf* provide_bet()
	template<typename T>
	class strategy_1326_t : public strategy_base_t	{
	public:
		
		strategy_1326_t(T* bet, const std::uint32_t wager)
			: mh_bet_agent(bet),
			mh_bet(mh_bet_agent->provide_bet()),
			m_current_wager(wager),
			m_losses(0),
			m_factor_index(0),
			m_factors(4)	{
			
			m_factors.set_val(0, 1);
			m_factors.set_val(1, 3);
			m_factors.set_val(2, 2);
			m_factors.set_val(3, 6);
		}

		bet_intf* provide_bet()	{
			//bet_intf* b = mh_bet_agent->provide_bet();
			assert(mh_bet != nullptr);

			if (WIN == mh_bet->recent_bet_outcome())	{
				m_factors.advance();
			}
			else	{
				m_factors.set_index(0);
			}

			mh_bet->set_bet_val(m_current_wager * (m_factors.current()));

			return mh_bet;
		}

		void set_bet_value(std::uint32_t low, std::uint32_t high)	{
			m_current_wager = low;
		}

	private:

		T* mh_bet_agent;

		bet_intf* mh_bet;

		std::uint32_t m_current_wager;
		std::uint32_t m_losses;
		std::uint32_t m_factor_index;
		cirucuar_number_wheel_t<std::uint8_t> m_factors;

	};

	enum strategy_type_t	{
		STRAIGHT_BET_STRATEGY	= 0,
		STREET_BET_STRATEGY,
		LINE_BET_STRATEGY,
		LOW_HIGH_STRATEGY,
		MARTINGALE_STRATEGY,
		SYSTEM_1326_STRATEGY,
		INVALID_STRATEGY
	};

	class strategy_pool_t	{
	public:

		static strategy_pool_t& instance()	{
			static strategy_pool_t st;
			return st;
		}

		template<typename T>
		strategy_intf* make_strategy_and_seed()	{
			auto st = new T;
			mh_strategies.push_back(st);
			st->set_seed(m_seed(m_generator));
			return st;
		}

		template<typename T>
		strategy_intf* make_strategy()	{
			auto st = new T;
			mh_strategies.push_back(st);
			return st;
		}

		strategy_intf* make_martingale_strategy(const std::uint32_t min_wage, const std::uint32_t max_wage)	{
			auto st = make_strategy_and_seed <martingale_strategy_t>();
			st->set_bet_value(min_wage, max_wage);
			return st;
		}

		strategy_intf* make_low_high_1326_strategy(const std::uint32_t wager)	{
			auto lh = make_strategy<low_high_strategy_t>();
			auto st = new strategy_1326_t<low_high_strategy_t>(static_cast<low_high_strategy_t*>(lh), wager);
			mh_strategies.push_back(st);
			return st;
		}

		/*strategy_intf* make_strategy(const strategy_type_t s)	{

			switch (s)	{

				case STRAIGHT_BET_STRATEGY:
				{
					auto st = new straight_bet_strategy_t;
					mh_strategies.push_back(st);
					st->set_seed(m_seed(m_generator));
					return st;
					break;
				}

				case STREET_BET_STRATEGY:
				{
					auto st = new street_bet_strategy_t;
					mh_strategies.push_back(st);
					st->set_seed(m_seed(m_generator));
					return st;
					break;
				}

				case LINE_BET_STRATEGY:
				{
					auto st = new line_bet_strategy_t;
					mh_strategies.push_back(st);
					st->set_seed(m_seed(m_generator));
					return st;
					break;
				}

				default:
					assert(0);
					return nullptr;
			}

		}*/

	private:

		std::vector<strategy_intf*> mh_strategies;
		std::default_random_engine m_generator;
		std::uniform_int_distribution<std::uint32_t> m_seed;

	};
}
#endif

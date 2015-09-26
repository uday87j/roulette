#ifndef BET_H_
#define BET_H_

#include "bet_intf.h"
#include "table_intf.h"
#include "box.h"
#include "payout.h"

#include <cassert>
#include <random>

// bet.h
namespace rt	{
	
	class bet_base_t : public bet_intf	{
	public:

		typedef bet_base_t this_type;

        ~bet_base_t()   {}
	};

	class straight_bet_t : public bet_base_t	{
	public:

		typedef straight_bet_t this_type;

		straight_bet_t(const std::uint8_t bet_target = 0, const std::int32_t bet_val = 0);

		virtual const std::string bet_name() const	{ return "Straight Bet"; }

		virtual const std::string bet_desc() const	{ return "A “straight bet” is a bet on a single number. There are 38 possible bets, and they pay odds of 35 to 1. Each bin on the wheel pays one of the straight bets."; }

		virtual const std::string odds() const	{ return "35:1"; }

		virtual std::vector<uint8_t> get_target_box_ids() const;

		virtual std::int32_t calc_payout(std::uint32_t outcome, colour_t colour);

		virtual bet_outcome_t recent_bet_outcome();

		void set_target_id(const std::uint8_t target_id);

		void set_bet_val(const std::uint32_t bet_value);

		std::uint32_t bet_value();

	private:

		std::uint8_t m_target_id;
		std::int32_t m_bet_value;
		bet_outcome_t m_outcome;
	};

	class street_bet_t : public bet_base_t	{
	public:

		typedef street_bet_t this_type;

		street_bet_t(const std::uint8_t bet_row = 1, const std::int32_t bet_val = 0);

		virtual const std::string bet_name() const	{ return "Street Bet"; }

		virtual const std::string bet_desc() const	{ return "A “street bet” includes the three numbers in a single row, which pays 11:1. There are twelve of these bets on the table. A single bin selects one street bet; any of three bins make a street bet a winner."; }

		virtual const std::string odds() const	{ return "11:1"; }

		virtual std::vector<uint8_t> get_target_box_ids() const;

		virtual std::int32_t calc_payout(std::uint32_t outcome, colour_t colour);

		virtual bet_outcome_t recent_bet_outcome();

		void set_target_row(const std::uint8_t row);

		void set_bet_val(const std::uint32_t bet_value);

		std::uint32_t bet_value();

	protected:

		void set_box_ids(const std::uint8_t row);

	private:

		std::uint8_t m_target_row;
		std::int32_t m_bet_value;
		bet_outcome_t m_outcome;
		std::vector<uint8_t> m_boxes;

	};

	class line_bet_t : public bet_base_t	{
		public:

			typedef line_bet_t this_type;

			line_bet_t(const std::uint8_t bet_row = 1, const std::int32_t bet_val = 0);

			virtual const std::string bet_name() const	{ return "Line Bet"; }

			virtual const std::string bet_desc() const	{ return "A “line bet” is a six number block, which pays 5:1. It is essentially two adjacent street bets. There are 11 such combinations.."; }

			virtual const std::string odds() const	{ return "11:1"; }

			virtual std::vector<uint8_t> get_target_box_ids() const;

			virtual std::int32_t calc_payout(std::uint32_t outcome, colour_t colour);

			virtual bet_outcome_t recent_bet_outcome();

			void set_target_row(const std::uint8_t row);

			void set_bet_val(const std::uint32_t bet_value);

			std::uint32_t bet_value();

	private:

		street_bet_t m_bet[2];	// 2 adjacent street-bets
		bet_outcome_t m_outcome;
		std::int32_t m_bet_value;
	};

	class range12_bet_t : public bet_base_t	{
	public:

		typedef line_bet_t this_type;

		range12_bet_t(const std::uint8_t range_num = 1, const std::int32_t bet_val = 0);

		virtual const std::string bet_name() const	{ return "Range of 12s Bet"; }

		virtual const std::string bet_desc() const	{ return "Any of the three 12-number ranges (1-12, 13-24, 25-36) pays 2:1. There are just three of these bets."; }

		virtual const std::string odds() const	{ return "2:1"; }

		virtual std::vector<uint8_t> get_target_box_ids() const;

		virtual std::int32_t calc_payout(std::uint32_t outcome, colour_t colour);

		virtual bet_outcome_t recent_bet_outcome();

		void set_target_range(const std::uint8_t r);

		void set_bet_val(const std::uint32_t bet_value);

		std::uint32_t bet_value();

	private:

		bet_outcome_t m_outcome;
		std::int32_t m_bet_value;
		std::uint8_t m_selected_range;
		trange_t m_ranges[3];	// (1-12, 13-24, 25-36)
	};

	class low_high_bet_t : public bet_base_t	{
	public:

		typedef low_high_bet_t this_type;

		low_high_bet_t(const std::uint8_t range_num = 1, const std::int32_t bet_val = 0);

		virtual const std::string bet_name() const	{ return "Low-High Bet"; }

		virtual const std::string bet_desc() const	{ return "There are two 18-number ranges: 1-18 is called low, 19-36 is called high. These are called even money bets because they pay at 1:1 odds.."; }

		virtual const std::string odds() const	{ return "1:1"; }

		virtual std::vector<uint8_t> get_target_box_ids() const;

		virtual std::int32_t calc_payout(std::uint32_t outcome, colour_t colour);

		virtual bet_outcome_t recent_bet_outcome();

		void set_target_range(const std::uint8_t r);

		void set_bet_val(const std::uint32_t bet_value);

		std::uint32_t bet_value();

	private:

		bet_outcome_t m_outcome;
		std::int32_t m_bet_value;
		std::uint8_t m_selected_range;
		trange_t m_ranges[2];	// (1-18, 19-36)
	};

	class remainder_bet_t : public bet_base_t	{
	public:

		typedef remainder_bet_t this_type;

		remainder_bet_t(const std::uint8_t remainder = 1, const std::int32_t bet_val = 0);

		virtual const std::string bet_name() const	{ return "Remainder Bet"; }

		virtual const std::string bet_desc() const	{ return "The layout offers the three 12-number columns at 2:1 odds. All of the numbers in a given column have the same remainder when divided by three. Column 1 contains 1, 4, 7, etc., all of which have a remainder of 1 when divided by 3."; }

		virtual const std::string odds() const	{ return "1:1"; }

		virtual std::vector<uint8_t> get_target_box_ids() const;

		virtual std::int32_t calc_payout(std::uint32_t outcome, colour_t colour);

		virtual bet_outcome_t recent_bet_outcome();

		void set_remainder(const std::uint8_t r);

		void set_bet_val(const std::uint32_t bet_value);

		std::uint32_t bet_value();

	private:

		bet_outcome_t m_outcome;
		std::int32_t m_bet_value;
		std::uint8_t m_remainder;
	};

	class red_black_bet_t : public bet_base_t	{
	public:

		typedef red_black_bet_t this_type;

		red_black_bet_t(const colour_t c = BLACK_COLOUR, const std::int32_t bet_val = 0);

		virtual const std::string bet_name() const	{ return "Red-Black Bet"; }

		virtual const std::string bet_desc() const	{ return "The individual numbers are colored red or black in an arbitrary pattern. Note that 0 and 00 are colored green. The bets on red or black are even money bets, which pay at 1:1 odds."; }

		virtual const std::string odds() const	{ return "1:1"; }

		virtual std::vector<uint8_t> get_target_box_ids() const;

		virtual std::int32_t calc_payout(std::uint32_t outcome, colour_t colour);

		virtual bet_outcome_t recent_bet_outcome();

		void set_colour(const colour_t c);

		void set_bet_val(const std::uint32_t bet_value);

		std::uint32_t bet_value();

	private:

		bet_outcome_t m_outcome;
		std::int32_t m_bet_value;
		colour_t m_colour;
	};

	class special_five_bet_t : public bet_base_t	{
	public:

		typedef special_five_bet_t this_type;

		special_five_bet_t(std::uint8_t num = 0, const std::int32_t bet_val = 0);

		virtual const std::string bet_name() const	{ return "Special-Five Bet"; }

		virtual const std::string bet_desc() const	{ return "At one end of the layout, it is possible to place a bet on the Five numbers 0, 00, 1, 2 and 3. This pays 6:1."; }

		virtual const std::string odds() const	{ return "6:1"; }

		virtual std::vector<uint8_t> get_target_box_ids() const;

		virtual std::int32_t calc_payout(std::uint32_t outcome, colour_t colour);

		virtual bet_outcome_t recent_bet_outcome();

		void set_num(const std::uint8_t num);

		void set_bet_val(const std::uint32_t bet_value);

		std::uint32_t bet_value();

	private:

		bet_outcome_t m_outcome;
		std::int32_t m_bet_value;
		std::uint8_t m_num;
	};

	class even_odd_bet_t : public bet_base_t	{
	public:

		typedef even_odd_bet_t this_type;

		even_odd_bet_t(std::uint8_t remainder = 0, const std::int32_t bet_val = 0);

		virtual const std::string bet_name() const	{ return "Even-Odd Bet"; }

		virtual const std::string bet_desc() const	{ return "The numbers (other than 0 and 00) are also either even or odd. These bets are also even money bets.. This pays 1:1."; }

		virtual const std::string odds() const	{ return "1:1"; }

		virtual std::vector<uint8_t> get_target_box_ids() const;

		virtual std::int32_t calc_payout(std::uint32_t outcome, colour_t colour);

		virtual bet_outcome_t recent_bet_outcome();

		void set_remainder(const std::uint8_t r);

		void set_bet_val(const std::uint32_t bet_value);

		std::uint32_t bet_value();

	private:

		bet_outcome_t m_outcome;
		std::int32_t m_bet_value;
		std::uint8_t m_rem;
	};


	enum bet_type_t	{
		STRAIGHT_BET	= 0,
		STREET_BET,
		LINE_BET,
		RANGE12_BET,
		LOW_HIGH_BET,
		REMAINDER_BET,
		RED_BLACK_BET,
		FIVE_NUM_BET,
		EVEN_ODD_BET,
		IVALID_BET
	};

	class bet_factory	{
	public:

		static bet_factory& instance()	{
			static bet_factory bf;
			return bf;
		}

		~bet_factory();

		template<typename BET_T>
		bet_intf* make_bet()	{
			auto bet = new BET_T;
			mh_bets.push_back(bet);
			return bet;
		}

		//bet_intf* make_bet(const bet_type_t b);	// Deprecated

	private:
		bet_factory();

		std::vector<bet_intf*> mh_bets;
	};

	template<typename T>
	struct bet_randomizer_t	{

		bet_randomizer_t()
			: m_bet(nullptr)	{}

		bet_intf* operator()()	{
			return m_bet;	// Default behaviour
		}

	private:
		T* m_bet;
	};

	template<>
	struct bet_randomizer_t<remainder_bet_t>	{

		bet_randomizer_t(remainder_bet_t* b = nullptr, 
			const std::int32_t bet_val_min = 0, const std::int32_t bet_val_max = 0,
			const std::uint32_t seed = 0)
			: m_bet(b),
			m_bet_target(0, 2),
			m_bet_value(bet_val_min, bet_val_max)	{

			m_generator.seed(seed);
		}

		remainder_bet_t* operator()()	{
			m_bet->set_bet_val(m_bet_value(m_generator));
			m_bet->set_remainder(m_bet_target(m_generator));
			return m_bet;
		}

		void set_seed(const std::uint32_t s)	{
			m_generator.seed(s);
		}

	private:

		remainder_bet_t* m_bet;

		std::default_random_engine m_generator;
		std::uniform_int_distribution<int> m_bet_target;
		std::uniform_int_distribution<int> m_bet_value;
	};

}
#endif

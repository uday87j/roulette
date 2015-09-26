#include "bet.h"
using namespace rt;

straight_bet_t::straight_bet_t(const std::uint8_t bet_target, const std::int32_t bet_val)
	: m_target_id(bet_target),
	m_bet_value(bet_val),
	m_outcome(UNDEFINED_RES)
{}

std::vector<uint8_t> straight_bet_t::get_target_box_ids() const	{
	std::vector<uint8_t> boxes;
	boxes.push_back(m_target_id);
	return boxes;
}

std::int32_t straight_bet_t::calc_payout(std::uint32_t outcome, colour_t colour)	{
	if (outcome == m_target_id)	{
		m_outcome = WIN;
		return (m_bet_value * 35);
	}
	else	{
		m_outcome = LOSS;
		return (-m_bet_value);
	}
}

bet_outcome_t straight_bet_t::recent_bet_outcome()	{
	return m_outcome;
}

void straight_bet_t::set_target_id(const std::uint8_t target_id)	{
	m_target_id = target_id;
}

void straight_bet_t::set_bet_val(const std::uint32_t bet_value)	{
	m_bet_value = bet_value;
}

std::uint32_t straight_bet_t::bet_value()	{
	return m_bet_value;
}

street_bet_t::street_bet_t(const std::uint8_t bet_row, const std::int32_t bet_val)
	: m_target_row(bet_row),
	m_bet_value(bet_val),
	m_outcome(UNDEFINED_RES)
{
	assert(bet_row < 12);
	m_boxes.reserve(3);

	set_box_ids(bet_row);
}

std::vector<uint8_t> street_bet_t::get_target_box_ids() const	{
	return m_boxes;
}

std::int32_t street_bet_t::calc_payout(std::uint32_t outcome, colour_t colour)	{
	for (auto& id : m_boxes)	{
		if (outcome == id)	{
			m_outcome = WIN;
			return (m_bet_value * 11);
		}
	}
	m_outcome = LOSS;
	return (-m_bet_value);
}

bet_outcome_t street_bet_t::recent_bet_outcome()	{
	return m_outcome;
}

void street_bet_t::set_target_row(const std::uint8_t row)	{
	m_target_row = row;
	//m_boxes.erase(m_boxes.begin(), m_boxes.end());	//TODO: Check
	//set_box_ids(row);//TODO: Check
}

void street_bet_t::set_bet_val(const std::uint32_t bet_value)	{
	m_bet_value = bet_value;
}

std::uint32_t street_bet_t::bet_value()	{
	return m_bet_value;
}

void street_bet_t::set_box_ids(const std::uint8_t row)	{
	assert(row != 0 && row <= 12);
	switch (row)	{

	case 1:
		m_boxes.push_back(1);	m_boxes.push_back(2);	m_boxes.push_back(3);
		break;

	case 2:
		m_boxes.push_back(4);	m_boxes.push_back(5);	m_boxes.push_back(6);
		break;

	case 3:
		m_boxes.push_back(7);	m_boxes.push_back(8);	m_boxes.push_back(9);
		break;

	case 4:
		m_boxes.push_back(10);	m_boxes.push_back(11);	m_boxes.push_back(12);
		break;

	case 5:
		m_boxes.push_back(13);	m_boxes.push_back(14);	m_boxes.push_back(15);
		break;

	case 6:
		m_boxes.push_back(16);	m_boxes.push_back(17);	m_boxes.push_back(18);
		break;

	case 7:
		m_boxes.push_back(19);	m_boxes.push_back(20);	m_boxes.push_back(21);
		break;

	case 8:
		m_boxes.push_back(22);	m_boxes.push_back(23);	m_boxes.push_back(24);
		break;

	case 9:
		m_boxes.push_back(25);	m_boxes.push_back(26);	m_boxes.push_back(27);
		break;

	case 10:
		m_boxes.push_back(28);	m_boxes.push_back(29);	m_boxes.push_back(30);
		break;

	case 11:
		m_boxes.push_back(31);	m_boxes.push_back(32);	m_boxes.push_back(33);
		break;

	case 12:
		m_boxes.push_back(34);	m_boxes.push_back(35);	m_boxes.push_back(36);
		break;

	default:
		assert(0);
		break;
	}
}

line_bet_t::line_bet_t(const std::uint8_t bet_target, const std::int32_t bet_val)
	: m_outcome(UNDEFINED_RES),
	m_bet_value(bet_val)
{
	m_bet[0].set_bet_val(bet_val);
	m_bet[0].set_target_row(bet_target);
}

std::vector<uint8_t> line_bet_t::get_target_box_ids() const	{
	std::vector<uint8_t> boxes;
	auto a = m_bet[0].get_target_box_ids();
	boxes.insert(boxes.end(), a.begin(), a.end());
	a = m_bet[1].get_target_box_ids();
	boxes.insert(boxes.end(), a.begin(), a.end());
	return boxes;
}

std::int32_t line_bet_t::calc_payout(std::uint32_t outcome, colour_t colour)	{
	if (m_bet[0].calc_payout(outcome, colour) > 0)   {
		m_outcome = WIN;
		return (m_bet_value * 5);
	}
	else if (m_bet[1].calc_payout(outcome, colour) > 0)   {
		m_outcome = WIN;
		return (m_bet_value * 5);
	}
	else    {
		m_outcome = LOSS;
		return (-m_bet_value);
	}
}


bet_outcome_t line_bet_t::recent_bet_outcome()	{
	return m_outcome;
}

void line_bet_t::set_target_row(const std::uint8_t row)	{
	assert(row < 12);
	m_bet[0].set_target_row(row);
	m_bet[1].set_target_row(row + 1);
}

void line_bet_t::set_bet_val(const std::uint32_t bet_value)	{
	m_bet_value = bet_value;
	m_bet[0].set_bet_val(bet_value);
	m_bet[1].set_bet_val(bet_value);
}

std::uint32_t line_bet_t::bet_value()	{
	return m_bet_value;
}

range12_bet_t::range12_bet_t(const std::uint8_t range_num, const std::int32_t bet_val)
	: m_outcome(UNDEFINED_RES),
	m_bet_value(bet_val),
	m_selected_range(range_num - 1)
{
	assert(range_num > 0 && range_num < 4);
	m_ranges[0].first = 1; m_ranges[0].second = 12;
	m_ranges[1].first = 13; m_ranges[1].second = 24;
	m_ranges[2].first = 25; m_ranges[2].second = 36;
}

std::vector<uint8_t> range12_bet_t::get_target_box_ids() const	{
	std::vector<uint8_t> boxes;
	for (auto i = m_ranges[m_selected_range].first; i <= m_ranges[m_selected_range].second; ++i)	{
		boxes.push_back(i);
	}
	return boxes;
}

std::int32_t range12_bet_t::calc_payout(std::uint32_t outcome, colour_t colour)	{
	for (auto i = m_ranges[m_selected_range].first; i <= m_ranges[m_selected_range].second; ++i)	{
		if (outcome == i)	{
			m_outcome = WIN;
			return (m_bet_value * 2);
		}
	}
	m_outcome = LOSS;
	return (-m_bet_value);
}

bet_outcome_t range12_bet_t::recent_bet_outcome()	{
	return m_outcome;
}

void range12_bet_t::set_target_range(const std::uint8_t r)	{
	assert(r > 0 && r < 4);
	m_selected_range = r - 1;
}

void range12_bet_t::set_bet_val(const std::uint32_t bet_value)	{
	m_bet_value = bet_value;
}

std::uint32_t range12_bet_t::bet_value()	{
	return m_bet_value;
}

low_high_bet_t::low_high_bet_t(const std::uint8_t range_num, const std::int32_t bet_val)
	: m_outcome(UNDEFINED_RES),
	m_bet_value(bet_val),
	m_selected_range(range_num - 1)
{
	assert(range_num > 0 && range_num < 3);
	m_ranges[0].first = 1; m_ranges[0].second = 18;
	m_ranges[1].first = 19; m_ranges[1].second = 36;
}

std::vector<uint8_t> low_high_bet_t::get_target_box_ids() const	{
	std::vector<uint8_t> boxes;
	for (auto i = m_ranges[m_selected_range].first; i <= m_ranges[m_selected_range].second; ++i)	{
		boxes.push_back(i);
	}
	return boxes;
}

std::int32_t low_high_bet_t::calc_payout(std::uint32_t outcome, colour_t colour)	{
	for (auto i = m_ranges[m_selected_range].first; i <= m_ranges[m_selected_range].second; ++i)	{
		if (outcome == i)	{
			m_outcome = WIN;
			return (m_bet_value * 1);
		}
	}
	m_outcome = LOSS;
	return (-m_bet_value);
}

bet_outcome_t low_high_bet_t::recent_bet_outcome()	{
	return m_outcome;
}

void low_high_bet_t::set_target_range(const std::uint8_t r)	{
	assert(r < 3);
	m_selected_range = r;
}

void low_high_bet_t::set_bet_val(const std::uint32_t bet_value)	{
	m_bet_value = bet_value;
}

std::uint32_t low_high_bet_t::bet_value()	{
	return m_bet_value;
}

remainder_bet_t::remainder_bet_t(const std::uint8_t remainder, const std::int32_t bet_val)
	: m_outcome(UNDEFINED_RES),
	m_bet_value(bet_val),
	m_remainder(remainder)
{
	assert(remainder > 0 && remainder < 3);
}

std::vector<uint8_t> remainder_bet_t::get_target_box_ids() const	{
	std::vector<uint8_t> boxes;
	std::uint8_t num = 0;
	switch (m_remainder)	{
	case 0:
		num = 3;
		break;
	case 1:
		num = 1;
		break;
	case 2:
		num = 2;
		break;
	default:
		assert(0);
	}
	for (auto i = 1; i <= 12; ++i)	{
		boxes.push_back(num);
		num *= 3;
	}
	return boxes;
}

std::int32_t remainder_bet_t::calc_payout(std::uint32_t outcome, colour_t colour)	{
	if (outcome % 3 == m_remainder)	{
		m_outcome = WIN;
		return (m_bet_value * 2);
	}
	m_outcome = LOSS;
	return (-m_bet_value);
}

bet_outcome_t remainder_bet_t::recent_bet_outcome()	{
	return m_outcome;
}

void remainder_bet_t::set_remainder(const std::uint8_t r)	{
	assert(r < 3);
	m_remainder = r;
}

void remainder_bet_t::set_bet_val(const std::uint32_t bet_value)	{
	m_bet_value = bet_value;
}

std::uint32_t remainder_bet_t::bet_value()	{
	return m_bet_value;
}

red_black_bet_t::red_black_bet_t(const colour_t c, const std::int32_t bet_val)
	: m_outcome(UNDEFINED_RES),
	m_bet_value(bet_val),
	m_colour(c)
{
}

std::vector<uint8_t> red_black_bet_t::get_target_box_ids() const	{
	std::vector<uint8_t> boxes;
	//TODO: Find what boxes on table are red
	return boxes;
}

std::int32_t red_black_bet_t::calc_payout(std::uint32_t outcome, colour_t colour)	{
	if (colour == m_colour)	{
		m_outcome = WIN;
		return (m_bet_value * 1);
	}
	m_outcome = LOSS;
	return (-m_bet_value);
}

bet_outcome_t red_black_bet_t::recent_bet_outcome()	{
	return m_outcome;
}

void red_black_bet_t::set_colour(const colour_t c)	{
	m_colour = c;
}

void red_black_bet_t::set_bet_val(const std::uint32_t bet_value)	{
	m_bet_value = bet_value;
}

std::uint32_t red_black_bet_t::bet_value()	{
	return m_bet_value;
}

special_five_bet_t::special_five_bet_t(const std::uint8_t num, const std::int32_t bet_val)
	: m_outcome(UNDEFINED_RES),
	m_bet_value(bet_val),
	m_num(num)
{
}

std::vector<uint8_t> special_five_bet_t::get_target_box_ids() const	{
	std::vector<uint8_t> boxes;
	boxes.push_back(m_num);
	return boxes;
}

std::int32_t special_five_bet_t::calc_payout(std::uint32_t outcome, colour_t colour)	{
	if (outcome == m_num)	{
		m_outcome = WIN;
		return (m_bet_value * 6);
	}
	m_outcome = LOSS;
	return (-m_bet_value);
}

bet_outcome_t special_five_bet_t::recent_bet_outcome()	{
	return m_outcome;
}

void special_five_bet_t::set_num(const std::uint8_t num)	{
	m_num = num;
}

void special_five_bet_t::set_bet_val(const std::uint32_t bet_value)	{
	m_bet_value = bet_value;
}

std::uint32_t special_five_bet_t::bet_value()	{
	return m_bet_value;
}

even_odd_bet_t::even_odd_bet_t(const std::uint8_t remainder, const std::int32_t bet_val)
	: m_outcome(UNDEFINED_RES),
	m_bet_value(bet_val),
	m_rem(remainder)
{
	assert(m_rem == 0 || m_rem == 1);
}

std::vector<uint8_t> even_odd_bet_t::get_target_box_ids() const	{
	std::vector<uint8_t> boxes;
	for (auto i = 1; i < 36; ++i)	{
		if (i % 2 == m_rem)	{
			boxes.push_back(i);
		}
	}
	return boxes;
}

std::int32_t even_odd_bet_t::calc_payout(std::uint32_t outcome, colour_t colour)	{
	if (outcome % 2 == m_rem)	{
		m_outcome = WIN;
		return (m_bet_value * 1);
	}
	m_outcome = LOSS;
	return (-m_bet_value);
}

bet_outcome_t even_odd_bet_t::recent_bet_outcome()	{
	return m_outcome;
}

void even_odd_bet_t::set_remainder(const std::uint8_t r)	{
	m_rem = r;
	assert(m_rem == 0 || m_rem == 1);
}

void even_odd_bet_t::set_bet_val(const std::uint32_t bet_value)	{
	m_bet_value = bet_value;
}

std::uint32_t even_odd_bet_t::bet_value()	{
	return m_bet_value;
}


//bet_intf* bet_factory::make_bet(const bet_type_t b)	{
//
//	switch (b)	{
//
//	case STRAIGHT_BET:
//	{
//		auto bet = new straight_bet_t;
//		mh_bets.push_back(bet);
//		return bet;
//		break;
//	}
//
//	case STREET_BET:
//	{
//		auto bet = new street_bet_t;
//		mh_bets.push_back(bet);
//		return bet;
//		break;
//	}
//
//	case LINE_BET:
//	{
//		auto bet = new line_bet_t;
//		mh_bets.push_back(bet);
//		return bet;
//		break;
//	}
//
//	case RANGE12_BET:
//	{
//		auto bet = new range12_bet_t;
//		mh_bets.push_back(bet);
//		return bet;
//		break;
//	}
//
//	default:
//	{
//		assert(0);
//		return nullptr;
//	}
//	}	
//}

bet_factory::bet_factory()	{}

bet_factory::~bet_factory()	{
	for (auto& itr : mh_bets)	{
		delete itr;
	}
}

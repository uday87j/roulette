#ifndef BET_INTF_H_
#define BET_INTF_H_

#include <vector>
#include <string>
#include <cstdint>

#include "payout_intf.h"
#include "box_intf.h"
#include "colour.h"

// bet_intf.h
namespace rt	{

	enum bet_outcome_t	{
		LOSS	= 0,
		WIN,
		NO_RESULT,
		UNDEFINED_RES
	};

	class bet_intf	{
	public:

		virtual const std::string bet_name() const = 0;
		
		virtual const std::string bet_desc() const = 0;

		virtual const std::string odds() const = 0;

		virtual std::vector<std::uint8_t> get_target_box_ids() const = 0;	// Box numbers of RT

		virtual std::int32_t calc_payout(std::uint32_t outcome, colour_t colour) = 0;

		virtual bet_outcome_t recent_bet_outcome() = 0;

		virtual void set_bet_val(const std::uint32_t bet_value)	= 0;

		virtual std::uint32_t bet_value() = 0;

		virtual ~bet_intf()	{}
	};
}
#endif

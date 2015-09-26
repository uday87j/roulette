#ifndef TABLE_INTF_H_
#define TABLE_INTF_H_

#include <cstdint>
#include <vector>
#include <utility>

#include "box.h"

// table_intf.h
namespace rt	{

	class table_range_intf	{
	public:

		virtual ~table_range_intf()	{};
		
	};

	typedef std::pair < std::uint32_t, std::uint32_t > trange_t;	// Range of possibe numbers on table

	class table_intf	{
	public:

		virtual std::uint32_t num_rows() const = 0;
		
		virtual std::uint32_t num_cols() const = 0;

		virtual colour_t get_box_colour(const std::uint32_t box_id) const = 0;

		virtual std::vector<trange_t > get_ranges() const = 0;

		virtual ~table_intf()	{}

	};
}
#endif

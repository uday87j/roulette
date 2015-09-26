#ifndef TABLE_H_
#define TABLE_H_

#include <random>
#include "range/irange.hpp"

#include "table_intf.h"
#include "box.h"

// table.h
namespace rt	{

	enum table_range_enum {
		FIRST_12	= 0,
		SECOND_12,
		THIRD_12,
		LOW_1_18,
		HIGH_19_36,
		EVEN,
		ODD,
		RED,
		BLACK,
		INVALID_TABLE_RNGE
	};

	//class table_range : public table_range_intf	{
	//public:

	//	virtual void add_range(const std::uint32_t start, const std::uint32_t end)	{
	//		m_ranges.push_back(
	//			boost::integer_range<std::uint32_t>(start, end)
	//			);
	//	}

	//	virtual std::vector<boost::integer_range<std::uint32_t> >
	//		get_ranges()	{

	//		return m_ranges;
	//	}

	//	virtual ~table_range()	{}

	//private:
	//	
	//	// Index using table_range_enum
	//	// Acts as implicit map
	//	std::vector<boost::integer_range<std::uint32_t> > m_ranges;

	//};

	class table_range_t : public table_range_intf	{
		public:

			virtual void add_range(const std::uint32_t start, const std::uint32_t end)	{
				m_ranges.push_back(
					std::make_pair(start, end)
					);
			}

			virtual std::vector<trange_t>
				get_ranges() const	{

				return m_ranges;
			}

			virtual ~table_range_t()	{}

		private:
			
			// Index using table_range_enum
			// Acts as implicit map
			std::vector<trange_t> m_ranges;
	};


	enum table_box_id_t	{
		ZERO	= 0,
		// Don't use "ONE", use 1 & so on till 36
		ZERO_ZERO	= 37
	};

	template<typename BOX_T>
	class table_t	: public table_intf	{
	public:

		static const std::uint8_t NUM_BOXES = 38;

		table_t()
		: m_rows(13),
		m_cols(3)
		{
			std::default_random_engine generator;
			std::uniform_int_distribution<int> distribution(0,1);

			for (auto i : boost::irange(0, 37))	{
				m_boxes[i].change_id(i);
				m_boxes[i].change_colour(distribution(generator) ? RED_COLOUR : BLACK_COLOUR);  // generates number in the range 0..1
			}

			m_boxes[0].change_colour(GREEN_COLOUR);	// 0
			m_boxes[NUM_BOXES-1].change_colour(GREEN_COLOUR);	// 00

			m_tab_range.add_range(1, 12);
			m_tab_range.add_range(13, 24);
			m_tab_range.add_range(25, 36);
			m_tab_range.add_range(1, 18);
			m_tab_range.add_range(19, 36);
			m_tab_range.add_range(7, 12);
			m_tab_range.add_range(25, 30);
			m_tab_range.add_range(13, 18);
			m_tab_range.add_range(19, 24);
		}

		virtual std::uint32_t num_rows() const	{
			return m_rows;
		}

		virtual std::uint32_t num_cols() const	{
			return m_cols;
		}

		virtual colour_t get_box_colour(const std::uint32_t box_id) const	{
			return m_boxes[box_id].colour();
		}

		virtual void set_box_colour(const std::uint32_t box_id, const colour_t& c)	{
			m_boxes[box_id].change_colour(c);
		}

		virtual std::vector<trange_t> get_ranges() const	{
			return m_tab_range.get_ranges();
		}

		virtual ~table_t()	{}

	private:

		//coloured_box m_boxes[NUM_BOXES];
		BOX_T m_boxes[NUM_BOXES];
		std::uint32_t m_rows;
		std::uint32_t m_cols;

		table_range_t m_tab_range;
	};
}
#endif

#ifndef BOX_H_
#define BOX_H_

#include <initializer_list>

#include "box_intf.h"
#include "colour.h"

// box.h
namespace rt	{

	class box_t	: public box_intf	{
	public:

		box_t(std::uint32_t p_id = 0)
			: m_id(p_id)
		{}

		virtual std::uint32_t id() const	{
			return m_id;
		}

		virtual void change_id(const std::uint32_t id)	{
			m_id = id;
		}

		virtual ~box_t()	{}

	private:
		std::uint32_t m_id;
	};

	const colour_t BLACK_COLOUR;
	const colour_t WHITE_COLOUR(255, 255, 255);
	const colour_t RED_COLOUR(255, 0, 0);
	const colour_t GREEN_COLOUR(0, 255, 0);

	class coloured_box_t : public box_t	{
	public:
		coloured_box_t(colour_t p_colour = BLACK_COLOUR, const std::uint32_t id = 0)
			: box_t(id),
			m_colour(p_colour)
		{}

		virtual colour_t colour() const	{
			return m_colour;
		}

		virtual void change_colour(const colour_t& p_colour)	{
				m_colour	= p_colour;
		}

		virtual ~coloured_box_t()	{}

	private:
		colour_t m_colour;
	};

	class linked_colour_box_t : public coloured_box_t	{
	public:

		linked_colour_box_t(colour_t p_colour = BLACK_COLOUR, const std::uint32_t id = 0);

		linked_colour_box_t* up();
		linked_colour_box_t* down();	
		linked_colour_box_t* left();
		linked_colour_box_t* right();

		void up(linked_colour_box_t*);
		void down(linked_colour_box_t*);
		void left(linked_colour_box_t*);
		void right(linked_colour_box_t*);

	private:

		linked_colour_box_t* m_up;
		linked_colour_box_t* m_down;
		linked_colour_box_t* m_left;
		linked_colour_box_t* m_right;
	};
}
#endif

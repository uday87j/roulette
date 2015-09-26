#include "box.h"
#include "colour.h"

using namespace rt;

linked_colour_box_t::linked_colour_box_t(colour_t p_colour, const std::uint32_t id)
	: coloured_box_t(p_colour, id),
	m_up(nullptr),
	m_down(nullptr),
	m_left(nullptr),
	m_right(nullptr)
{}

linked_colour_box_t* linked_colour_box_t::up()	{ return m_up; }
linked_colour_box_t* linked_colour_box_t::down()	{ return m_down; }
linked_colour_box_t* linked_colour_box_t::left()	{ return m_left; }
linked_colour_box_t* linked_colour_box_t::right()	{ return m_right; }

void linked_colour_box_t::up(linked_colour_box_t* p)	{ m_up = p; }
void linked_colour_box_t::down(linked_colour_box_t* p)	{ m_down = p; }
void linked_colour_box_t::left(linked_colour_box_t* p)	{ m_left = p; }
void linked_colour_box_t::right(linked_colour_box_t* p)	{ m_right = p; }

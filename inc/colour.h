#ifndef COLOUR_H_
#define COLOUR_H_

// colour.h
namespace rt{

	struct colour_t	{
		
		colour_t()
			: colour_t(0, 0, 0)
		{}

		colour_t(std::uint8_t r, std::uint8_t g, std::uint8_t b)	{	
			rgb[0] = r;
			rgb[1] = g;
			rgb[2] = b;
		}

		colour_t(const colour_t& c)	{
			*this = c;
		}

		colour_t& operator = (const colour_t& c)	{
			for (auto i : { 0, 1, 2 })	{
				rgb[i] = c.rgb[i];
			}
			return *this;
		}

		bool operator == (const colour_t c)	{
			for (auto i : { 0, 1, 2 })	{
				if (rgb[i] == c.rgb[i])	{
					return false;
				}
			}
			return true;
		}

		char rgb[3]; 
	} ;
	
}
#endif

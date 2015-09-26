#ifndef WHEEL_H_
#define WHEEL_H_

#include "wheel_intf.h"

#include <ctime>
#include <random>

// wheel.h
namespace rt	{

	template<const std::uint32_t NUM_SLOTS = 38>
	class wheel_t	: public wheel_intf	{
	public:

		wheel_t()
			: distribution(0, NUM_SLOTS - 1)
		{
			generator.seed(static_cast<std::uint32_t>(std::time(nullptr)));
		}

		virtual void spin()	{}

		virtual void halt()	{}

		virtual void place_ball_into_bin(const std::uint32_t id)	{}

		// Return: 0...37
		// 37 SHOULD BE treated as '00'
		virtual std::uint32_t resulting_bin_id()	{
			return distribution(generator);
		}

		virtual ~wheel_t()	{}

	private:

		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution;

	};
}
#endif

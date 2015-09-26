#ifndef PAYOUT_H_
#define PAYOUT_H_

#include "payout_intf.h"

// payout.h
namespace rt	{

	class payout_t : public payout_intf	{
	public:
		
		payout_t(const std::int32_t val = 0)
			: m_val(val)
		{}

		payout_t(const payout_t& p)	{
			*this = p;
		}

		virtual std::int32_t value() const	{
			return m_val;
		}

		virtual void change_value(const std::int32_t val)	{
			m_val = val;
		}

		virtual ~payout_t()	{}

		payout_t& operator = (const payout_t& p)	{
			m_val = p.value();
			return *this;
		}

		payout_t& operator - (const payout_t& p)	{
			this->m_val -= p.m_val;
			return *this;
		}

		payout_t& operator + (const payout_t& p)	{
			this->m_val += p.m_val;
			return *this;
		}

		payout_t& operator -= (payout_t& p)	{
			*this = *this - p;
			return *this;
		}

		payout_t& operator += (payout_t& p)	{
			*this = *this + p;
			return *this;
		}

	private:

		std::int32_t m_val;

	};

	

	
}
#endif

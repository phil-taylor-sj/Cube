#pragma once

#include <vector>
#include <array>
#include <bitset>

namespace Utilities
{
	class Primes
	{
	public:	
		static const size_t MAX_INDEX = 27; // (9 * 9 * 9)
	
		static std::array<std::vector<size_t>, Primes::MAX_INDEX + 1> getPrimes(bool isPrime);
	
	private:
		static std::bitset<1000> m_sievePrimes();
	
		static size_t m_sumDigits(size_t number);
	};
}
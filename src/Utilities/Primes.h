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
	
		
		/**
		 * @brief Get all three-digit prime (or non-prime) numbers in a single sorted array.  
		 * @param isPrime Set to true to return prime numbers, otherwise set to false. 
		 * @return 1D arrays of all prime/non-prime numbers.
		 */
		static std::vector<unsigned int> getPrimes(bool isPrime);

		/**
		 * @brief Get all three-digit prime (or non-prime) numbers grouped by the sum of their digits.
		 * @param isPrime Set to true to return prime numbers, otherwise set to false. 
		 * @return 2D array of all prime/non-prime numbers, grouped at the index equivalent to the sum of their digits.
		 */
		static std::array<std::vector<unsigned int>, Primes::MAX_INDEX + 1> getPrimesGrouped(bool isPrime);
	
	private:
		/**
		 * @brief Identifies all prime numbers between 0 and 999.
		 * @return A bitset which marks all prime numbers as set.
		 */
		static std::bitset<1000> m_sievePrimes();
	
		/**
		 * @brief Sums the individual digits of a positive integer.
		 * @param A positive integer.
		 * @return The sum of the individual digits.
		 */
		static unsigned int m_sumDigits(unsigned int number);
	};
}
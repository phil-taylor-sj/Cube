#include "Primes.h"

namespace Utilities
{
	// Get all three-digit primes (or non-primes) in a single sorted vector.
	std::vector<unsigned int> Primes::getPrimes(bool isPrime)
	{
		std::bitset<1000> primeSieve = Primes::m_sievePrimes();
		std::vector<unsigned int> primes;

		for (size_t idx = 100; idx < primeSieve.size(); idx++)
		{
			if (primeSieve.test(idx) == isPrime) // Check if the index value matches the condition argument.
			{
				primes.push_back(idx);
			}
		}

		return std::move(primes);
	}

	// Get all three-digit primes (or non-primes) grouped by the sum of their digits.
	std::array<std::vector<unsigned int>, Primes::MAX_INDEX + 1> Primes::getPrimesGrouped(bool isPrime)
	{
		std::bitset<1000> primeSieve = Primes::m_sievePrimes();
		std::array<std::vector<unsigned int>, Primes::MAX_INDEX + 1> primes;

		for (size_t idx = 100; idx < primeSieve.size(); idx++)
		{
			if (primeSieve.test(idx) == isPrime) // Check if the index value matches the condition argument.
			{
				// Add to the sub-array located at the index which corresponds to the sum of the digits.
				primes[Primes::m_sumDigits(idx)].push_back(idx);
			}
		}

		return std::move(primes);
	}

	// Returns a bitset which marks indices as either prime (set/true) or non-prime (unset/false).
	std::bitset<1000> Primes::m_sievePrimes()
	{
		std::bitset<1000> sieve; // All values between 0 and 999.
		sieve.set();

		for (size_t ptr_1 = 2; ptr_1 < sieve.size(); ptr_1++)
		{
			size_t ptr_2 = ptr_1 * 2;
#			// Second pointer cycles through the remainer of array in increments of ptr_1.
			while(ptr_2 < sieve.size())
			{
				// Mark the value of ptr_2 as non-prime (false).
				sieve.reset(ptr_2);
				ptr_2 += ptr_1;
			}
		}

		return std::move(sieve);
	}

	// Returns the sum of the individual digits of a non-zero number.
	unsigned int Primes::m_sumDigits(unsigned int number)
	{
		unsigned int sum = 0;
		while (number != 0) {
			sum += number % 10;
			number /= 10;
		}
		return sum;
	}


}
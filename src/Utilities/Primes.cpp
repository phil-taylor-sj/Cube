#include "Primes.h"

namespace Utilities
{
	std::array<std::vector<size_t>, Primes::MAX_INDEX + 1> Primes::getPrimes(bool isPrime)
	{
		std::bitset<1000> primeSieve = Primes::m_sievePrimes();
		std::array<std::vector<size_t>, Primes::MAX_INDEX + 1> primes;
		
		for (size_t idx = 100; idx < primeSieve.size(); idx++)
		{
			if (primeSieve.test(idx) == isPrime)
			{
				primes[Primes::m_sumDigits(idx)].push_back(idx);
			}
		}

		return std::move(primes);
	}

	std::bitset<1000> Primes::m_sievePrimes()
	{
		std::bitset<1000> sieve;
		sieve.set();

		for (size_t ptr_1 = 2; ptr_1 < sieve.size(); ptr_1++)
		{
			size_t ptr_2 = ptr_1 * 2;
			while(ptr_2 < sieve.size())
			{
				sieve.reset(ptr_2);
				ptr_2 += ptr_1;
			}
		}

		return std::move(sieve);
	}

	size_t Primes::m_sumDigits(size_t number)
	{
		size_t sum = 0;
		while (number != 0) {
			sum += number % 10;
			number /= 10;
		}
		return sum;
	}


}
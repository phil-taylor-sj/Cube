#include "../pch.h"
#include "Utilities/Primes.h"

#include <vector>

namespace Primes_Tests
{
	class Primes_DigitsFixture : public testing::TestWithParam<std::tuple<unsigned int, std::vector<unsigned int>>>
	{
	protected:
		void SetUp() override
		{
			sum = std::get<0>(GetParam());
			expected = std::get<1>(GetParam());
		}
		size_t sum;
		std::vector<unsigned int> expected;

		void TearDown() override {}
	};

	class Primes_AllPrimesF : public Primes_DigitsFixture {};
	TEST_P(Primes_AllPrimesF, Primes_AllPrimes)
	{
		std::array<std::vector<unsigned int>, 28> output = Utilities::Primes::getPrimesGrouped(true);
		ASSERT_LT(sum, output.size());
		ASSERT_EQ(expected.size(), output[sum].size());
		ASSERT_EQ(expected, output[sum]);
	}

	INSTANTIATE_TEST_SUITE_P(Primes_AllPrimes, Primes_AllPrimesF, testing::Values(
		std::make_tuple(2, std::vector<unsigned int>{101}),
		std::make_tuple(4, std::vector<unsigned int>{103, 211}),
		std::make_tuple(5, std::vector<unsigned int>{113, 131, 311, 401}),
		std::make_tuple(7, std::vector<unsigned int>{151, 223, 241, 313, 331, 421, 601}),
		std::make_tuple(8, std::vector<unsigned int>{107, 233, 251, 431, 503, 521, 701}),
		std::make_tuple(10, std::vector<unsigned int>{109, 127, 163, 181, 271, 307, 433, 523, 541, 613, 631, 811}),
		std::make_tuple(11, std::vector<unsigned int>{137, 173, 191, 227, 263, 281, 317, 353, 443, 461, 641, 821, 911}),
		std::make_tuple(13, std::vector<unsigned int>{139, 157, 193, 229, 283, 337, 373, 409, 463, 571, 607, 643, 661, 733, 751, 823}),
		std::make_tuple(14, std::vector<unsigned int>{149, 167, 239, 257, 293, 347, 383, 419, 491, 509, 563, 617, 653, 743, 761, 941}),
		std::make_tuple(16, std::vector<unsigned int>{277, 349, 367, 439, 457, 547, 619, 673, 691, 709, 727, 853, 907}),
		std::make_tuple(17, std::vector<unsigned int>{179, 197, 269, 359, 449, 467, 557, 593, 647, 683, 719, 773, 809, 827, 863, 881, 953, 971}),
		std::make_tuple(19, std::vector<unsigned int>{199, 379, 397, 487, 577, 739, 757, 829, 883, 919, 937, 991}),
		std::make_tuple(20, std::vector<unsigned int>{389, 479, 569, 587, 659, 677, 839, 857, 929, 947, 983}),
		std::make_tuple(22, std::vector<unsigned int>{499, 769, 787, 859, 877, 967}),
		std::make_tuple(23, std::vector<unsigned int>{599, 797, 887, 977}),
		std::make_tuple(25, std::vector<unsigned int>{997})
	));

	class Primes_AllNonPrimesF : public Primes_DigitsFixture {};
	TEST_P(Primes_AllNonPrimesF, Primes_AllNonPrimes)
	{
		std::array<std::vector<unsigned int>, 28> output = Utilities::Primes::getPrimesGrouped(false);
		ASSERT_LT(sum, output.size());
		ASSERT_EQ(expected.size(), output[sum].size());
		ASSERT_EQ(expected, output[sum]);
	}

	INSTANTIATE_TEST_SUITE_P(Primes_AllNonPrimes, Primes_AllNonPrimesF, testing::Values(
		std::make_tuple(1, std::vector<unsigned int>{100}),
		std::make_tuple(2, std::vector<unsigned int>{110, 200}),
		std::make_tuple(3, std::vector<unsigned int>{102, 111, 120, 201, 210, 300}),
		std::make_tuple(4, std::vector<unsigned int>{112, 121, 130, 202, 220, 301, 310, 400}),
		std::make_tuple(5, std::vector<unsigned int>{104, 122, 140, 203, 212, 221, 230, 302, 320, 410, 500}),
		std::make_tuple(6, std::vector<unsigned int>{105, 114, 123, 132, 141, 150, 204, 213, 222, 231, 240, 303, 312, 321, 330, 402, 411, 420, 501, 510, 600}),
		std::make_tuple(7, std::vector<unsigned int>{106, 115, 124, 133, 142, 160, 205, 214, 232, 250, 304, 322, 340, 403, 412, 430, 502, 511, 520, 610, 700}),
		std::make_tuple(8, std::vector<unsigned int>{116, 125, 134, 143, 152, 161, 170, 206, 215, 224, 242, 260, 305, 314, 323, 332, 341, 350, 404, 413, 422, 440, 512, 530, 602, 611, 620, 710, 800}),
		std::make_tuple(9, std::vector<unsigned int>{108, 117, 126, 135, 144, 153, 162, 171, 180, 207, 216, 225, 234, 243, 252, 261, 270, 306, 315, 324, 333, 342, 351, 360, 405, 414, 423, 432, 441, 450, 504, 513, 522, 531, 540, 603, 612, 621, 630, 702, 711, 720, 801, 810, 900}),
		std::make_tuple(10, std::vector<unsigned int>{118, 136, 145, 154, 172, 190, 208, 217, 226, 235, 244, 253, 262, 280, 316, 325, 334, 343, 352, 361, 370, 406, 415, 424, 442, 451, 460, 505, 514, 532, 550, 604, 622, 640, 703, 712, 721, 730, 802, 820, 901, 910}),
		std::make_tuple(11, std::vector<unsigned int>{119, 128, 146, 155, 164, 182, 209, 218, 236, 245, 254, 272, 290, 308, 326, 335, 344, 362, 371, 380, 407, 416, 425, 434, 452, 470, 506, 515, 524, 533, 542, 551, 560, 605, 614, 623, 632, 650, 704, 713, 722, 731, 740, 803, 812, 830, 902, 920}),
		std::make_tuple(26, std::vector<unsigned int>{899, 989, 998}),
		std::make_tuple(27, std::vector<unsigned int>{999})
	));


	TEST(Primes_getPrimes, returns_a_list_contianing_all_three_digit_prime_numbers_if_true)
	{
		std::vector<unsigned int> output = Utilities::Primes::getPrimes(true);

		std::vector<unsigned int> expected = {
			101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 
			211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 
			307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 
			401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499,
			503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 
			601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691,
			701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 
			809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 
			907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997
		};

		ASSERT_EQ(expected.size(), output.size());
		ASSERT_EQ(expected, output);
	
	}

}
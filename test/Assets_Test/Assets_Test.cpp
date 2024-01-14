#include "../pch.h"
#include "Assets/TextureDict.h"

namespace TextureDict_Tests
{
	TEST(TextureDict_getTexture_Test, Returns_an_error_when_passed_a_nonexistent_key)
	{
		ASSERT_THROW(
			TextureDict::getInstance()->getTexture("FakeRoom"),
			std::invalid_argument
			);
	}
}
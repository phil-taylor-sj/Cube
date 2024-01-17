#include "../pch.h"
#include "Levels/LevelEntityManager.h"
#include "Actors/ActorComponents.h"
#include "Physics/Physics.h"

namespace LevelEntityManager_Tests
{
	TEST(Level_getCollision_test,
		Should_return_non_empty_vector_for_actor_overlapping_walls)
	{
		Levels::LevelEntityManager level = Levels::LevelEntityManager(5, 5);
		level.setCommonCellWidth(1000.f);
		level.updateAllCellScaling();
		
		Actors::ActorCollisionComponent actorOne;
		actorOne.broadCircle.setPosition(1000.f, 1000.f);
		actorOne.broadCircle.setRadius(50.f);
		std::vector<Physics::RectParams>collisionsOne = 
			level.getCircleCollisions(actorOne);

		EXPECT_EQ(collisionsOne.size(), 8);
	}
}
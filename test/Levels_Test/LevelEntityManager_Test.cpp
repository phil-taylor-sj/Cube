#include "../pch.h"
#include "Levels/LevelEntityManager.h"
#include "Actors/ActorComponents.h"
#include "Physics/Physics.h"



namespace LevelEntityManager_Tests
{
	/**
	class SmallGridFixture: public ::testing::Test 
	{
	protected:
		Levels::LevelEntityManager level;
		Actors::ActorCollisionComponent actorOne;
		void SetUp() override {
			level = Levels::LevelEntityManager(5, 5);
			level.setCommonCellWidth(1000.f);
			level.updateAllCellScaling();
			actorOne.broadCircle.setRadius(50.f);
			actorOne.broadCircle.setPosition(1000.f, 1000.f);
		}
		void TearDown() override {}
	};

	class DefaultGridFixture : public ::testing::Test
	{
	protected:
		Levels::LevelEntityManager level;
		Actors::ActorCollisionComponent actorOne;
		void SetUp() override {
			level = Levels::LevelEntityManager(5, 5);
			actorOne.broadCircle.setRadius(50.f);
			actorOne.broadCircle.setPosition(0.f, 0.f);
		}
		void TearDown() override {}
	};

	TEST_F(DefaultGridFixture,
		setCommonCellWidth_should_set_new_cell_width_and_scale_cells
		)
	{
		level.setCommonCellWidth(2000.f);

		Levels::DetectedLevelCollisions collisionsOne =
			level.getCircleCollisions(actorOne);
		EXPECT_EQ(collisionsOne.staticWalls.size(), 0);
	
		actorOne.broadCircle.translate(vecp::Vec2f(1000.f, 1000.f));
		Levels::DetectedLevelCollisions collisionsTwo =
			level.getCircleCollisions(actorOne);
		EXPECT_EQ(collisionsTwo.staticWalls.size(), 8);
	}

	TEST_F(SmallGridFixture,
		getCircleCollisions_should_return_non_empty_wall_vector_for_actor_overlapping_walls)
	{
		Levels::DetectedLevelCollisions collisionsOne = 
			level.getCircleCollisions(actorOne);
		EXPECT_EQ(collisionsOne.staticWalls.size(), 8);	
		
		actorOne.broadCircle.translate(vecp::Vec2f(250.f, 0.f));
		Levels::DetectedLevelCollisions collisionsTwo =
			level.getCircleCollisions(actorOne);
		EXPECT_EQ(collisionsTwo.staticWalls.size(), 2);
	}

	TEST_F(SmallGridFixture,
		getCircleCollisions_should_return_empty_wall_vector_for_actor_not_overlapping_walls)
	{
		Levels::DetectedLevelCollisions collisionsOne =
			level.getCircleCollisions(actorOne);
		actorOne.broadCircle.setPosition(500.f, 500.f);
		EXPECT_EQ(collisionsOne.staticWalls.size(), 0);
	}
	*/
}
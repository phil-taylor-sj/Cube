#pragma once
#include "Physics/Vec2.h"
#include "Physics/Rectangle.h"

namespace Levels
{
	class CellStaticWall
	{
	public:
		void setRelativePosition(float relativeX, float relativeY);
		void setRelativePosition(Physics::Vec2f relativePosition);
		void setRelativeDimensions(float relativeWidth, float relativeHeight);

		void setAngle(float angle);
		void setCellWidth(float width);
		void setCellPosition(float xPosition, float yPosition);
		void setCellPosition(Physics::Vec2f position);

		Physics::RectParams getRectangle();

		CellStaticWall();
		~CellStaticWall();

	protected:
		void m_updateRectangle();

		/* The following variables will change frequntly once cube shuffling
		is implemented into the gameplay (i.e. moving cells). */
		Physics::Rectangle m_rectangle;
		Physics::Vec2f m_cellPosition;
		
		// The following varaibles will change infrequetly during runtime.
		float m_cellWidth;

		// The following variables will rarely change during runtime.
		Physics::Vec2f m_relativePosition;
		float m_relativeWidth;
		float m_relativeHeight;
		float m_angle;
	};
}
#pragma once
#include <math.h>
#include "Physics/Vec2.h"

#include <VecPlus/Vec2.h>

namespace Physics
{
	/**
	 * @struct CircleParams
	 * @brief Parameters for a circular object.
	 */
	struct CircleParams {
		vecp::Vec2f position;
		vecp::Vec2f previousPosition;
		float radius;
		float radiusSquared;
	};

	class Circle
	{
	public:
		/**
		 * @brief Set the x-y coordinates of the circle centre.
		 * @param position Vector of new x-y coordinates.
		 */
		void setPosition(vecp::Vec2f position);

		/**
		 * @brief Set the x-y coordinates of the circle centre.
	     * @param xPosition The new x-coordinate.
		 * @param yPosition The new y-coordinate.
		 */
		void setPosition(float xPosition, float yPosition);
		 
		/**
		 * @brief Translate the x-y corrdinates of the circle centre.
		 * @param deltaPosition Distance by which to shift the centre along each axis.
		 */
		void translate(vecp::Vec2f deltaPosition);
		
		/**
		 * @brief Translate the x-y corrdinates of the circle centre.
		 * @param xDelta Distance by which to shift the centre along the x axis.
		 * @param yDelta Distance by which to shift the centre along the y axis.
		 */
		void translate(float xDelta, float yDelta);

		/**
		 * @brief Set the radius of the circle.
		 * @param 
		 */
		void setRadius(float radius);
		void scaleRadius(float scale);
		void scalePosition(float scale);

		struct CircleParams getCircle() const;

		Circle();
		Circle(vecp::Vec2f position, float radius);
		Circle(float xPosition, float yPosition, float radius);
		~Circle();

	private:
		CircleParams m_params;
	};
}
#pragma once
#include "Physics/Vec2.h"

namespace Physics
{
    /**
     * @struct RectParams
     * @brief A structure representing parameters of a rectangular shape.
     */
	struct RectParams {
		Vec2f position;
		Vec2f previousPosition;
		float width;
		float height;
		float halfWidth;
		float halfHeight;
		float angle;
	};

	/**
	 * @class Rectangle
	 * @brief A class representing a 2D rectangular shape.
	 */
	class Rectangle
	{
	public:
		/**
         * @brief Set the position of the Rectangle using a Vec2f.
         * @param position The new position of the Rectangle.
         */
		void setPosition(Vec2f position);

		/**
		 * @brief Set the position of the Rectangle using individual x and y coordinates.
		 * @param xPosition The x-coordinate of the new position.
		 * @param yPosition The y-coordinate of the new position.
		 */
		void setPosition(float xPosition, float yPosition);

        /**
         * @brief Translate the Rectangle by a specified delta position using a Vec2f.
         * @param deltaPosition The delta position to translate by.
         */
        void translate(Vec2f deltaPosition);

        /**
         * @brief Translate the Rectangle by specified delta x and y values.
         * @param xDelta The delta value to add to the x-coordinate.
         * @param yDelta The delta value to add to the y-coordinate.
         */
        void translate(float xDelta, float yDelta);

        /**
         * @brief Set the width of the Rectangle.
         * @param width The new width of the Rectangle.
         * This also updates the half-width parameter.
         */
        void setWidth(float width);

        /**
         * @brief Set the height of the Rectangle.
         * @param height The new height of the Rectangle.
         * This also updates the half-height parameter.
         */
        void setHeight(float height);

        /**
         * @brief Set the angle (rotation) of the Rectangle.
         * @param angle The new angle of the Rectangle in degrees.
         */
        void setAngle(float angle);

        /**
         * @brief Scale the width and height of the Rectangle by a specified scale factor.
         * @param scale The scale factor to apply to the width and height.
         * This also updates the half-width and half-height parameters.
         */
        void scaleWidthHeight(float scale);

        /**
         * @brief Scale the position of the Rectangle by a specified scale factor.
         * @param scale The scale factor to apply to the position.
         */
        void scalePosition(float scale);

        /**
         * @brief Get the parameters of the Rectangle.
         * @return The parameters of the Rectangle as a RectParams structure.
         */
        RectParams getRectangle() const;

		/**
		 * @brief Default constructor to create a Rectangle with default parameters.
		 * The default position is (0,0), width and height are set to 1, and the angle is 0.
		 */
		Rectangle();

		/**
		 * @brief Constructor to create a Rectangle with a specified position.
		 * @param position The position of the Rectangle.
		 * The width and height are set to 1, and the angle is 0.
		 */
		Rectangle(Vec2f position);
		/**
         * @brief Constructor to create a Rectangle with specified x and y positions.
         * @param xPosition The x-coordinate of the Rectangle's position.
         * @param yPosition The y-coordinate of the Rectangle's position.
         * The width and height are set to 1, and the angle is 0.
         */
		Rectangle(float xPosition, float yPosition);
		
		/**
         * @brief Constructor to create a Rectangle with a specified position, width, and height.
         * @param position The position of the Rectangle.
         * @param width The width of the Rectangle.
         * @param height The height of the Rectangle.
         * The angle is set to 0.
         */
		Rectangle(Vec2f position, float width, float height);
		
		/**
         * @brief Constructor to create a Rectangle with specified x and y positions, width, and height.
         * @param xPosition The x-coordinate of the Rectangle's position.
         * @param yPosition The y-coordinate of the Rectangle's position.
         * @param width The width of the Rectangle.
         * @param height The height of the Rectangle.
         * The angle is set to 0.
         */
		Rectangle(
			float xPosition, float yPosition, 
			float width, float height
		);

		/**
		 * @brief Destructor for the Rectangle class.
		 */
		~Rectangle();

	private:
		RectParams m_params; ///< The parameters of the Rectangle.
	};
}
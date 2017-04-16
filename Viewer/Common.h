#ifndef COMMON_H
#define COMMON_H

/*!
 * \file
 * \brief Contains some useful functions and commonFont
 */

#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

//! Returns length of a vector (x, y)
inline double length(const double &x, const double &y);

//! Returns length^2 of a vector (x, y)
inline double lengthSquare(const double &x, const double &y);

//! Returns euclidean distance between vectors (x1, y1) and (x2, y2)
inline double dist(const double &x1, const double &y1, const double &x2, const double &y2);

//! Returns square of euclidean distance between vectors (x1, y1) and (x2, y2)
inline double distSquare(const double &x1, const double &y1, const double &x2, const double &y2);

/*!
 * \brief A factory function for creating circles
 * \param radius the radius of the circle
 * \param x the x-coordinate of the circle's center
 * \param y the y-coordinate of the circle's center
 * \param fillColor the color of the circle
 * \return an sf::CircleShape with center at (x, y)
 */
sf::CircleShape makeCircle(float radius, float x, float y, sf::Color fillColor);

/*!
 * \brief A factory function for creating rectangles
 * \param width the width of the rect
 * \param height the height of the rect
 * \param x the x-coordinate of the rect's center
 * \param y the y-coordinate of the rect's center
 * \param fillColor the color of the rect
 * \return an sf::RectangleShape with center at (x, y)
 */
sf::RectangleShape makeRectangle(float width, float height, float x, float y, sf::Color fillColor);

/*!
 * \brief A factory function for creating lines
 * \param x1 the x-coordinate of first end of line
 * \param y1 the y-coordinate of first end of line
 * \param x2 the x-coordinate of second end of line
 * \param y2 the y-coordinate of second end of line
 * \param thickness the thickness of the line
 * \param fillColor the color of the line
 * \return an sf::RectangleShape which is a line segment with specified thickness between (x1, y1) and (x2, y2)
 */
sf::RectangleShape makeLine(float x1, float y1, float x2, float y2, float thickness, sf::Color fillColor);

/*!
 * \brief A factory function for creating texts
 * \param caption the text to be displayed
 * \param fontSize the size of characters
 * \param x the x-coordinate of the center of text
 * \param y the y-coordinate of the center of text
 * \param color the color of text
 * \return an sf::Text with center at (x, y)
 */
sf::Text makeText(string caption, int fontSize, float x, float y, sf::Color color);

//! You should use only this font in your program. It loads font from FONT_PATH defined in Config.h
extern sf::Font commonFont;

#endif // COMMON_H


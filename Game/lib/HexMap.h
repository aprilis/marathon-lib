#ifndef HEXMAP_H
#define HEXMAP_H

/*!
 * \file
 * \brief Contains the HexMap class
 */

#include <vector>
#include <SFML/Graphics.hpp>
#include "GameState.h"
using namespace std;


//! Useful class for using hex maps
class HexMap
{
    vector<vector<sf::CircleShape>> hexes;

    float radius = 1.f;

    const float h_factor = 0.9, v_factor = 0.8;

public:
    //! The default constructor
    HexMap() = default;

    /*!
     * \brief Simply calls init(rows, colums, size)
     * \param rows the number of rows
     * \param columns the number of columns
     * \param size the size of one hex (2 * radius)
     */
    HexMap(int rows, int columns, float size = 30.f) { init(rows, columns, size); }

    /*!
     * \brief Initializes the map. Initially, all hexes are white.
     * \param rows the number of rows
     * \param columns the number of columns
     * \param size the size of one hex (2 * radius)
     */
    void init(int rows, int columns, float size = 30.f);

    //! Returns the number of rows
    int rowCount() const { return hexes.size(); }

    //! Returns the number of columns
    int colCount() const { return hexes.empty() ? 0 : hexes[0].size(); }

    /*!
     * \brief Sets the color of a selected hex
     * \param row the row of a hex
     * \param column the column of a hex
     * \param color the new color
     */
    void setColor(int row, int column, sf::Color color);

    /*!
     * \brief Gets the color of a selected hex
     * \param row the row of a hex
     * \param column the column of a hex
     * \return The color of the hex
     */
    sf::Color getColor(int row, int column) const;

    /*!
     * \brief Returns position of the center of a selected hex
     * \param row the row of a hex
     * \param column the column of a hex
     * \return The position of the center of the specified hex
     */
    sf::Vector2f getPosition(int row, int column) const;

    /*!
     * \brief Returns pair of (row, column) coords of the hex which contains the position
     * \param position the position where hex is looked for
     * \return The row and column of the hex or (-1, -1) if position is outside the map
     */
    pair<int, int> getHex(sf::Vector2f position) const;

    /*!
     * \brief adds all drawables to the gameState
     * \param gameState the game state
     */
    void draw(GameState &gameState) const;

    /*!
     * \brief draws the map directly to the window
     * \param window the render window
     */
    void draw(sf::RenderWindow &window) const;

    /*!
     * \brief Returns position of each neighbour of the hex on (row, column)
     * \param row the row of the hex
     * \param column the column of the hex
     * \return A vector of hex' neighbours' positions
     */
    vector<pair<int, int>> getNeighbours(int row, int column) const;
};

#endif // HEXMAP_H


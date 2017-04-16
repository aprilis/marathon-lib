#ifndef INFO_H
#define INFO_H


/*!
 * \file
 * \brief Contains the Info class
 */

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

//! Usable class for printing real-time info
class Info
{
    vector<pair<string, function<string()>>> items;

public:
    /*!
     * \brief Adds function returning string to the info
     * \param label the label
     * \param function the function that should take 0 arguments and return a string
     */
    void addFunction(string label, function<string()> function)
    {
        items.emplace_back(label, function);
    }

    /*!
     * \brief Adds a reference to the variable
     * \param label the label
     * \param variable a reference to the variable.
     *  It must be possible to call to_string(variable). The variable should exist until the end of the game.
     */
    template<class T> void addItem(string label, T &variable)
    {
        addFunction(label, [&]() { return to_string(variable); });
    }

    /*!
     * \brief Removes all infos with specified label
     * \param label the label
     */
    void removeItem(string label);

    /*!
     * \brief Checks if there exists any info with specified label
     * \param label the label
     * \return
     */
    bool hasItem(string label);

    /*!
     * \brief Removes all items
     */
    void clear();

    /*!
     * \brief Draws info to the window
     * \param window the render window
     */
    void draw(sf::RenderWindow &window);

    /*!
     * \brief Saves info for later replays
     * \param o the stream to save to
     */
    void log(ostream &o);
};

template<> void Info::addItem<string>(string label, string &variable);

#endif // INFO_H

#ifndef LOG_H
#define LOG_H


/*!
 * \file
 * \brief Contains the MultiStream class
 */

#include <vector>
#include <iostream>
using namespace std;

//! Class used to combining multiple streams into one
class MultiStream
{
    vector<ostream*> out;

public:
    //! Default constructor
    MultiStream() = default;

    /*!
     * \brief Initialization of multistream with a list of streams
     * \param a list of ofstream pointers
     */
    MultiStream(initializer_list<ostream*> list) : out(list) { }

    /*!
     * \brief Adds a stream
     * \param the stream to add
     */
    void addStream(ostream &str) { out.push_back(&str); }

    /*!
     * \brief Removes all streams
     */
    void clear() { out.clear(); }

    /*!
     * \brief writes obj into all streams (unfortunately, manipulators like endl don't work)
     * \obj the object to write
     */
    template<class T> MultiStream& operator<<(const T& obj)
    {
        for(auto o: out)
            (*o) << obj;
        return *this;
    }

    /*!
     * \brief Flushes all streams
     */
    void flush()
    {
        for(auto o: out)
            (*o) << std::flush;
    }
};

//! MultiStream which initially contains only cout
extern MultiStream mout;

//! MultiStream which initially contains only cerr
extern MultiStream merr;

/*!
 * \brief Reopens the stream into a new file in a specified directory. If the directory doesn't exist it is created.
 * The name of the file is HH_MM_SS.log where HH, MM, SS is current hour, minute and second.
 * \param of the stream to reopen
 * \param dir the name of the directory
 */
void open_log(ofstream &of, string dir);

#endif // LOG_H

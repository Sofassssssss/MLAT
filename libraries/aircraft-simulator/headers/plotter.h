#ifndef MLAT_PLOTTER_H
#define MLAT_PLOTTER_H

#include <fstream>
#include <string>

/*! \class Plotter
*   \brief Converts data to file.
* It translates the data needed to build a graph into some file.
* Then the script that launches the chart is manually launched.
*/
class Plotter
{
public:
	inline Plotter(const std::string& filepath) : _file(new std::ofstream(filepath)) {}
	inline ~Plotter() { if (_file) { delete _file; } }
    //! Insert point to the file
	void addPoint(float x, float y, float z);
private:
    //! Result file with points
	std::ofstream* _file;
};
#endif
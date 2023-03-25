#ifndef MLAT_PROCESSOR_H
#define MLAT_PROCESSOR_H

#include <chrono>
#include <vector>
#include <vector.h>
#include <map>
#include <set>
#include <tower.h>
#include <equation_solver.h>

class Processor
{
public:
    Processor() = default;

    //! Adding TOA for one iteration
    void addTOA(uint16_t id, const std::stack<float>& TOA);
    //! Overloading operator[]
    std::stack<float>& operator[](uint16_t id) { return _towers_toa[id]; }

    Tower getTower(uint16_t id) { return _towers[id]; }
    void setTower(uint16_t id, const Tower& tower) 
    { 
        _towers[id] = tower; 
        _towers_coordinates[id] = tower.getPosition();
        _solver.setTowersCoordinates(_towers_coordinates);
    }
    /*! Processing accepted data
    * Calculating TDOA and getting aircraft position
    * using overdeterminated system of nonlinear equation
    * which solves using least squares method and
    * Gauss-Newton algorithm
    */
    void process();

    //! Getter for _TDOA;
    //[[nodiscard]] std::vector<OurVector<6>> getTDOA() const { return _TDOA; }
private:
    std::map<uint16_t, std::stack<float>> _towers_toa;
    std::map<uint16_t, Tower> _towers;
    std::map<uint16_t, OurVector<3>> _towers_coordinates;
    EquationSolver _solver;
    //std::vector<OurVector<6>> _TDOA;
};

#endif


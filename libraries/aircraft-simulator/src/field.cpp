#include <field.h>
#include <aircraft.h>
#include <chrono>
#include <thread>

Field::Field() : _coordinates(new OurVector<3>[1000]),
_times(new float[1000]), _towers(new Tower[7])
{
    _current_position[2] = 10;
}

Field::~Field()
{
    delete[] _coordinates;
    delete[] _times;
    delete[] _towers;
}

void Field::startMovement()
{
    setTowers();
    setAircraftTowers();
    _aircraft.checkAcceleration();
    for(int i=0;;++i)
    {
        _current_position = _current_position + _aircraft.getSpeed() * (60.f / kilometer);
        checkHeight();
        _aircraft.calculateNewSpeed();
        _aircraft.checkSpeed();

        _times[i] = 60.f * i;
        _coordinates[i] = _current_position;
        for (uint16_t j = 0; j < number; ++j)
        {
            std::set<float> set = _processor[_towers[j].getID()];
            set.insert(_aircraft.sendSignal(_towers[j], _current_position));
            _processor.addTOA(_towers[j].getID(), set);
        }
        // it doesn't realize :)
        //_processor.calculateTDOA();
        if (_plt)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            _plt->addPoint(_current_position[0], _current_position[1], _current_position[2]);
        }
    }
}

void Field::checkHeight()
{
    if (_current_position[2] > 11.5f && _aircraft.getSpeed()[2] > 0.f)
    {
        OurVector<3> new_speed = _aircraft.getSpeed();
        new_speed[2] /= 16;

        OurVector<3> new_acceleration = _aircraft.getAcceleration();
        new_acceleration[2] = new_acceleration[2] < 0.f ? new_acceleration[2] : -new_acceleration[2];

        _aircraft.setSpeed(new_speed);
        _aircraft.setAcceleration(new_acceleration);
    }
    if (_aircraft.getSpeed()[2] < -1.f)
    {
        OurVector<3> new_speed = _aircraft.getSpeed();
        new_speed[2] = 0;

        OurVector<3> new_acceleration = _aircraft.getAcceleration();
        new_acceleration[2] = 0;

        _aircraft.setSpeed(new_speed);
        _aircraft.setAcceleration(new_acceleration);
    }
}

void Field::setTowers()
{
    OurVector<3> tower_position;
    tower_position[0] = -1500;
    tower_position[1] = 400;
    tower_position[2] = 50;

    _towers[0].setID(0);
    _towers[0].setPosition(tower_position);

    tower_position[0] = 2000;
    tower_position[1] = 3000;
    tower_position[2] = 1000;

    _towers[1].setID(1);
    _towers[1].setPosition(tower_position);

    tower_position[0] = 5000;
    tower_position[1] = 12000;
    tower_position[2] = 100;

    _towers[2].setID(2);
    _towers[2].setPosition(tower_position);

    tower_position[0] = 11000;
    tower_position[1] = -4000;
    tower_position[2] = 250;

    _towers[3].setID(3);
    _towers[3].setPosition(tower_position);
}

void Field::setAircraftTowers()
{
    for (uint16_t i = 0; i < number; ++i)
    {
        _aircraft.setNewTower(_towers[i]);
    }
}

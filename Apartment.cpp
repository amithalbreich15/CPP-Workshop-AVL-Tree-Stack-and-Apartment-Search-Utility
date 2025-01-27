#include "Apartment.h"
#include <iostream>
#include <cmath>

using std::sqrt; using std::endl;

/**
   * Constructor that get pair of points, and creates new apartment.
   * @param Coordinates std::pair, which the first is the x coordinate
   * and the second is the y.
   */
Apartment::Apartment(const std::pair<double, double> &Coordinates) :
        _x(Coordinates.first), _y(Coordinates.second) {}

/**
*
* @return the x coordinate of the apartment
*/
double Apartment::get_x() const
{
    return _x;
}

/**
   *
   * @return the y coordinate of the apartment
   */
double Apartment::get_y() const
{
    return _y;
}

/**
   * Operator <, apartment is smaller than other if it closer to
   * [31.772425, 35.213506]
   * @param other
   * @return true, if this apartment is smaller than the other one,
   * false otherwise
   */
bool Apartment::operator<(const Apartment &other) const
{
    double x_dist = sqrt((_x - other._x)*(_x - other._x));
    double y_dist = sqrt((_y - other._y) * (_y - other._y));
    if (x_dist <= EPSILON && y_dist <= EPSILON)
    {
        return false;
    }
    double this_dist = sqrt(pow((_x - X_FEEL_BOX), 2) +
                            pow((_y - Y_FEEL_BOX), 2));
    double other_dist = sqrt(pow((other._x - X_FEEL_BOX), 2)
                             + pow((other._y - Y_FEEL_BOX), 2));
    return this_dist < other_dist;
}

/**
   * Operator >, apartment is greater than other if it farther from
   * [31.772425, 35.213506]
   * @param other
   * @return true, if this apartment is greater than the other one
   * , false otherwise
   */
bool Apartment::operator>(const Apartment &other) const
{
    double x_dist = sqrt((_x - other._x)*(_x - other._x));
    double y_dist = sqrt((_y - other._y) * (_y - other._y));
    if (x_dist <= EPSILON && y_dist <= EPSILON)
    {
        return false;
    }
    double this_dist = sqrt(pow((_x - X_FEEL_BOX), 2) +
                            pow((_y - Y_FEEL_BOX), 2));
    double other_dist = sqrt(pow((other._x - X_FEEL_BOX), 2)
            + pow((other._y - Y_FEEL_BOX), 2));
    return this_dist > other_dist;
}

/**
   * Operator ==, Two apartments are identical if their x and y values
   * are the same, to the point of an epsilon = 0.0001
   * @param other
   * @return true if the two apartments are equal, false otherwise
   */
bool Apartment::operator==(const Apartment &other) const
{
    double x_dist = sqrt((_x - other._x)*(_x - other._x));
    double y_dist = sqrt((_y - other._y) * (_y - other._y));
    return (x_dist <= EPSILON && y_dist <= EPSILON);
}

std::ostream &operator<<(std::ostream &os, const Apartment &apartment) {
    os << "(" << apartment.get_x() << "," << apartment.get_y() << ")" << endl;
    return os;
}

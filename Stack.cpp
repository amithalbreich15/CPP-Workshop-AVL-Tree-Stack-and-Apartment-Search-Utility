#include "Stack.h"

Stack::Stack() = default;

Stack::Stack(std::vector<std::pair<double, double>> coordinates)
{

    for (size_t i = 0; i < coordinates.size() ; ++i)
    {
        Apartment add_apartment = Apartment(coordinates.at(i));
        apartments.push_back(add_apartment);
    }
}

void Stack::push(const Apartment &apartment)
{
    apartments.push_back(apartment);
}

void Stack::pop()
{
    if (!apartments.empty())
    {
        apartments.pop_back();
    }
    else
    {
       throw std::out_of_range (STACK_EMPTY_ERROR);
    }
}

bool Stack::empty() const
{
    return apartments.empty();

}

size_t Stack::size() const
{
    return apartments.size();
}

Apartment &Stack::top()
{
    if (!apartments.empty())
    {
        return apartments.back();
    }
    throw std::out_of_range (STACK_EMPTY_ERROR);
}

Apartment Stack::top() const
{
    if (!apartments.empty())
    {
        return apartments.back();
    }
    throw std::out_of_range(STACK_EMPTY_ERROR);
}
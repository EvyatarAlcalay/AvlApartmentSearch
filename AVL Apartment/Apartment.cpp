//
// Created by evy18 on 19/12/2021.
//

#include "Apartment.h"




Apartment::Apartment(const std::pair <double, double>& Coordinates){
    this->_x = Coordinates.first;
    this->_y = Coordinates.second;
}

double Apartment::get_x() const {
    return _x;
}

double Apartment::get_y() const {
    return _y;
}

int Apartment::distance_from_feelbox(const Apartment &other) const{
    double dist_this = sqrt((this->_x-X_FEEL_BOX)*(this->_x-X_FEEL_BOX) +
                            (this->_y-Y_FEEL_BOX)*
                            (this->_y-Y_FEEL_BOX));
    double dist_other = sqrt((other.get_x()-X_FEEL_BOX)*(other.get_x()
            -X_FEEL_BOX) + (other.get_y()-Y_FEEL_BOX) *(other.get_y()
                    -Y_FEEL_BOX));
    if (abs(dist_this-dist_other)<=EPSILON){
        return EQUAL;
    }
    else if (dist_this < dist_other){
        return LITTLE_THAN_OTHER;
    }
    else{
        return GREATER_THAN_OTHER;
    }
}

bool Apartment::operator<(const Apartment &other) const {
    return distance_from_feelbox(other) == LITTLE_THAN_OTHER;
}

bool Apartment::operator>(const Apartment &other) const {
    return distance_from_feelbox(other) == GREATER_THAN_OTHER;
}

bool Apartment::operator==(const Apartment &other) const {
    return distance_from_feelbox(other) == EQUAL;
}

std::ostream& operator<<(std::ostream &os, const Apartment &apartment){
    os << "(" << apartment.get_x() << "," << apartment.get_y() << ")"
    <<std::endl;
    return os;
}
#include "includes.h"

using namespace std;

float Ponto::x() const {
    return _x;
}

float Ponto::y() const {
    return _y;
}

float& Ponto::r() {
    return _r;
}

float& Ponto::g() {
    return _g;
}

float& Ponto::b() {
    return _b;
}

void Ponto::imprime(std::ostream& o) {
    o << "Ponto x: " << _x << ", y: " << _y;
}

bool Ponto::operator==(const Ponto& A) {
    if ( (A.x() == this->x()) && (A.y() == this->y()) )
        return true;
    else
        return false;
}

bool Ponto::operator< (const Ponto& A) {
    if ( this->y() < A.y() )
        return true;
    else if ( this->y() == A.y() ){
        if ( this->x() < A.x() )
            return true;
        else
            return false;
    } else {
        return false;
    }
}

float Ponto::produto_escalar(const Ponto& A, const Ponto& B, const Ponto& base) {
    return  ( A.x() - base.x() ) * ( B.y() - base.y() ) -
            ( B.x() - base.x() ) * ( A.y() - base.y() );
}

std::ostream& operator<< (std::ostream& o, Ponto p) {
     p.imprime(o);
     return o;
}

#ifndef PONTO_H
#define PONTO_H

class Ponto {
public:
    Ponto(float x, float y) : _x(x), _y(y), _r(0.3), _g(0.3), _b(1.0) {}
    Ponto() : _x(0), _y(0), _r(0.3), _g(0.3), _b(1.0) {}

    float x() const;

    float y() const;
    
    float& r();
    float& g();
	float& b();

    void imprime(std::ostream& o);

    bool operator==(const Ponto& A);

    bool operator< (const Ponto& A);
    
    static float produto_escalar(const Ponto& A, const Ponto& B, const Ponto& base);
    
private:
    float _x, _y;
    float _r, _g, _b;
    
};

#endif


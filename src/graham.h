#ifndef GRAHAM_H
#define GRAHAM_H

class GrahamScan {
	public:
		GrahamScan(std::vector<Ponto> pontos, Controlador& c) : pontos(pontos), c(c) {}
		void operator() ();
		void remove_mesmo_angulo_polar(std::vector<Ponto>& pontos, const Ponto& base);
	
	private:
		std::vector<Ponto> pontos;
		Controlador& c;
};

#endif
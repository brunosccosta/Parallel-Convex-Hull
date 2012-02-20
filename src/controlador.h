#ifndef CONTROL_H
#define CONTROL_H

class Controlador {

	public:	
		Controlador(std::vector< std::vector<Ponto> > &fechos) : m(), fechos(fechos) {}
		
		void salva(std::vector<Ponto> fecho);
		
	private:
		boost::mutex m;
		std::vector< std::vector<Ponto> > &fechos;
};

#endif
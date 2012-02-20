#include "includes.h"

using namespace std;

struct Comparador {
	Ponto base;

    Comparador(Ponto base) : base(base) {}
    
    bool operator()(const Ponto& A, const Ponto& B) {
        float p_escalar = Ponto::produto_escalar(A, B, base);
                     
        if (p_escalar >= 0)
            return true;
        else
            return false;
    }
};

void GrahamScan::operator()() {
	vector<Ponto>::iterator it, p_menor, p_final;
		
	stack<Ponto> pilha;
	vector<Ponto> fecho;
	
	Ponto menor, pi, topo, abaixo_topo;
		
	it = pontos.begin();
	menor = *it;
	p_menor = it;
	
	for( ; it != pontos.end(); ++it ) {
		if (*it < menor) {
			menor = *it;
			p_menor = it;
		}
	}
	
	/*
	cout << "Total: " << pontos.size() << endl;
	for ( it = pontos.begin(); it != pontos.end(); ++it) {
		cout << "Ponto x: " << (*it).x() << ", y: " << (*it).y() << endl;
	}
	*/
	
	pontos.erase(p_menor);
	std::sort(pontos.begin(), pontos.end(), Comparador(menor));
	
	/*
	cout << "Total: " << pontos.size() << endl;
	for ( it = pontos.begin(); it != pontos.end(); ++it) {
		cout << "Ponto x: " << (*it).x() << ", y: " << (*it).y() << endl;
	}
	*/
	
	remove_mesmo_angulo_polar(pontos, menor);
		
	pilha.push(menor);
	pilha.push( pontos[0] );
	pilha.push( pontos[1] );

	//já guardou dois na pilha, comecamos no 2
	for (unsigned int i=2; i < pontos.size(); i++) {
		topo = pilha.top();
		pilha.pop();
		abaixo_topo = pilha.top();
		pilha.pop();
		pi = pontos[i];
		
		while ( Ponto::produto_escalar(topo, pi, abaixo_topo) < 0) {
			topo = abaixo_topo;
			abaixo_topo = pilha.top();
			pilha.pop();
		}

		pilha.push( abaixo_topo );
		pilha.push( topo );
		pilha.push( pi );
	}

	pontos.clear();

	while ( !pilha.empty() ) {
		pontos.push_back( pilha.top() );
		pilha.pop();
	}
	
	std::reverse(pontos.begin(), pontos.end());
	
	c.salva(pontos);
}

void GrahamScan::remove_mesmo_angulo_polar(vector<Ponto>& pontos, const Ponto& base) {
	unsigned int i, j;
	Ponto p1, p2;
	
	i = 0;
	j = 1;
	
	while ( j < pontos.size() ) {
		p1 = pontos[i];
		p2 = pontos[j];
		
		if ( Ponto::produto_escalar(p1, p2, base) == 0 ) {
			if ( p1 == p2 ) {
				pontos.erase( pontos.begin() + i );
			}
			else if ( p1 < p2 ) {
				pontos.erase( pontos.begin() + i );
			}
			else {
				pontos.erase( pontos.begin() + j );
			}
		} else {
			i++;
			j++;
		}
	}
}
#include "includes.h"

using namespace std;

void Controlador::salva(vector<Ponto> fecho){
	m.lock();
		fechos.push_back(fecho);
	m.unlock();
}
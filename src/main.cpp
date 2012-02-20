#include "includes.h"

using namespace std;

int main_window;

vector<Ponto> pontos;
vector< vector<Ponto> > fechos;
vector<float> cor;

//OpenGL Functions
void idle(void){
    glutSetWindow(main_window);
    glutPostRedisplay();
}
    
void display(void) {
    int tw, th;

    tw = MAIN_WINDOW_W;
    th = MAIN_WINDOW_H;
    
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode (GL_PROJECTION);
    
    glViewport (tw/10, th/10, tw * 0.8, th * 0.8);
    
    glPointSize(5);
    glBegin(GL_POINTS);
        for( vector<Ponto>::iterator it = pontos.begin(); it != pontos.end(); ++it) {
       	    glColor3f( (*it).r(), (*it).g(), (*it).b() );
            glVertex3f( (*it).x(), (*it).y(), 0.0f );
        }
    glEnd();
    
    int i = 0;
    for( vector< vector<Ponto> >::const_iterator it = fechos.begin(); it != fechos.end(); ++it) {
   	    glColor3f(cor[i],cor[i+1],cor[i+2]);
   	    i += 3;
		glBegin(GL_LINE_STRIP);
			for( vector<Ponto>::const_iterator it2 = (*it).begin(); it2 != (*it).end(); ++it2) {
				glVertex3f( (*it2).x(), (*it2).y(), 0.0f );
			}
			vector<Ponto>::const_iterator it2 = (*it).begin();
			glVertex3f( (*it2).x(), (*it2).y(), 0.0f );
		glEnd();
	}
    
    glLoadIdentity ();  
    glutSwapBuffers();
}

void init() {
    glEnable (GL_LINE_SMOOTH);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
    glLineWidth (1.5);
}

int main (int argc, char* argv[]) {
    
    int total_pontos = 10;
    
    if ( argc > 1 ) {
        total_pontos = atoi(argv[1]);
    }
    
    srand( time(NULL) );
    for( int i = 0; i < total_pontos; i++ ) {
        float x = (rand()%1000)/1000.0;
        if (rand()%2) x *= -1;
        
        float y = (rand()%1000)/1000.0;
        if (rand()%2) y *= -1;
        pontos.push_back(Ponto( x,y ));
    }
    
	Controlador c(fechos);
    int n_thread = boost::thread::hardware_concurrency();    
    int pontos_por_grupo = total_pontos / n_thread;
    int modulo_divisao = total_pontos % n_thread;
    vector<boost::shared_ptr<boost::thread> > threads;
    
    //TODO pontos_por_grupo DEVE ser MAIOR que 3!!!
    
    for (int i=0; i < n_thread; i++) {
    	cor.push_back( (rand()%1000)/1000.0 );
    	cor.push_back( (rand()%1000)/1000.0 );
    	cor.push_back( (rand()%1000)/1000.0 );
    }
	    
	vector<Ponto> pontos_thread;
	int pos_inicial = 0;
	int pos_final = 0;
		
	for (int i=0; i<n_thread; i++){
		pontos_thread.clear();
		
		pos_final = pos_inicial + pontos_por_grupo;
		if (i < modulo_divisao) pos_final++;
				
		pontos_thread.resize(pos_final - pos_inicial);
		
		// corte em [p_inicial, p_final)
		copy(pontos.begin() + pos_inicial, pontos.begin() + pos_final, pontos_thread.begin());
				
		pos_inicial = pos_final;
		
		boost::shared_ptr<boost::thread> thread(new boost::thread( GrahamScan(pontos_thread, c) ) );
		threads.push_back(thread);
	}
	
	for (unsigned int i=0; i<threads.size(); i++) {
		threads[i]->join();
	}
    
    vector<Ponto>::iterator it, p_direita;
    Ponto inicial, direita, pi, topo, abaixo_topo;
    vector<Ponto> fecho_final;
    
    inicial = Ponto(0, -2);
	p_direita = pontos.begin();
	
    for( it = pontos.begin(); it != pontos.end(); ++it) {
		 if ( (*it).x() > (*p_direita).x() ) {
		 	p_direita = it;
		 }
    }
    
    (*p_direita).r() = 1.0;
    (*p_direita).g() = 0.0;
    (*p_direita).b() = 0.0;
    
    // OpenGL stuff    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(MAIN_WINDOW_W, MAIN_WINDOW_H);
    glutInitWindowPosition(0, 0);
    
    main_window = glutCreateWindow("Teste do Convex Hull");
    
    init();
    
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    
    glutMainLoop();

    return 0;
}

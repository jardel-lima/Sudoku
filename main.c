/*
 * =====================================================================================
 *
 *       Filename:  vertices.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10-12-2015 16:38:25
 *       Revision:  none
 *       Compiler:  gcc main.c -o main -lGL -lGLU -lglut  && ./main
 *       
 *         Author:  GUSTAVO MARQUES (), GUTODISSE AT GMAIL DOT COM
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>


/*-----------------------------------------------------------------------------
 *  MACROS
 *-----------------------------------------------------------------------------*/
#define COR_V1 c1[0],c1[1],c1[2]
#define COR_V2 c2[0],c2[1],c2[2]
#define COR_V3 c3[0],c3[1],c3[2]
#define COR_V4 c4[0],c4[1],c4[2]

/*-----------------------------------------------------------------------------
 *  CONSTANTES
 *-----------------------------------------------------------------------------*/

// TELA
#define MAX_X 600
#define MAX_Y 600

  
// 
#define X1 0
#define X2 6
#define X3 7
#define X4 5
#define Y1 8
#define Y2 8
#define Y3 9
#define Y4 5

// CORES
#define VERMELHO   1,0,0
#define VERDE      0,1,0
#define AZUL       0,0,1
#define BRANCO     1,1,1
#define AMARELO    1,1,0
#define PRETO      0,0,0

/*-----------------------------------------------------------------------------
 *  VARIAVEIS
 *-----------------------------------------------------------------------------*/
float win, aspecto;
int largura, altura;

int backup = 1;

int tr_x=0, tr_y=0, tr_z=0; // TRANSLATE

float c1[3]={PRETO}, 
      c2[3]={AMARELO},
      c3[3]={BRANCO},
      c4[3]={VERMELHO};

float p_scale=1;


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  renderStrokeFontLetter
 *  Description:  
 * =====================================================================================
 */
void escreve(
		float x,
		float y,
		float z,
		char *letter) {

	glPushMatrix();
	glTranslatef(x, y ,0);
	
	glColor3f(PRETO);
	
	glutStrokeCharacter(GLUT_STROKE_ROMAN,'H');

	glPopMatrix();
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  DesenhaPoligono
 *  Description:  Fun��o que faz o desenho do tabuleiro
 * =====================================================================================
 */
void DesenhaTabela()
{
	int i;
	
	// TRANSLATE                		
	glTranslatef(tr_x, tr_y, tr_z);
	tr_x = tr_y = tr_z = 0;

	// ESCALA
	glScalef(p_scale, p_scale, p_scale);
	p_scale = 1;
	
	// Desenha as linhas
	for(i=-4; i<6; i++)
	{
		glBegin(GL_LINES);      
			glColor3f( PRETO );
			glVertex2f( -4 , i );
		  	glVertex2f(  5 , i );       
		glEnd();    
    	}
    	
    	// Desenha as colunas
    	for(i=-4; i<6; i++)
	{
		// Desenha o poligono  
		glBegin(GL_LINES);      
			glColor3f( PRETO );
			glVertex2f( i, -4 );
		  	glVertex2f( i,  5 );       
		glEnd();    
    	}
}
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  DesenhaPoligono
 *  Description:  Fun��o que faz o desenho do POLIGONO
 * =====================================================================================
 */
void DesenhaPoligono()
{
	// TRANSLATE                		
	glTranslatef(tr_x, tr_y, tr_z);
	tr_x = tr_y = tr_z = 0;

	// ESCALA
	glScalef(p_scale, p_scale, p_scale);
	p_scale = 1;

	// Desenha o poligono  
	glBegin(GL_POLYGON);      
		
		glColor3f ( COR_V1);
		glVertex2f( X1,Y1 );
	  	
		glColor3f ( COR_V2);	
		glVertex2f( X2,Y2 );
	 	
		glColor3f ( COR_V3);	
		glVertex2f( X3,Y3 );

		glColor3f ( COR_V4);	
		glVertex2f( X4,Y4 );             
	glEnd();    
    
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Desenha
 *  Description:  Fun��o de callback de redesenho da janela de visualiza��o
 * =====================================================================================
 */
void Desenha(void)
{
	// Limpa a janela de visualiza��o com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Define a Viewport 1
	glViewport(0, 0, largura, altura);
	// Desenha a casa na Viewport 1                        
	//DesenhaPoligono();
	DesenhaTabela();
	
	escreve(0,0,0,"1");
	
	// Executa os comandos OpenGL 
	glFlush();
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  AlteraTamanhoJanela
 *  Description:  Fun��o callback chamada quando o tamanho da janela � alterado
 * =====================================================================================
 */
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Evita a divisao por zero
	if(h == 0) h = 1;
	
	// Atualiza as vari�veis
	largura = w;
	altura = h;

	aspecto = (float) largura/altura;	
	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Estabelece a janela de sele��o (esquerda, direita, inferior, 
	// superior) mantendo a propor��o com a janela de visualiza��o
	gluOrtho2D (-win*aspecto, win*aspecto, -win, win);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  TecladoEspecial
 *  Description:  Fun��o callback chamada para gerenciar eventos de teclas especiais
 * =====================================================================================
 */
void TecladoEspecial (int key, int x, int y) 
{
	switch(key)
	{
		case GLUT_KEY_HOME:
			glPopMatrix();
			backup = 1;
			p_scale =1;
		break;
		case GLUT_KEY_PAGE_UP:
			p_scale = 1.5;
		break;
		case GLUT_KEY_PAGE_DOWN:
			p_scale = 0.5;
		break;
		case GLUT_KEY_LEFT:
			tr_x = -1;
		break;
		case GLUT_KEY_RIGHT:
			tr_x = 1;
		break;
	}
	glutPostRedisplay();	
}	

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Teclado
 *  Description:  Fun��o callback chamada para gerenciar eventos de teclas
 * =====================================================================================
 */
void Teclado (unsigned char key, int x, int y)
{
	// 0       1      2
	// RED - GREEN - BLUE
	switch(key)
	{
		case 'B':
			c4[2] += 0.1;
		break;
		case 'b':
			c4[2] -= 0.1;
		break;
		case 'V':
			c2[1] += 0.1;
		break;
		case 'v':
			c2[1] -= 0.1;
		break;
		case 27:
		case 'q':
		case 'Q':
			exit(0);
		break;
	}
	glutPostRedisplay();
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  GerenciaMouse
 *  Description:  Fun��o callback chamada para gerenciar eventos do mouse
 * =====================================================================================
 */
void GerenciaMouse(int button, int state, int x, int y)
{       
	int linha, coluna, i;
	printf("coluna[%d]linha[%d]\n",(int) (x-405)/70 ,(int) (y-36)/69 ); 
	if (button == GLUT_RIGHT_BUTTON)
	{

	}

	if(button == GLUT_LEFT_BUTTON )
	{

	}   

	/*
	if (button == GLUT_LEFT_BUTTON || button ==GLUT_RIGHT_BUTTON) 
	{
	    glMatrixMode(GL_PROJECTION);
	    glLoadIdentity(); 
	    gluOrtho2D (-win*aspecto, win*aspecto, -win, win);
	    glutPostRedisplay();
	}
	*/
	//glutPostRedisplay();
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Inicializa
 *  Description:  Fun��o respons�vel por inicializar par�mentros e vari�veis
 * =====================================================================================
 */
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualiza��o como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	win = 5.5f;
}
 
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main(int argc, char** argv)
{
	// Init 
	glutInit(&argc, argv);
       	
	// Define do modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
 
	// Especifica a posi��o inicial da janela GLUT
	glutInitWindowPosition(5,5); 
    
	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(MAX_X,MAX_Y); 
 
	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Sudoku");
 
	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);
  
	// Registra a fun��o callback de redimensionamento da janela de visualiza��o
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a fun��o callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);
  
	// Registra a fun��o de callback para tratamento de teclas especiais
	glutSpecialFunc (TecladoEspecial);

	// Registra a fun��o callback para tratamento do mouse
	glutMouseFunc(GerenciaMouse);  
	
	// ATIVA A JANELA EM FULLSCREEN
	glutFullScreen();
	
	// Chama a fun��o respons�vel por fazer as inicializa��es 
	Inicializa();
 
	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();
 
	return 0;
}

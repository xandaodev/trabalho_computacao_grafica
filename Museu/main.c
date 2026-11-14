#include <GL/glut.h>
#include <stdlib.h>
#include "camera.h"
#include "scene.h"

// ------------------------------------------------------------
// Projeto Museu 3D - Computacao Grafica
// Codigo-base fornecido pelo professor.
//
// ------------------------------------------------------------

int largura = 1000;
int altura = 700;

void desenho()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    configuraProjecao(largura, altura);
    aplicaCamera();

    desenhaCena();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    largura = (w > 0) ? w : 1;
    altura  = (h > 0) ? h : 1;
    glViewport(0, 0, largura, altura);
}

void idle()
{
    atualizaAnimacao();
    glutPostRedisplay();
}

void inicializa()
{
    glClearColor(0.08f, 0.08f, 0.10f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    inicializaCamera();
    inicializaCena();
}

// teclas normais
void teclado(unsigned char tecla, int x, int y)
{
    switch (tecla)
    {
        // movimentacao da camera
        case 'w': case 'W': andaFrente(0.3f); break;
        case 's': case 'S': andaFrente(-0.3f); break;
        case 'a': case 'A': andaLado(-0.3f); break;
        case 'd': case 'D': andaLado(0.3f); break;
        case 'q': case 'Q': sobeDesce(0.3f); break;
        case 'e': case 'E': sobeDesce(-0.3f); break;

        // projecoes
        case 'p': case 'P': usaPerspectiva();break;
        case 'o': case 'O': usaOrtografica(); break;

        // sombreamento
        case 'f': case 'F': usaFlat(); break;
        case 'g': case 'G': usaSmooth(); break;

        // luz e animacao
        case 'l': case 'L': alternaIluminacao(); break;
        case ' ': alternaAnimacao(); break;

        // esc fecha o programa
        case 27: exit(0);
    }
}

// setas giram a camera
//esquerda e direita viram pros lados e cima e baixo inclinam o olhar
void teclasEspeciais(int tecla, int x, int y)
{
    switch (tecla)
    {
        case GLUT_KEY_LEFT: giraCamera(-0.05f, 0.0f); break;
        case GLUT_KEY_RIGHT: giraCamera(0.05f, 0.0f); break;
        case GLUT_KEY_UP: giraCamera(0.0f, 0.05f); break;
        case GLUT_KEY_DOWN: giraCamera(0.0f, -0.05f); break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(largura, altura);
    glutCreateWindow("Museu 3D - Computacao Grafica");

    inicializa();

    glutDisplayFunc(desenho);
    glutReshapeFunc(reshape);   
    glutIdleFunc(idle);

    // registra as funcoes do teclado
    glutKeyboardFunc(teclado);
    glutSpecialFunc(teclasEspeciais);

    glutMainLoop();

    return 0;
}

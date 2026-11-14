#include <GL/glut.h>
#include "consoles.h"

// ------------------------------------------------------------
// CONSOLES DA EXPOSICAO
// ------------------------------------------------------------

// regras pra encaixar no pedestal
// desenhar o console centrado na origem com a parte de baixo em y 0
// caber mais ou menos numa caixa de 1.2 de largura por 1.2 de profundidade
// a frente do console fica virada pro z positivo que e de onde o visitante vem
// o scene.c ja faz o translate pra cima do pedestal entao aqui nao precisa

// caixa provisoria pra ver onde o console vai ficar
// e so apagar quando o console de verdade estiver pronto
static void caixaProvisoria(float r, float g, float b)
{
    glPushMatrix();

        glTranslatef(0.0f, 0.3f, 0.0f);
        glScalef(1.0f, 0.6f, 0.8f);

        glColor3f(r, g, b);

        glutSolidCube(1.0);

    glPopMatrix();
}

// game boy 1989
void desenhaGameBoy()
{
    caixaProvisoria(0.80f, 0.80f, 0.75f);
}

// super nintendo 1990
void desenhaSNES()
{
    caixaProvisoria(0.65f, 0.65f, 0.75f);
}

// playstation 1994
void desenhaPlayStation()
{
    caixaProvisoria(0.55f, 0.55f, 0.60f);
}

// nintendo switch 2017
void desenhaSwitch()
{
    caixaProvisoria(0.90f, 0.20f, 0.20f);
}

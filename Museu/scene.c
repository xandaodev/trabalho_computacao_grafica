#include <GL/glut.h>
#include "scene.h"
#include "consoles.h"

// ------------------------------------------------------------
// ESTADO DA CENA
// ------------------------------------------------------------

static int iluminacaoLigada = 1;
static int animacaoLigada = 1;

static float anguloAnimacao = 0.0f;

// ------------------------------------------------------------
// FUNCOES AUXILIARES
// ------------------------------------------------------------

void configuraIluminacao()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Luz ambiente geral
    GLfloat ambiente[] = {
        0.20f, 0.20f, 0.20f, 1.0f
    };

    // Luz difusa
    GLfloat difusa[] = {
        0.80f, 0.80f, 0.80f, 1.0f
    };

    // Luz especular
    GLfloat especular[] = {
        1.00f, 1.00f, 1.00f, 1.0f
    };

    GLfloat posicao[] = {
        0.0f, 7.0f, 4.0f, 1.0f
    };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, especular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicao);
}

void configuraMaterialExemplo()
{
    GLfloat especular[] = {
        0.8f, 0.8f, 0.8f, 1.0f
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 60.0f);
}

// ------------------------------------------------------------
// ELEMENTOS DO AMBIENTE
// ------------------------------------------------------------

// piso quadriculado tipo tabuleiro pra lembrar jogo
// sao quadrados de 2 por 2 alternando laranja e verde agua
void desenhaPiso()
{
    glPushMatrix();

    glNormal3f(0.0f, 1.0f, 0.0f);

    for (int i = -6; i < 6; i++)
    {
        for (int j = -6; j < 6; j++)
        {
            // se a soma for par usa uma cor e se for impar usa a outra
            if ((i + j) % 2 == 0)
                glColor3f(0.95f, 0.50f, 0.30f);
            else
                glColor3f(0.15f, 0.60f, 0.65f);

            float x = i * 2.0f;
            float z = j * 2.0f;

            glBegin(GL_QUADS);
                glVertex3f(x,0.0f, z);
                glVertex3f(x,0.0f, z + 2.0f);
                glVertex3f(x + 2.0f, 0.0f,z + 2.0f);
                glVertex3f(x + 2.0f, 0.0f, z);
            glEnd();
        }
    }

    glPopMatrix();
}

void desenhaParedeFundo()
{
    glPushMatrix();

    glColor3f(0.22f, 0.24f, 0.28f);

    glBegin(GL_QUADS);

        glNormal3f(0.0f, 0.0f, 1.0f);

        glVertex3f(-12.0f, 0.0f, -8.0f);
        glVertex3f( 12.0f, 0.0f, -8.0f);
        glVertex3f( 12.0f, 8.0f, -8.0f);
        glVertex3f(-12.0f, 8.0f, -8.0f);

    glEnd();

    glPopMatrix();
}

void desenhaParedeEsquerda()
{
    glPushMatrix();

    glColor3f(0.18f, 0.20f, 0.23f);

    glBegin(GL_QUADS);

        glNormal3f(1.0f, 0.0f, 0.0f);

        glVertex3f(-12.0f, 0.0f,-8.0f);
        glVertex3f(-12.0f, 0.0f,8.0f);
        glVertex3f(-12.0f, 8.0f,8.0f);
        glVertex3f(-12.0f, 8.0f,-8.0f);

    glEnd();

    glPopMatrix();
}

// parede da direita igual a da esquerda so que em x 12
// a normal aponta pra dentro da sala
void desenhaParedeDireita()
{
    glPushMatrix();

    glColor3f(0.18f, 0.20f, 0.23f);

    glBegin(GL_QUADS);

        glNormal3f(-1.0f, 0.0f, 0.0f);

        glVertex3f(12.0f, 0.0f,-8.0f);
        glVertex3f(12.0f, 8.0f,-8.0f);
        glVertex3f(12.0f, 8.0f,8.0f);
        glVertex3f(12.0f, 0.0f,8.0f);

    glEnd();

    glPopMatrix();
}

// teto em y 8 que e a altura das paredes
// as cordas das moedas ficam presas nele
void desenhaTeto()
{
    glPushMatrix();

    glColor3f(0.14f, 0.15f, 0.18f);

    glBegin(GL_QUADS);

        glNormal3f(0.0f, -1.0f, 0.0f);

        glVertex3f(-12.0f, 8.0f, -8.0f);
        glVertex3f(-12.0f, 8.0f,8.0f);
        glVertex3f(12.0f, 8.0f,8.0f);
        glVertex3f(12.0f, 8.0f,-8.0f);

    glEnd();

    glPopMatrix();
}

// ------------------------------------------------------------
// OBJETO-EXEMPLO
// ------------------------------------------------------------

void desenhaObjetoExemplo()
{
    glPushMatrix();

        glTranslatef(-3.0f, 1.0f, -2.0f);
        glRotatef(anguloAnimacao, 0.0f, 1.0f, 0.0f);
        glScalef(2.0f, 2.0f, 2.0f);

        glColor3f(0.75f, 0.55f, 0.20f);

        glutSolidCube(1.0);

    glPopMatrix();
}

// ------------------------------------------------------------
// ESTANDES
// ------------------------------------------------------------

// pedestal e um cubo esticado com 2 de altura
// translada pra cima em 1 porque o cubo e desenhado pelo centro
void desenhaPedestal(float x)
{
    glPushMatrix();

        glTranslatef(x, 1.0f, -4.0f);
        glScalef(1.5f, 2.0f, 1.5f);

        glColor3f(0.40f, 0.40f, 0.42f);

        glutSolidCube(1.0);

    glPopMatrix();
}

// moeda dourada pendurada em cima de cada pedestal
// e a animacao do museu porque fica girando no eixo y
void desenhaMoeda(float x)
{
    GLUquadric *q = gluNewQuadric();

    // moeda
    glPushMatrix();

        glTranslatef(x, 5.0f, -4.0f);
        glRotatef(anguloAnimacao, 0.0f, 1.0f, 0.0f);

        // o cilindro nasce em z 0 e cresce pra frente
        // volta metade da espessura pra girar pelo centro
        glTranslatef(0.0f, 0.0f, -0.075f);

        glColor3f(1.0f, 0.80f, 0.10f);

        // borda da moeda
        gluCylinder(q, 0.5, 0.5, 0.15, 32, 1);

        // face de tras virada 180 graus pra normal apontar pra fora
        glPushMatrix();
            glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
            gluDisk(q, 0.0, 0.5, 32, 1);
        glPopMatrix();

        // face da frente
        glTranslatef(0.0f, 0.0f, 0.15f);
        gluDisk(q, 0.0, 0.5, 32, 1);

    glPopMatrix();

    // corda que liga a moeda ate o teto
    // o cilindro nasce deitado no z entao gira 90 graus no x pra ficar em pe
    glPushMatrix();

        glTranslatef(x, 5.5f, -4.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

        glColor3f(0.10f, 0.10f, 0.10f);

        gluCylinder(q, 0.02, 0.02, 2.5, 8, 1);

    glPopMatrix();

    gluDeleteQuadric(q);
}

void desenhaObjetosDoMuseu()
{
    // ========================================================
    // ALUNO:
    // Substitua/adapte esta funcao para criar o museu.
    //
    // Requisitos minimos sugeridos:
    //   - pelo menos 3 objetos relevantes ao tema;
    //   - uso de translacao, rotacao e escala;
    //   - materiais diferentes;
    //   - segunda fonte de luz;
    //   - uma animacao relacionada ao tema.
    //
    // ========================================================

    // os 4 estandes ficam em linha seguindo a ordem dos anos
    // da esquerda pro mais antigo ate a direita pro mais novo
    float posicoes[4] = { -6.0f, -2.0f, 2.0f, 6.0f };

    for (int i = 0; i < 4; i++)
    {
        desenhaPedestal(posicoes[i]);
        desenhaMoeda(posicoes[i]);
    }

    // cada console vai em cima do seu pedestal
    // o topo do pedestal fica em y 2 entao sobe 2 e vai pro z dos estandes
    glPushMatrix();
        glTranslatef(posicoes[0], 2.0f,-4.0f);
        desenhaGameBoy();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(posicoes[1], 2.0f, -4.0f);
        desenhaSNES();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(posicoes[2], 2.0f, -4.0f);
        desenhaPlayStation();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(posicoes[3], 2.0f, -4.0f);
        desenhaSwitch();
    glPopMatrix();
}

void configuraLuzesDaCena()
{
    // ========================================================
    // ALUNO:
    // Adicione aqui pelo menos uma segunda fonte de luz.
    //
    // Sugestao:
    //   GL_LIGHT1
    //
    // A dupla deve explicar:
    //   - posicao da luz;
    //   - componente ambiente;
    //   - componente difusa;
    //   - componente especular.
    // ========================================================
}

// ------------------------------------------------------------
// CENA PRINCIPAL
// ------------------------------------------------------------

void desenhaCena()
{
    // Posicao das luzes deve ser definida em MODELVIEW.
    glMatrixMode(GL_MODELVIEW);

    if (iluminacaoLigada)
    {
        glEnable(GL_LIGHTING);

        // A luz base e configurada aqui.
        configuraIluminacao();

        // Area que deve ser implementada pela dupla.
        configuraLuzesDaCena();
    }
    else
    {
        glDisable(GL_LIGHTING);
    }

    desenhaPiso();
    desenhaParedeFundo();
    desenhaParedeEsquerda();
    desenhaParedeDireita();
    desenhaTeto();

    // Objeto fornecido pelo professor.
    // desenhaObjetoExemplo();

    // Objetos desenvolvidos pela dupla.
    desenhaObjetosDoMuseu();
}

// ------------------------------------------------------------
// CONTROLES
// ------------------------------------------------------------

void inicializaCena()
{
    glShadeModel(GL_SMOOTH);

    configuraMaterialExemplo();
}

void alternaIluminacao()
{
    // inverte entre ligado e desligado
    iluminacaoLigada = !iluminacaoLigada;
}

void usaFlat()
{
    // uma cor so pra cada face
    glShadeModel(GL_FLAT);
}

void usaSmooth()
{
    // interpola a cor entre os vertices
    glShadeModel(GL_SMOOTH);
}

void alternaAnimacao()
{
    // inverte entre ligado e desligado
    animacaoLigada = !animacaoLigada;
}

void atualizaAnimacao()
{
    if (!animacaoLigada)
        return;

    anguloAnimacao += 0.5f;

    if (anguloAnimacao >= 360.0f)
        anguloAnimacao -= 360.0f;
}

#include <GL/glut.h>
#include "scene.h"

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

void desenhaPiso()
{
    glPushMatrix();

    glColor3f(0.35f, 0.35f, 0.38f);

    glBegin(GL_QUADS);

        glNormal3f(0.0f, 1.0f, 0.0f);

        glVertex3f(-12.0f, 0.0f, -12.0f);
        glVertex3f( 12.0f, 0.0f, -12.0f);
        glVertex3f( 12.0f, 0.0f,  12.0f);
        glVertex3f(-12.0f, 0.0f,  12.0f);

    glEnd();

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

        glVertex3f(-12.0f, 0.0f, -8.0f);
        glVertex3f(-12.0f, 0.0f,  8.0f);
        glVertex3f(-12.0f, 8.0f,  8.0f);
        glVertex3f(-12.0f, 8.0f, -8.0f);

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

    // Exemplo temporario para orientar os alunos:
    glPushMatrix();

        glTranslatef(3.0f, 1.0f, -2.0f);
        glScalef(1.5f, 1.5f, 1.5f);

        glColor3f(1.0f, 0.0f, 0.0f);

        glutSolidSphere(1.0, 32, 16);

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

    // Objeto fornecido pelo professor.
    desenhaObjetoExemplo();

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
    
}

void usaFlat()
{
    
}

void usaSmooth()
{
   
}

void alternaAnimacao()
{
   
}

void atualizaAnimacao()
{
    if (!animacaoLigada)
        return;

    anguloAnimacao += 0.5f;

    if (anguloAnimacao >= 360.0f)
        anguloAnimacao -= 360.0f;
}

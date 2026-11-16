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

// cubo esticado que e usado pra montar quase todas as pecas
// x y z e o centro da peca e sx sy sz e o tamanho dela
// a cor tem que ser escolhida antes de chamar
static void peca(float x, float y, float z, float sx, float sy, float sz){
    glPushMatrix();

        glTranslatef(x, y, z);
        glScalef(sx, sy, sz);

        glutSolidCube(1.0);

    glPopMatrix();
}

// botao redondo pequeno feito com esfera
static void botao(float x, float y, float z, float raio){
    glPushMatrix();

        glTranslatef(x, y, z);
        glutSolidSphere(raio, 12, 8);

    glPopMatrix();
}

// game boy 1989
// portatil em pe com a tela em cima e os botoes embaixo
void desenhaGameBoy(){
    glPushMatrix();

        // inclina um pouco pra tras pra parecer apoiado
        glRotatef(-10.0f, 1.0f, 0.0f, 0.0f);

        // corpo
        glColor3f(0.765f, 0.741f, 0.725f);
        peca(0.0f, 0.5f, 0.0f, 0.6f, 1.0f, 0.18f);

        // tela com uma borda escura em volta
        glColor3f(0.271f, 0.337f, 0.071f);
        peca(0.0f, 0.70f, 0.09f, 0.44f, 0.36f, 0.02f);

        glColor3f(0.75f, 0.78f, 0.70f);
        peca(0.0f, 0.70f, 0.10f, 0.36f, 0.28f, 0.02f);

        // direcional em cruz feito com dois cubos
        glColor3f(0.141f, 0.141f, 0.149f);
        peca(-0.15f, 0.30f, 0.10f, 0.16f, 0.05f, 0.03f);
        peca(-0.15f, 0.30f, 0.10f, 0.05f, 0.16f, 0.03f);

        // dois botoes um do lado do outro
        glColor3f(0.604f, 0.129f, 0.345f);
        botao(0.10f, 0.30f, 0.10f, 0.04f);
        botao(0.20f, 0.30f, 0.10f, 0.04f);

    glPopMatrix();
}

// controle com fio do super nintendo
// fica deitado em cima do pedestal na frente do console
static void controleSNES(float x, float z){
    GLUquadric *q = gluNewQuadric();

    glPushMatrix();

        glTranslatef(x, 0.08f, z);
        glRotatef(30.0f, 1.0f, 0.0f, 0.0f);

        // meio do controle e as duas pontas arredondadas
        glColor3f(0.70f, 0.70f, 0.72f);
        peca(0.0f, 0.0f, 0.0f, 0.22f, 0.06f, 0.14f);

        glPushMatrix();
            glTranslatef(-0.11f, 0.0f, 0.0f);
            glScalef(1.0f, 0.43f, 1.0f);
            glutSolidSphere(0.07, 16, 8);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.11f, 0.0f, 0.0f);
            glScalef(1.0f, 0.43f, 1.0f);
            glutSolidSphere(0.07, 16, 8);
        glPopMatrix();

        // botoes
        glColor3f(0.20f, 0.20f, 0.25f);
        peca(-0.12f, 0.03f, 0.0f, 0.06f, 0.02f, 0.02f);
        peca(-0.12f, 0.03f, 0.0f, 0.02f, 0.02f, 0.06f);
        botao(0.10f, 0.03f, 0.02f, 0.015f);
        botao(0.14f, 0.03f, -0.01f, 0.015f);

        // fio indo pra tras ate o console
        // o cilindro cresce pro z positivo entao gira 180 no y pra ir pra tras
        glColor3f(0.30f, 0.30f, 0.30f);
        glPushMatrix();
            glTranslatef(0.0f, 0.0f, -0.07f);
            glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(q, 0.01, 0.01, 0.25, 6, 1);
        glPopMatrix();

    glPopMatrix();

    gluDeleteQuadric(q);
}

// super nintendo 1990
// caixa baixa e larga com o cartucho encaixado em cima e dois controles
void desenhaSNES(){
    // corpo do console mais pra tras pra sobrar espaco pros controles
    glColor3f(0.75f, 0.75f, 0.78f);
    peca(0.0f, 0.125f, -0.2f, 1.1f, 0.25f, 0.7f);

    // entrada do cartucho
    glColor3f(0.45f, 0.45f, 0.50f);
    peca(0.0f, 0.26f, -0.25f, 0.55f, 0.02f, 0.25f);

    // cartucho saindo pra cima
    glColor3f(0.35f, 0.35f, 0.38f);
    peca(0.0f, 0.42f, -0.25f, 0.45f, 0.32f, 0.08f);

    // etiqueta na frente do cartucho
    glColor3f(0.000f, 0.608f, 0.820f);
    peca(0.0f, 0.44f, -0.205f, 0.35f, 0.18f, 0.01f);

    // botoes de ligar e resetar
    glColor3f(0.400f, 0.314f, 0.706f);
    peca(-0.38f, 0.26f, -0.05f, 0.12f, 0.03f, 0.10f);
    peca(0.38f, 0.26f, -0.05f, 0.12f, 0.03f, 0.10f);

    // controles na frente
    controleSNES(-0.28f, 0.4f);
    controleSNES(0.28f, 0.4f);
}

// controle do playstation com as duas alcas
static void controlePS(float x, float z){
    glPushMatrix();

        glTranslatef(x, 0.08f, z);
        glRotatef(30.0f, 1.0f, 0.0f, 0.0f);

        glColor3f(0.65f, 0.65f, 0.68f);
        peca(0.0f, 0.0f, 0.0f, 0.30f, 0.06f, 0.12f);

        // alcas inclinadas pra baixo e pra fora
        glPushMatrix();
            glTranslatef(-0.12f, -0.01f, 0.08f);
            glRotatef(-20.0f, 0.0f, 1.0f, 0.0f);
            peca(0.0f, 0.0f, 0.0f, 0.07f, 0.06f, 0.16f);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.12f, -0.01f, 0.08f);
            glRotatef(20.0f, 0.0f, 1.0f, 0.0f);
            peca(0.0f, 0.0f, 0.0f, 0.07f, 0.06f, 0.16f);
        glPopMatrix();

        // botoes
        glColor3f(0.25f, 0.25f, 0.28f);
        peca(-0.09f, 0.03f, 0.0f, 0.06f, 0.02f, 0.02f);
        peca(-0.09f, 0.03f, 0.0f, 0.02f, 0.02f, 0.06f);
        botao(0.09f, 0.03f, -0.02f, 0.012f);
        botao(0.09f, 0.03f, 0.02f, 0.012f);
        botao(0.07f, 0.03f, 0.0f, 0.012f);
        botao(0.11f, 0.03f, 0.0f, 0.012f);

    glPopMatrix();
}

// playstation 1994
// caixa com a tampa redonda aberta mostrando o cd
void desenhaPlayStation(){
    GLUquadric *q = gluNewQuadric();

    // corpo
    glColor3f(0.70f, 0.70f, 0.72f);
    peca(0.0f, 0.11f, -0.15f, 0.9f, 0.22f, 0.75f);

    // cd em cima do corpo
    // o disco nasce virado pro z entao gira -90 no x pra deitar
    glPushMatrix();

        glTranslatef(-0.1f, 0.222f, -0.15f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

        glColor3f(0.85f, 0.85f, 0.90f);
        gluDisk(q, 0.03, 0.22, 32, 1);

    glPopMatrix();

    // tampa aberta
    // gira pela parte de tras da tampa que e onde fica a dobradica
    glPushMatrix();

        glTranslatef(-0.1f, 0.22f, -0.43f);
        glRotatef(-70.0f, 1.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, 0.0f, 0.28f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

        glColor3f(0.62f, 0.62f, 0.65f);

        // borda da tampa
        gluCylinder(q, 0.28, 0.28, 0.04, 32, 1);

        // parte de baixo virada 180 graus pra normal apontar pra fora
        glPushMatrix();
            glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
            gluDisk(q, 0.0, 0.28, 32, 1);
        glPopMatrix();

        // parte de cima
        glTranslatef(0.0f, 0.0f, 0.04f);
        gluDisk(q, 0.0, 0.28, 32, 1);

    glPopMatrix();

    // botoes redondos do lado direito
    glColor3f(0.40f, 0.40f, 0.45f);
    glPushMatrix();
        glTranslatef(0.3f, 0.22f, -0.3f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(q, 0.05, 0.05, 0.02, 16, 1);
        glTranslatef(0.0f, 0.0f, 0.02f);
        gluDisk(q, 0.0, 0.05, 16, 1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.3f, 0.22f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(q, 0.05, 0.05, 0.02, 16, 1);
        glTranslatef(0.0f, 0.0f, 0.02f);
        gluDisk(q, 0.0, 0.05, 16, 1);
    glPopMatrix();

    gluDeleteQuadric(q);

    // controle na frente
    controlePS(0.0f, 0.38f);
}

// nintendo switch 2017
// tela larga encaixada na base com um controle em cada lado
void desenhaSwitch(){
    // base onde a tela fica encaixada
    glColor3f(0.20f, 0.20f, 0.22f);
    peca(0.0f, 0.225f, -0.1f, 0.8f, 0.45f, 0.25f);

    glPushMatrix();

        // a tela fica na frente da base e um pouco inclinada pra tras
        glTranslatef(0.0f, 0.45f, 0.06f);
        glRotatef(-8.0f, 1.0f, 0.0f, 0.0f);

        // corpo da tela
        glColor3f(0.08f, 0.08f, 0.09f);
        peca(0.0f, 0.0f, 0.0f, 0.9f, 0.5f, 0.06f);

        // parte que acende
        glColor3f(0.15f, 0.22f, 0.32f);
        peca(0.0f, 0.0f, 0.031f, 0.72f, 0.40f, 0.01f);

        // controles dos lados
        glColor3f(0.000f, 0.608f, 0.820f);
        peca(-0.51f, 0.0f, 0.0f, 0.12f, 0.5f, 0.07f);

        glColor3f(0.992f, 0.125f, 0.086f);
        peca(0.51f, 0.0f, 0.0f, 0.12f, 0.5f, 0.07f);

        // analogicos
        glColor3f(0.15f, 0.15f, 0.15f);
        botao(-0.51f, 0.10f, 0.04f, 0.03f);
        botao(0.51f, -0.08f, 0.04f, 0.03f);

        // botoes
        botao(-0.51f, -0.10f, 0.04f, 0.015f);
        botao(0.51f, 0.12f, 0.04f, 0.015f);
        botao(0.48f, 0.09f, 0.04f, 0.015f);
        botao(0.54f, 0.09f, 0.04f, 0.015f);

    glPopMatrix();
}
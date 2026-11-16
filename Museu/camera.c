#include <GL/glut.h>
#include <math.h>
#include "camera.h"

// Camera simples.
//
// A camera olha para um ponto-alvo.
// O aluno pode modificar este arquivo para criar uma navegacao
// mais sofisticada.

static float camX = 0.0f;
static float camY = 3.0f;
static float camZ = 12.0f;

static float alvoX = 0.0f;
static float alvoY = 2.0f;
static float alvoZ = 0.0f;

static int perspectiva = 1;

// angulos da camera em radianos
// yaw gira pros lados e pitch olha pra cima e pra baixo
static float yaw = 0.0f;
static float pitch = 0.0f;

void inicializaCamera(){
    camX = 0.0f;
    camY = 3.0f;
    camZ = 12.0f;

    alvoX = 0.0f;
    alvoY = 2.0f;
    alvoZ = 0.0f;

    perspectiva = 1;

    // comeca olhando pro mesmo ponto que a professora colocou
    yaw = 0.0f;
    pitch = atan2f(alvoY - camY, camZ - alvoZ);
}

void aplicaCamera(){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        camX, camY, camZ,
        alvoX, alvoY, alvoZ,
        0.0f, 1.0f, 0.0f
    );
}

void configuraProjecao(int largura, int altura){
    float aspecto = (altura == 0) ? 1.0f: (float)largura / (float)altura;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (perspectiva){
        gluPerspective(
            60.0,
            aspecto,
            0.5,
            100.0
        );
    }else{
        float metadeAltura = 10.0f;
        float metadeLargura = metadeAltura * aspecto;

        glOrtho(
            -metadeLargura, metadeLargura,
            -metadeAltura, metadeAltura,
            -50.0, 50.0
        );
    }

    glMatrixMode(GL_MODELVIEW);
}

void usaPerspectiva(){
    perspectiva = 1;
}

void usaOrtografica(){
    perspectiva = 0;
}

// Movimento simples.

// nao deixa a camera atravessar as paredes o piso e o teto
static void limitaPosicao(){
    if (camX < -11.5f) camX = -11.5f;
    if (camX >  11.5f) camX =11.5f;
    if (camZ <  -7.5f) camZ = -7.5f;
    if (camZ >  14.0f) camZ = 14.0f;
    if (camY <   0.5f) camY = 0.5f;
    if (camY >   7.5f) camY = 7.5f;
}

// recalcula o ponto pra onde a camera olha usando os angulos
//o alvo fica sempre um passo na frente da camera
static void atualizaAlvo(){
    alvoX = camX + cosf(pitch) * sinf(yaw);
    alvoY = camY + sinf(pitch);
    alvoZ = camZ - cosf(pitch) * cosf(yaw);
}

//anda pra frente ou pra tras na direcao que a camera ta olhando
// passo positivo vai pra frente e negativo volta
// ignora o pitch pra camera nao entrar no chao quando olha pra baixo
void andaFrente(float passo){
    camX += sinf(yaw) * passo;
    camZ -= cosf(yaw) * passo;

    limitaPosicao();
    atualizaAlvo();
}

// anda de lado usando o vetor perpendicular a direcao da camera
// passo positivo vai pra direita e negativo pra esquerda
void andaLado(float passo){
    camX += cosf(yaw) * passo;
    camZ += sinf(yaw) * passo;

    limitaPosicao();
    atualizaAlvo();
}

// sobe ou desce a camera sem mudar pra onde ela olha
void sobeDesce(float passo){
    camY += passo;

    limitaPosicao();
    atualizaAlvo();
}

// gira a camera mudando os angulos
// o pitch tem limite pra camera nao virar de cabeca pra baixo
void giraCamera(float dYaw, float dPitch){
    yaw += dYaw;
    pitch += dPitch;

    if (pitch >  1.2f) pitch =  1.2f;
    if (pitch < -1.2f) pitch = -1.2f;

    atualizaAlvo();
}
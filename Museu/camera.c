#include <GL/glut.h>
#include <math.h>
#include "camera.h"

// ------------------------------------------------------------
// Camera simples.
//
// A camera olha para um ponto-alvo.
// O aluno pode modificar este arquivo para criar uma navegacao
// mais sofisticada.
// ------------------------------------------------------------

static float camX = 0.0f;
static float camY = 3.0f;
static float camZ = 12.0f;

static float alvoX = 0.0f;
static float alvoY = 2.0f;
static float alvoZ = 0.0f;

static int perspectiva = 1;

void inicializaCamera()
{
    camX = 0.0f;
    camY = 3.0f;
    camZ = 12.0f;

    alvoX = 0.0f;
    alvoY = 2.0f;
    alvoZ = 0.0f;

    perspectiva = 1;
}

void aplicaCamera()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        camX, camY, camZ,
        alvoX, alvoY, alvoZ,
        0.0f, 1.0f, 0.0f
    );
}

void configuraProjecao(int largura, int altura)
{
    float aspecto = (altura == 0) ? 1.0f: (float)largura / (float)altura;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (perspectiva)
    {
        gluPerspective(
            60.0,
            aspecto,
            0.5,
            100.0
        );
    }
    else
    {
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

void usaPerspectiva()
{
    perspectiva = 1;
}

void usaOrtografica()
{
    perspectiva = 0;
}

// ------------------------------------------------------------
// Movimento simples.
// ------------------------------------------------------------


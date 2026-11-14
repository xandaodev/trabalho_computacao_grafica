#ifndef CAMERA_H
#define CAMERA_H

void inicializaCamera();

void aplicaCamera();
void configuraProjecao(int largura, int altura);

void usaPerspectiva();
void usaOrtografica();

// movimentacao da camera pelo teclado
void andaFrente(float passo);
void andaLado(float passo);
void sobeDesce(float passo);
void giraCamera(float dYaw, float dPitch);


#endif

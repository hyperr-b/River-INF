#ifndef MOVIMENTO_H
#define MOVIMENTO_H




int moveteclado_aviao(float *aviao_x);
void move_constante_aviao(float *aviao_y);
void tiro_origem(float *tiro_y, float *tiro_x, float *aviao_x, float *aviao_y, int tiroativo);
int tiro_movimento(float *tiro_y);


#endif
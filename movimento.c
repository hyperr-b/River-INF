#include "raylib.h"
#include "movimento.h"

// funçao que faza aviao se mover para a esquerda ou para a direita baseada no que é digitado no teclado
void moveteclado_aviao(float *aviao_x){
    if(IsKeyDown(KEY_D)){
        *aviao_x += 0.05;
    }
    else if(IsKeyDown(KEY_A)){
        *aviao_x -= 0.05;
    }
    
}
// funçao que faz o aviao se mover constantemente para frente
void move_constante_aviao(float *aviao_y){
    
    *aviao_y -= 0.05;
    
}
//funçao que analisa se um tiro foi feito 
void tiro_origem(float *tiro_y, float *tiro_x, float *aviao_x, float *aviao_y){
    if(IsKeyPressed(KEY_K) || IsKeyPressed(KEY_SPACE)){
        *tiro_y = *aviao_y;
        *tiro_x = *aviao_x; 
        
        }
    }
// atualiza a  posiçao do tiro retorna se ele aidna esta na tela =1
int tiro_movimento(float *tiro_y){
    int ativo = 0;
    if(*tiro_y > 0) {
    *tiro_y -= 1;
    ativo = 1;
    }
else ativo = 0;

return ativo;
}

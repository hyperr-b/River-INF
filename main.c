# include "raylib.h"
# include <stdio.h>
#include "movimento.h"

# define ALTURA_MAPA 20
# define LARGURA_MAPA 24
# define NUMEROFASES 3



char mapa[ALTURA_MAPA][LARGURA_MAPA];

//Função para carregar mapa do nível:
    void CarregaMapa(const char *arqNivel){
        FILE *level = fopen(arqNivel, "r");   //Abre o arquivo .txt do nível
        
        //Leitura do arquivo linha por linha:
        for (int y = 0; y < ALTURA_MAPA; y++){
            
            //Se o arquivo acabar acabar, preenche com espaços em branco
            if(fgets(mapa[y], LARGURA_MAPA + 2, level) == NULL){
                for (int x = 0; x < LARGURA_MAPA; x++){
                    mapa[y][x] = ' ';
                }
            }

            //Continua leitura linha por linha e salva em um arranjo
            for (int x = 0; x < LARGURA_MAPA; x++){
                if (mapa[y][x] == '\n'){
                    mapa[y][x] = '\0';
                    break;
                }
            }

        
    }
   
    
    fclose(level);   //Fecha o arquivo

}

int main(){
    //incializaçao variaveis de posiçao aviao, tiro
    float aviao_x =  LARGURA_MAPA/2, aviao_y = ALTURA_MAPA+1;
    //PARA FAZER PROXIMA FASE
    char *fases[NUMEROFASES] = {"levels/level_1.txt", "levels/level_2.txt", "levels/level_3.txt"};
    
    int tiroativo = 0, sentido = 2, detectorxaviao, detectoryaviao, i = 0, novomapa = 0, fasecompleta = 0;
    float tiro_x;
    float tiro_y =   0;
    //Inicialização da janela do jogo:
    const int screenWidth = 960;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "River-INF");

    SetTargetFPS(60);   //Configura o jogo para rodar a 60 frames por segundo

    //Inicialização das texturas
    Texture2D terra = LoadTexture("resources/terra.png");
    Texture2D terra2 = LoadTexture("resources/terra2.png");
    Texture2D agua = LoadTexture("resources/agua.png");
    Texture2D aviao = LoadTexture("resources/aviao.png");
    Texture2D aviao_direita = LoadTexture("resources/aviao-direita.png");
    Texture2D aviao_esquerda = LoadTexture("resources/aviao-esquerda.png");
    Texture2D tiro = LoadTexture("resources/tiro.png");
    Texture2D combustivel = LoadTexture("resources/combustivel.png");
    //TENTATIVA PARA LOOP
    CarregaMapa(fases[i]);
    
    //Loop principal:
    while (!WindowShouldClose())   //Detecta o botão de fechar do Windows ou a tecla ESC para finalizar o programa
    {
        //Se trocar mapa
       
         CarregaMapa(fases[i]);
       
        
        
         
         
        
        BeginDrawing();
        
       
            ClearBackground(RAYWHITE);   //Coloca a cor de fundo como branco

            //Desenho do mapa:
            for (int y = 0; y < ALTURA_MAPA; y++){
                for (int x = 0; x < LARGURA_MAPA; x++){
                    //Análise do caractere e da textura a ser desenhada:
                    switch (mapa[y][x]){
                        case 'T':
                            DrawTexture(terra, x * 40, y * 40, WHITE);
                            break;
                        case 't':
                            DrawTexture(terra2, x * 40, y * 40, WHITE);
                            break;
                        case ' ':
                            DrawTexture(agua, x * 40, y * 40, WHITE);
                            break;
                        case 'A':
                            DrawTexture(aviao, x * 40, y * 40, WHITE);
                            break;
                        case 'D':
                            DrawTexture(aviao_direita, x * 40, y * 40, WHITE);
                            break;
                        case 'E':
                            DrawTexture(aviao_esquerda, x * 40, y * 40, WHITE);
                            break;
                        case 'B':
                            DrawTexture(tiro, x * 40, y * 40, WHITE);
                            break;
                        case 'C':
                            DrawTexture(combustivel, x * 40, y * 40, WHITE);
                            break;
                    }
                     
                }
                    
            }
            //chamada das funçoes que movem o aviao
            sentido = moveteclado_aviao(&aviao_x);
            move_constante_aviao(&aviao_y); 

            //chamda funçoe que analisa tiro
           tiroativo = tiro_movimento(&tiro_y);
            if(!tiroativo){
                tiro_origem(&tiro_y, &tiro_x, &aviao_x, &aviao_y, tiroativo);
                 
            }
           if(tiroativo){
            DrawTexture(tiro, tiro_x * 40, tiro_y * 40, WHITE);
           }
       
           
        
            
            

            // PRECISA AJEITAR ESTA FEIA desenho do aviao tentando cuidar para andra so no oceano, se for agua segue se nao vlta para o ponto de partida
            //faz com que assim que ele encote ele ja retorne 
            //para identificar se ele esta indo para direita ou esquerda para poder fazer com que assim que toqeu na parede ele desapareça
            if(aviao_x>12)
                detectorxaviao = aviao_x+1;
                else 
                detectorxaviao = aviao_x;
                //para fazer com que ele ande um ouco mais apos o fim do mapa  
                if(aviao_y >19)
                    detectoryaviao = aviao_y -2;
                    else 
                        detectoryaviao = aviao_y;
            if(mapa[(int)(detectoryaviao)][detectorxaviao] == ' ' || mapa[(int)(detectoryaviao)][detectorxaviao] == 'C' ){
                if(sentido ==2){
                 DrawTexture(aviao, aviao_x *40, aviao_y *40, WHITE);
                }
                else if(sentido == 1){
                    DrawTexture(aviao_direita, aviao_x * 40, aviao_y * 40, WHITE);
                }
                 else if(sentido == 0){
                    DrawTexture(aviao_esquerda, aviao_x * 40, aviao_y * 40, WHITE);
                }
           
            }
            else{
                aviao_x = LARGURA_MAPA/2;
                aviao_y = ALTURA_MAPA+1;
            }

            //PARA TENTAR FAZER PROXIMA FASE
            
            if((detectoryaviao)  <0 ){
                fasecompleta = 1;
            }
            else{
                fasecompleta = 0;
            }
            if(fasecompleta == 1){ 
                   
                    if(i > NUMEROFASES-2){
                       i = 0;
                       // novomapa = 1;
                         
                    }
                    else{
                       i++;
                        //novomapa = 1;
                         
                    }
                }
        
           
            EndDrawing();
        }
    
        

    

    UnloadTexture(terra);   //Descarrega a textura da memória

    //Finalização
    CloseWindow();

    return 0;
}
#include <stdio.h>
#include <stdlib.h>


typedef struct info_symbl{
    int symbl;
    int freq;
    int binary_code;
}InfSymbl;

typedef struct lligada { //Struct da Lista ligada de blocos que prefazem um ficheiro
    int nbloco; //número do bloco
    int tamanho_bloco; //tamano do bloco
    InfSymbl arr[256]; //frequência de cada símbolo
    struct lligada *prox;
}*LInt;



int modulo_t(char *fileName){
    if(correct_file(fileName, "qerf.")){
        FILE *fp = fopen(fileName, "r+");

        if(fp == NULL){
            printf("Não foi possível ler o ficheiro!");
            return 0;
        }

        char file_type;
        int num_blocos;
        int ant_freq;

        fscanf(fp, "@%c@%d@", &file_type, &num_blocos);

        LInt info_blocos; //criar função
        //acrescentar 0 (*10)
        //acrescentar 1 (*10+1)

        LInt *inicio_info_blocos = info_blocos;


        //while(fp) ver se é necessário, not sure

        for(int nb = 1; nb <= num_blocos; nb++){
            info_blocos->prox = criar_lista();
            
            info_blocos->nbloco = nb;
            fscanf(fp, "%d@", &info_blocos->tamanho_bloco);
            
            for(int i=0; i<=256; i++){ //caso particular do ;; em que valor da freq é igual ao anterior
                if(fscanf(fp, "%d", &info_blocos->arr[i].freq) == 1){
                    ant_freq = &info_blocos->arr[i].freq;
                    fseek(fp, 1, SEEK_CUR);
                } else{
                    info_blocos->arr[i].freq = ant_freq;
                }
            }
            info_blocos = info_blocos->prox;
        }

        freqDecres(info_blocos->arr, 256);
        

        fclose(fp);
    }else{
        printf("Tipo de ficheiro incorreto!");
    } 

}


void swap(int *xp, int *yp){ 
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
  
// A function to implement bubble sort 
void freqDecres(InfSymbl arr[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++){
        for (j = 0; j < n-i-1; j++){
            if (arr[j].freq < arr[j+1].freq){
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}



int correct_file (char s1[], char s2[]){
    int i, j=0, ans=0;

    for(i=0;s1[i];i++);

    for(i--,j; s2[j],s1[i]==s2[j]; i--,j++);

    if(!s2[j]) ans = 1; //s2[j]=='\0'

    return ans;
}
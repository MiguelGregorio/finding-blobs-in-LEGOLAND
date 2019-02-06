#include <stdio.h>
#include <string.h>
#include "auxiliar.h"

int main(){
	
	FILE *f;
	char info[50];
	Imagem *ListImg = NULL;
	Pixel p;
	int tamVI =0, tamVP=0;
	int l, c, canal;
	int num;
	int r=-1,g=-1,b=-1;
	int i, j, k;
	int cl=0, cc=0;
	Zona **vz=NULL;
	int tamVZ=0;
	
	int altura=0, largura=0, n=0;
	

	
	int rr, gg, bb, di;
	
	
	int opcao = menu();
    if(opcao == 0){
    	return 0;
	}
	
	while(opcao != 0){
		switch(opcao){
				case 1:
	
	
					f = fopen("imgs.txt", "r");
					
					if(f == NULL){
									printf("Erro ao abrir o ficheiro de imagens!\n");
								}
								
								else{
									printf("Ficheiro de imagens aberto com sucesso!\n");
								
									
										while( (fgets(info, sizeof(info), f))!=NULL ){
										
											num=words(info);
											
										//	if(strstr(info,"20" )!=NULL){
										//		printf("ola");
										//	}
											
											if(num==1 && strstr(info, "IMG") != NULL ){ //se encontrar o inicio de uma imagem
											
												
												ListImg = (Imagem*) realloc (ListImg, ++tamVI * sizeof(Imagem));
												strcpy(ListImg[tamVI-1].nome, info);
												cc=0;
												cl=0;
								
											}
											
											if(num ==3){ 
												sscanf(info, "%d %d %d", &l, &c,&canal);
												
												ListImg[tamVI-1].linhas=l;
												ListImg[tamVI-1].colunas=c;
												
												ListImg[tamVI-1].m=(Pixel**) malloc(l*sizeof(Pixel*));
												
												for(i=0; i<ListImg[tamVI-1].linhas; i++){
													ListImg[tamVI-1].m[i]=(Pixel*)malloc(c*sizeof(Pixel));
												}
												
												
											}
											
											if(num==1 && strstr(info, "IMG") == NULL){
												if(r==-1){
													r=atoi(info);
													//printf("VALOR DE R=%d\n", r);
												}
												
												else if(r!=-1 && g==-1 && b==-1){
													g=atoi(info);
												}
												
												else if(r!= -1 && g!= -1 && b==-1){
													b=atoi(info);
												
													
													p.r=r;
													p.g=g;
													p.b=b;
											
													
													if(cc==ListImg[tamVI-1].colunas){
														cl++;
														cc=0;
													}
													
													ListImg[tamVI-1].m[cl][cc]=p;
													ListImg[tamVI-1].m[cl][cc].flag=0;
													
													//printf("valores r ---> %d \n",ListImg[tamVI-1].m[cl][cc].r );
													//printf("valores g---> %d \n",ListImg[tamVI-1].m[cl][cc].g );
													//printf("valores b---> %d \n",ListImg[tamVI-1].m[cl][cc].b );
													
													
													cc++;
														
													
													
													
													r=-1;
													g=-1;
													b=-1;
													
													
												
												}
											}	
										}
								}
									
						
						
						break;
						
						case 2:
							
							printf("introduza um valor de r: "); scanf("%d", &rr);
							printf("introduza um valor de g: "); scanf("%d", &gg);
							printf("introduza um valor de b: "); scanf("%d", &bb);
							printf("introduza a tolerancia pretendida: "); scanf("%d", &di);
							
							
							for(i=0; i< tamVI; i++){
								for(j=0; j< ListImg[i].linhas; j++){
									for(k=0; k< ListImg[i].colunas; k++){
										
										if(((ListImg[i].m[j][k].r >= rr-di) && (ListImg[i].m[j][k].r <= rr+di)) &&
											((ListImg[i].m[j][k].g >= gg-di) && (ListImg[i].m[j][k].g <= gg+di))&&
											((ListImg[i].m[j][k].b >= bb-di) && (ListImg[i].m[j][k].b <= bb+di)) && ListImg[i].m[j][k].flag==0){
												
												
											vz= (Zona**) realloc(vz, ++tamVZ*sizeof(Zona*));
												
											vz[tamVZ-1]=flood(&(ListImg[i].m), j, k,r,g,b,di);
												
											strcpy(vz[tamVZ-1]->nome, ListImg[i].nome);	
											
											//printf("altura = %d  largura= %d \n", vz[tamVZ-1]->altura, vz[tamVZ-1]->largura);
												
											}
										
									}
								}
							}
							
						for(i =0; i<tamVZ; i++){
							printf("NOME : %s ", vz[i]->nome);
							printf("( , ):  pixeis \n");
							printf("\n");
							
						}
							
							break;
						default:
						printf("Deve introduzir uma opcao valida!\n");
						}
		opcao = menu();
				}
				
			}



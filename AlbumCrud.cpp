#include <stdio.h>
#include <conio2.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>

#define TF 100
#define TFM 20
#define TS 31
#define KEY_UP 72
#define KEY_DOWN 80
// --------------------------------------------------------------------------- STRUCTS ---------------------------------------------------------------------------------------------------
struct album{
	int ano_alb;
	int qtd_msc;
	char nome_alb[TS];
	char nome_aut[TS];
	char nome_gen[TS];
	char nome_msc[TFM][TS];	
};

// --------------------------------------------------------------------------- FIM STRUCTS ----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------Funcoes Utilidade. Menu. Execução-------------------------------------------------------------------------------------
void LimpaSeta(int x,int y)
{
    gotoxy(x,y);
    printf("   ");
}


char Setinha(int opcoes,int x,int y)
{
    opcoes--;
    char hit;
    int pos = 0;
    while(hit !=13)
    {
        gotoxy(x,pos+y);
        printf(" ->");
        gotoxy(x,pos+y);
        hit = getch();
        LimpaSeta(x,pos+y);
        if(hit == 72)
        {
            if(pos == 0)
            {
                pos=opcoes;
            }
            else 
                pos--;
        }
        else if(hit == 80)
        {
            if(pos == opcoes)
                pos = 0;
            else
                pos++;
        }
    }
    return pos+1;
}

void Limpa(int x, int y, int num)
{
	gotoxy(x,y);while(num--)printf(" ");
}
void Moldura(int CI, int LI, int CF, int LF, int cor)
{
	int i;
	
	textcolor(cor);

	Sleep(13);
	gotoxy(CI,LI); printf("#");
	gotoxy(CF,LF); printf("#");
	gotoxy(CF,LI); printf("#");
	gotoxy(CI,LF); printf("#");
	
	//Coluna ate Coluna F
	for(i=CI+1; i<CF; i++)
	{
		gotoxy(i,LI);printf("-");
		Sleep(8);
		gotoxy(i,LF);printf("-");
	}
	//Linha ate Linha F
	for(i=LI+1; i<LF; i++)
	{
		gotoxy(CI,i);printf(".");
		Sleep(8);	
		gotoxy(CF,i);printf(".");
	}

}


char Menu(){
//---------------------------------------------------------------------Configurações iniciais de tela-------------------------------------------------------------------------------------
	clrscr();
	Moldura(1,1,80,25,13);
	textcolor(9);
//----------------------------------------------------------------------------------------Opcoes desejas ao usuario-----------------------------------------------------------------------
	gotoxy(15,2);printf("------------- Estrobo's Som ------------");
	gotoxy(15,3);printf("Selecione a opcao que deseja! (Setas do teclado)");
	gotoxy(15,5);printf("   Cadastrar Album");	
	gotoxy(15,6);printf("   Alterar Album");
	gotoxy(15,7);printf("   Listagem");
	gotoxy(15,8);printf("   Pesquisar");
	gotoxy(15,9);printf("   Excluir Album:");
	gotoxy(15,10);printf("   Estatisticas Gerais:");
	gotoxy(15,11);printf("   Sair");
	
	return Setinha( 7, 15, 5);
}
//------------------------------------------------------------------------------Fim de Funcoes Utilidade. Menu. Excecução -------------------------------------------------------------------
//------------------------------------------------------------------------------Inicio Funcoes Para manipulação de dados dos albuns ---------------------------------------------------------
void LeMusica(album &Albuns)
{
	int i=0;
	while(i <Albuns.qtd_msc)
	{
		gotoxy(15,17);printf("->Nome da Musica %d: ",i+1);
		fflush(stdin);gets(Albuns.nome_msc[i++]);
		Limpa(15,17,66);
		if(strlen(Albuns.nome_msc[i-1]) >= TFM)
		{
			gotoxy(15,20);printf("Nome da musica excedido!");
			i--;
			gotoxy(15,17);printf("->Nome da Musica %d: ",i+1);
			fflush(stdin);gets(Albuns.nome_msc[i++]);
			Limpa(15,17,52);
		}
			
	}
}

void LeAlbum(album Albuns[TF], int &TLA)
{
	int i=0;
	gotoxy(15,9);printf("Digite as informacoes do Album!");
	gotoxy(15,11);printf("-> Nome: ");
	fflush(stdin);gets(Albuns[TLA].nome_alb);
	for(i=0; i<TLA; i++)
	{
		while(stricmp(Albuns[TLA].nome_alb,Albuns[i].nome_alb) == 0)
		{
			gotoxy(15,10);textcolor(10);printf("Album ja existe, Digite outro nome");Limpa(15,11,31);textcolor(13);
			gotoxy(15,11);printf("-> Nome: ");
			fflush(stdin);gets(Albuns[TLA].nome_alb);Limpa(15,10,34);
		}
	}
		
		
	gotoxy(15,12);printf("-> Ano: ");
	scanf("%d",&Albuns[TLA].ano_alb);
	gotoxy(15,13);printf("-> Autor(Artista,Banda,Dupla,Grupo(...)): ");
	fflush(stdin);gets(Albuns[TLA].nome_aut);
	gotoxy(15,14);printf("-> Genero: ");
	fflush(stdin);gets(Albuns[TLA].nome_gen);
	gotoxy(15,16);printf("-> Qtd Musicas (Maximo -> 20): ");
	scanf("%d",&Albuns[TLA].qtd_msc);
	while(Albuns[TLA].qtd_msc <= 0 || Albuns[TLA].qtd_msc > TFM)
	{
		textcolor(10);gotoxy(15,30);printf("Erro! Quantidade de musicas invalida! ");
		gotoxy(15,16);printf("-> Qtd Musicas (Maximo -> 20): ");textcolor(13);
		scanf("%d",&Albuns[TLA].qtd_msc);
	}
	Limpa(15,30,100);
	LeMusica(Albuns[TLA]);	
	TLA++;
	getch();
}

void ExibeAlbum(album Albuns,int i)
{
	
	
	gotoxy(15,8);printf("-------- Album %d ---------",i+1);
	gotoxy(15,10);printf("Nome -> %s",Albuns.nome_alb);
	gotoxy(15,11);printf("Ano -> %d",Albuns.ano_alb);
	gotoxy(15,12);printf("Autor -> %s",Albuns.nome_aut);
	gotoxy(15,13);printf("Qtd Msc -> %d",Albuns.qtd_msc);
	gotoxy(15,14);printf("Genero -> %s",Albuns.nome_gen);
	getch();
	Limpa(23,10,strlen(Albuns.nome_alb) + 8);
	Limpa(22,11,4);
	Limpa(24,12,strlen(Albuns.nome_aut));
	Limpa(26,13,2);
	Limpa(25,14,strlen(Albuns.nome_gen));

}
void ExibeAlbuns(album Albuns[], int TLA)
{
	int i=0;
	for(i=0; i<TLA; i++)
	{
		textcolor(12);
		ExibeAlbum(Albuns[i], i);
		
	}
}
int BuscaAlbum(album Albuns[], int TLA, char nome[TS])
{
	int pos=0;
	while(pos < TLA && stricmp(Albuns[pos].nome_alb,nome) !=0 )
		pos++;

	if(pos <TLA)
		return pos;
	else
	{
		gotoxy(15,20);textcolor(10);printf("Erro! Album nao encontrado");
		pos =-1;
		return pos;
	}
	
}
void AlteraAlbum(album Albuns[TF],int pos)
{
	gotoxy(15,10);printf("Alterar album %s",Albuns[pos].nome_alb);
	gotoxy(15,12);printf("Ano: ");scanf("%d",&Albuns[pos].ano_alb);
	gotoxy(15,13);printf("Artista: ");fflush(stdin);gets(Albuns[pos].nome_aut);
	gotoxy(15,14);printf("-> Qtd Musicas (Maximo -> 20): ");
	scanf("%d",&Albuns[pos].qtd_msc);
	while(Albuns[pos].qtd_msc <= 0 || Albuns[pos].qtd_msc > TFM)
	{
		textcolor(10);gotoxy(15,30);printf("Erro! Quantidade de musicas invalida! ");
		gotoxy(15,16);printf("-> Qtd Musicas (Maximo -> 20): ");
		scanf("%d",&Albuns[pos].qtd_msc);
	}
	LeMusica(Albuns[pos]);	
}
void DeletaAlbum(album Albuns[],int pos, int &TLA)
{
	char op='N';
	int j=0, i;
	textcolor(11);
	gotoxy(15,10);printf("Deletando Album %s",Albuns[pos].nome_alb);
	gotoxy(15,12);printf("Deseja Continuar ? S/N");
	fflush(stdin);scanf("%c",&op);
	Limpa(15,12,23);
	op=toupper(op);
	if(op == 'S')
	{
		for(i=pos; i<TLA-1; i++)
		{
			Albuns[i] = Albuns[i+1];
		}
		TLA--;
		
		gotoxy(15,12);printf("Excluido com sucesso!");
	}		
	else
	{
		gotoxy(15,12);printf("Exclusao cancelada!!");
	}
		
	getch();
}
void ExibeMusicas(album Albuns)
{
	int i;
	textcolor(11);gotoxy(15,5);printf("-------- Lista de albuns e  suas musicas ---------");textcolor(13);
	for(i=0; i<TFM; i++)
	{
		if (i <10)
			Limpa(5,15+i,31);
		if (i >= 10 )
			Limpa(40,15+(i-10),31);			
	}	
	
	for(i=0; i<Albuns.qtd_msc; i++)
	{
		if(i < 10)
		{
			gotoxy(5,15+i);printf("%s",Albuns.nome_msc[i]);
		}
		
		if(i >= 10)
		{
			gotoxy(40,15+(i-10));printf("%s",Albuns.nome_msc[i]);
		}
	}
	
}

void ListaGenero(album Albuns[TF], int TLA)
{
	int i=0, j=0, rep=0;
	char GenerosAux[TF][TS];
	int TLG=0;
	for(i=0; i<TLA; i++)
	{
		j=0;
		while(j <TLG && stricmp(Albuns[i].nome_gen, GenerosAux[j] ) != 0)
			j++;
			
		if( j == TLG )
		{
			strcpy(GenerosAux[TLG++] , Albuns[i].nome_gen);
			textcolor(11);gotoxy(15,5);printf("Genero: %s",Albuns[i].nome_gen);textcolor(13);
			for(j=0; j<TLA; j++)
			{
				if(stricmp(Albuns[j].nome_gen , Albuns[i].nome_gen ) ==0 )
					ExibeAlbum(Albuns[j], j);
			}
			
			Limpa(15,5,31);
		}
	}
}
void PesquisaMusica(album Albuns[TF], int TLA, char nome[TS])
{
	int i,pos =0, enc=0, j;
	gotoxy(15,10);printf("Musica: %s",nome);
	for(i=0; i<TLA; i++)
	{
		for(j=0; j< Albuns[i].qtd_msc; j++ )
		{
			if( stricmp(Albuns[i].nome_msc[j] , nome) == 0)
			{
				textcolor(12);
				gotoxy(15,12+enc);printf("Album: %s Artista: %s",Albuns[i].nome_alb,Albuns[i].nome_aut);
				enc++;
			}
		}	
	}
	if(enc !=0)
		gotoxy(15,22),printf("%d musicas encontradas!",enc);
	else
	{
		gotoxy(15,11);textcolor(10);printf("Nenhuma Encontrada!");textcolor(13);
	}
}
void PesquisaAutor(album Albuns[TF], int TLA, char nome[TS])
{
	int pos=0,i;
	while(pos < TLA && stricmp(Albuns[pos].nome_aut , nome ) !=0 ) // verifica se realmente existe
		pos++;
	if(pos <TLA) // se existir exibe os albuns que ele possui
	{
		textcolor(11);gotoxy(15,6);printf("Artista: %s",Albuns[pos].nome_aut);
		textcolor(13);
		for(i=0; i<TLA; i++)
		{
			if( stricmp(Albuns[i].nome_aut , nome)==0 )
				ExibeAlbum(Albuns[i],i);
		}
	}
	else
	{
		gotoxy(15,10);printf("Artista nao encontrado!");
	}
}
void PesquisaAno(album Albuns[TF], int TLA, int ano)
{
	int pos=0,i;
	while(pos < TLA &&  ano != Albuns[pos].ano_alb ) // verifica se realmente existe
		pos++;
		
	if(pos <TLA) // se existir exibe os albuns que ele possui
	{
		textcolor(11);gotoxy(15,6);printf("Albuns lancados em %d",Albuns[pos].ano_alb);
		textcolor(13);
		for(i=0; i<TLA; i++)
		{
			if( Albuns[i].ano_alb == ano )
				ExibeAlbum(Albuns[i],i);
		}
	}
	else
	{
		gotoxy(15,10);printf("Nenhum album cadastrado com esse ANO !");
	}
}
void Estatistica(album Albuns[TF], int TLA)
{
	int i,k, contG[TLA*20] , MaiorG=0, j, TLCG=0, MaiorAno=0, ano, TLM=0, contQtd[TLA], MaiorQtd=0;
	char  auxMusica[TLA*20][TS], auxAutor[TLA][TS];
	float totm=0;
	for(i=0; i<TLA*20; i++) // zera vetor
		contG[i] = 0;
	for(i=0; i<TLA; i++)
		contQtd[i] =0;
	
	for(i=0; i<TLA; i++) // for album
	{
		for(j=0; j<Albuns[i].qtd_msc; j++)  // Maior Musica gravada
		{
			for(k = 0; k< TLCG && stricmp(Albuns[i].nome_msc[j], auxMusica[k]) !=0 ; k++);
			
			if(k == TLCG)
			{
				contG[TLCG]++;
				strcpy(auxMusica[TLCG++] , Albuns[i].nome_msc[j]);
				
			}
			else
			{
				contG[k]++;
				if(contG[k] > contG[MaiorG])
					MaiorG = k;
			}
				
		}
		
		//Maior Qtd Musica
		for(k = 0; k< TLM && stricmp(Albuns[i].nome_aut, auxAutor[k]) !=0 ; k++);	
		if(k == TLM)
		{
			strcpy(auxAutor[TLM] ,  Albuns[i].nome_aut);
			contQtd[TLM]  =  Albuns[i].qtd_msc;
			TLM++;
		}
		else
		{
			contQtd[k]+= Albuns[i].qtd_msc;
			if(contQtd[k] > contQtd[MaiorQtd])
				MaiorQtd = k;
		}
			
		
		
	
		//Ano Musica
		int contAno =0;
		for(j=0; j<TLA; j++)
		{
			if(Albuns[i].ano_alb == Albuns[j].ano_alb)
				contAno ++;
		}
		
		if(contAno > MaiorAno)
		{
			MaiorAno = contAno;
			ano = Albuns[i].ano_alb;
		}
		
		
		totm += Albuns[i].qtd_msc; //Media
	}
	textcolor(11);
	gotoxy(10,10);printf("A musica mais gravada foi: %s quantidade: %d vezes ",auxMusica[MaiorG],contG[MaiorG]);
	gotoxy(10,11);printf("o Artista com mais musicas gravadas foi: %s com %d musicas ",auxAutor[MaiorQtd], contQtd[MaiorQtd]);
	gotoxy(10,12);printf("O ano com mais albuns foi: %d quantidade: %d ",ano,MaiorAno);
	gotoxy(10,13);printf("Media de Musicas nos albuns ! %.2f ",totm / TLA);
}
//------------------------------------------------------------------------------Fim das Funcoes Para manipulação de dados dos albuns --------------------------------------------------------

//------------------------------------------------------------------------------Progama de Execução------------------------------------------------------------------------------------------
void Executa()
{
	int cod_alb, cod_msc, cod_gen,  TLA=0, pos=0, ano;
	album Albuns[TF];
	char op,op2, nome[TS];
	//Exibe Menu e executa Opcao Desejada
	do
	{
		op = Menu();
		clrscr();
		Moldura(1,1,80,25,13);
		switch(op)
		{
			case 1:
				gotoxy(15,5);printf("-> Cadastro de Album <-");
				LeAlbum(Albuns,TLA);
				getch();
				break;
			case 2:
				gotoxy(15,6);printf("-> Alterar album <-");
				gotoxy(15,7);printf("Digite o nome do album: ");
				fflush(stdin);gets(nome);
				pos = BuscaAlbum(Albuns,TLA,nome);
				if(pos != -1)
				{
					AlteraAlbum(Albuns,pos);
				}
				getch();
				break;
			case 3:
				gotoxy(15,2);printf("Digite a opcao que deseja!");
				gotoxy(15,3);printf("   A-Listagem de albuns");
				gotoxy(15,4);printf("   B-Albuns e musicas");
				gotoxy(15,5);printf("   C-Generos");
				gotoxy(15,6);printf("   Voltar");
				op2 = Setinha(4,15,3);
				switch(op2)
				{
					
					case 1:
						Limpa(15,2,50);
						Limpa(15,3,50);
						Limpa(15,4,50);
						Limpa(15,5,50);
						Limpa(15,6,50);
						if(TLA  > 0 )
							ExibeAlbuns(Albuns, TLA);
						else
						{
							textcolor(10);gotoxy(15,13);printf("Vazio! nenhum cadastrado");	
							getch();
						}
					
					break;
					case 2:
						Limpa(15,2,50);
						Limpa(15,3,50);
						Limpa(15,4,50);
						Limpa(15,5,50);
						Limpa(15,6,50);
						if(TLA > 0)
						{
							gotoxy(15,9);
							Limpa(15,10,TS+9);
							for(pos =0; pos < TLA; pos++)
							{
								ExibeMusicas(Albuns[pos]);
								ExibeAlbum(Albuns[pos],pos);
							}
						}
						else
						{
							textcolor(10);gotoxy(15,13);printf("Vazio! nenhum cadastrado");
							getch();
						}
						break;
					case 3:
						printf("Generos");
							Limpa(15,2,50);
							Limpa(15,3,50);
							Limpa(15,4,50);
							Limpa(15,5,50);
							Limpa(15,6,50);
						if(TLA>0)
							ListaGenero(Albuns,TLA);
						else
						{
							textcolor(10);gotoxy(15,13);printf("Vazio! nenhum cadastrado");
							getch();
						}
					break;	
				}
			
				break;
			case 4:
				gotoxy(15,2);printf("selecione a opcao que deseja!");
				gotoxy(15,3);printf("   A-Pesquisa por musica");
				gotoxy(15,4);printf("   B-Pesquisa por artista");
				gotoxy(15,5);printf("   C-Pesquisa por ano");
				gotoxy(15,6);printf("   Voltar");
				fflush(stdin);op2 = Setinha(4,15,3);
				switch(op2)
				{
					
					case 1:
						if(TLA  > 0 )
						{
							Limpa(15,2,50);
							Limpa(15,3,50);
							Limpa(15,4,50);
							Limpa(15,5,50);
							Limpa(15,6,50);
							
							gotoxy(15,8);printf("Musica: ");fflush(stdin);gets(nome);
							Limpa(15,8,31);
							PesquisaMusica(Albuns, TLA, nome);
							getch();
						}
						else
						{
							textcolor(10);gotoxy(15,13);printf("Vazio! nenhum cadastrado");	
							getch();
						}
					break;
					case 2:
						if(TLA > 0)
						{
							Limpa(15,2,50);
							Limpa(15,3,50);
							Limpa(15,4,50);
							Limpa(15,5,50);
							Limpa(15,6,50);
							gotoxy(15,8);printf("Autor: ");fflush(stdin);gets(nome);
							Limpa(15,8,strlen(nome));
							PesquisaAutor(Albuns, TLA, nome);	
							
						}
						else
						{
							textcolor(10);gotoxy(15,13);printf("Vazio! nenhum cadastrado");
							getch();
						}
					break;
					case 3:
						Limpa(15,2,50);
						Limpa(15,3,50);
						Limpa(15,4,50);
						Limpa(15,5,50);
						Limpa(15,6,50);
						if(TLA > 0)
						{
							gotoxy(15,8);printf("Ano: ");scanf("%d",&ano);
							Limpa(15,8,10);
							PesquisaAno(Albuns, TLA, ano);
						
						}
						else
						{
							textcolor(10);gotoxy(15,13);printf("Vazio! nenhum cadastrado");
							getch();
						}
						
					break;	
				}
				break;
			case 5:
				gotoxy(15,9);printf("-> Deletar Album <-");
				if(TLA > 0)
				{
					gotoxy(15,10);printf("-> Nome: ");
					fflush(stdin);gets(nome);
					pos = BuscaAlbum(Albuns,TLA,nome);
					if(pos != -1)
						DeletaAlbum(Albuns,pos,TLA);	
				}
				else
					textcolor(10),gotoxy(15,10),printf("Nenhum album cadastrado");
			
				getch();
				break;
			case 6:
				
			{	gotoxy(15,9);printf("-> Estatistica dos Albuns <-");
				if(TLA >0)
					Estatistica(Albuns, TLA);
			
				else
					textcolor(10),gotoxy(15,12),printf("# # # Erro! nenhum album cadastrado # # #");	
				getch();
				break;
			}
		}	
	}while(op != 7);
//-------------------------------------------------------------------------------------Encerando o Progama-----------------------------------------------------------------------------------;
	gotoxy(22,12);
	textcolor(9);
	printf(" # # #  F I M   # # #");
	printf("\n\n\n");
	Sleep(2000);
}
//------------------------------------------------------------------------------FIM Progama de Execução ---------------------------------------------------------------------------------------


int main(void)
{
	Executa();
	return 1;
}

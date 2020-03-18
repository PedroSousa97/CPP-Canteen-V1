#include <iostream>
#include <fstream>
#include <stdlib.h>     
#include <time.h>
#include <string>
#include <locale.h>
#include "FunctionsFile.h"
#include "Entidade.h"
#include "Mesa.h"
#include "Refeiçao.h"
using namespace std;

int main() {
	setlocale(LC_ALL, "Portuguese");

	srand(time(NULL));

	string * primeirosnomes = new string[contaLinhas("primeiro_nome.txt")];
	preencheArray(primeirosnomes, "primeiro_nome.txt");
	string * ultimosnomes = new string[contaLinhas("ultimo_nome.txt")];
	preencheArray(ultimosnomes, "ultimo_nome.txt");
	string * cursos = new string[contaLinhas("cursos.txt")];						//Leitura, contagem de linhas e criação de arrays que irão conter os nomes e cursos
	preencheArray(cursos, "cursos.txt");
	int tamanhoy = contaLinhas("cursos.txt");

	int sorting = 0;
	bool swap = true;
	string temp;
	int ajudasistema = 50;
	int functions;
	bool pessoaencontrada = false;
	int aremover;
	int emerg;
	int ganhostotais = 0;
	int contaS = 0;																//Declaração de variáveis
	int contaciclos=0;
	string entrada;
	string pratoprincip;
	float custo;
	int resposta;
	bool dadosgravados = false;

	Refeiçao* Atual = new Refeiçao;										//Refeição Atual
	Refeiçao* Gravada = new Refeiçao;									//Refeição gravada


	cout << "******************************* BEM VINDO À CANTINA EDA *******************************" << endl << endl;
	cout << "************************************ REFEIÇAO NOVA ************************************" << endl << endl;
	cout << "A cantina EDA necessita de uma nova refeição." << endl;
	cout << "   1.Introduza a entrada:" << endl;
	cin >> entrada;
	cout << "   2.Introduza o prato principal:" << endl;
	cin >> pratoprincip;
	cout << "   3.Introduza o custo:" << endl;
	cin >> custo;

	Atual->entrada = entrada;
	Atual->pratoprincipal = pratoprincip;								//Preenchimento da Refeição Atual tendo em conta os dados introduzidos pelo utilizador
	Atual->custo = custo;

	Entidade** entidadesRemovidas = new Entidade*[300];					//Apontador para um vetor de apontadores para Entidade que será utilizado para guardar as pessoas removidas sem plafond
	int num_ent_removidas=0;											//num_ent_removidas será incrementado a cada remoçõ e corresponde à nova posição onde será guardada a entidade no vetor de remoção

	int grupo;
	int elementosgrupo;
	int randomcargo;
	int randomciclos;
	int randomcourse;
	bool estatutoespecial;
	bool studentorstaff;
	string curso;

	int randomCantina = 30 + (std::rand() % (50 - 30 + 1));								//Tamanho aleatório da Cantina entre 30 e 50

	Mesa *gravaçãomesas = new Mesa[randomCantina];										//Apontador para um vetor de Mesas que irá guardar a informação realacionada com dados gravados
	Mesa *conjmesas = new Mesa[randomCantina];											//Apontador para um vetor de Mesas que constituem a cantina
	int lugaresdisponiveis = randomCantina;
	int v = 0;
	int numeromesa = 1;
	int numalunossentados = 0;
	int tamanhomesa;
	int vagasocupadas = 0;
	do{
		while (v <= randomCantina && lugaresdisponiveis > 0) {          //Enquanto houver cadeiras a colocar na cantina ele irá criar Mesas no vetor conjmesas
			tamanhomesa = 2 + (std::rand() % (5 - 2 + 1));				//Tamanho aleatório da mesa a criar
			if (tamanhomesa < lugaresdisponiveis) {
				tamanhomesa = tamanhomesa;								
			}
			else if (tamanhomesa > lugaresdisponiveis) {				//Se o tamanho ultrapassar a disponibilidade, então o tamanho passa a ser a própria disponibilidade de colocção de cadeiras na cantina
				tamanhomesa = lugaresdisponiveis;
			}
				criaMesa(tamanhomesa, numalunossentados, numeromesa, conjmesas, v);
				lugaresdisponiveis = lugaresdisponiveis - tamanhomesa;
				numeromesa++;
				v++;
		}break;
	} while (lugaresdisponiveis >=0);
	

	Entidade **gravaçaofila = new Entidade*[50];						//Apontador para um vetor de apontadores para Entidade que será utilizado para gravar dados
	Entidade **filadeespera = new Entidade*[50];						//Apontador para um vetor de apontadores para Entidade que será utilizado para criar a fila
	int j = 0;
	int i = 49;
	do {
		grupo = 100 + (std::rand() % (500 - 100 + 1));						
		elementosgrupo = 1 + (std::rand() % (10 - 1 + 1));
		randomcargo = 0 + (std::rand() % (2 - 0 + 1));								//Randoms
		randomciclos =2 + (std::rand() % (5 - 2 + 1));
		randomcourse = 0 + (std::rand() % ((tamanhoy - 1) - 0 + 1));
		curso = cursos[randomcourse];

		if (randomcargo > 0) {		
			studentorstaff = true;										//Definição de novas entidades como aluno ou staff
		}
		else if (randomcargo == 0) {
			studentorstaff = false;
		}
		while (j < elementosgrupo && i >= 0) {
			int randomestatuto = 1 + (std::rand() % (100 - 1 + 1));				//Random para estatuto de 1 a 100
			if (randomestatuto <= 5) {											//Se o valor obtido for menor ou igual a 5 então é estudante estatuto especial 
				estatutoespecial = true;										//(ou seja 5 de 100 números dá uma probabilidade de 5% como pedido)
			}
			else if (randomestatuto > 5) {
				estatutoespecial = false;										//Enquanto j for menor que o núemro de elementos constituintes do grupo e não ultrapassar a capacidade da fila, cria entidades
			}
				criaEntidade(primeirosnomes, ultimosnomes, curso, filadeespera, grupo,estatutoespecial, i, studentorstaff,randomciclos, elementosgrupo);
				j++;
				i--;
				}
			j = 0;
	} while (i >= 0);
	for (int x = 0; x <= 49; x++) {									//Percorre o vetor e verifica se alguém não tem plafond
		if (filadeespera[x]->plafond < Atual->custo) {
			cout << "**************************************** ATENÇÃO ****************************************" << endl;
			cout << "A entidade " << filadeespera[x]->prim_nome << " com número mecanográfico " << filadeespera[x]->num_mec << " grupo " << filadeespera[x]->num_grupo_dep << " não tem plafond suficiente." << endl;
			cout << "   1.Remover entidade da fila;" << endl;
			cout << "   2.Remover grupo/departamento da fila;" << endl;
			cin >> resposta;
			if (resposta == 1) {
				removeSemPlafond(filadeespera, entidadesRemovidas, x, num_ent_removidas);
				criaEntidade(primeirosnomes, ultimosnomes, curso, filadeespera, grupo, estatutoespecial, x, studentorstaff, randomciclos, 1);     //Remove a entidade sem Plafond e cria uma nova nessa posição
				num_ent_removidas++;
			}
			if (resposta == 2) {
				int z;
				int novoselementos = filadeespera[x]->numcosntgrupo;
				grupo = 100 + (std::rand() % (500 - 100 + 1));
				randomciclos = 2 + (std::rand() % (5 - 2 + 1));								//Remove todos os elementos do grupo. Depois da posição i(primeiro elemento do grupo encontrado)-(nº de elementos-1) irá popular com novos elementos
				randomcourse = 0 + (std::rand() % ((tamanhoy - 1) - 0 + 1));
				curso = cursos[randomcourse];
				for (z = procuraGrupo(filadeespera, filadeespera[x]->num_grupo_dep); z >= (procuraGrupo(filadeespera, filadeespera[x]->num_grupo_dep)- (filadeespera[x]->numcosntgrupo - 1)); z--) {
					removeSemPlafond(filadeespera, entidadesRemovidas, z, num_ent_removidas);
					criaEntidade(primeirosnomes, ultimosnomes, curso, filadeespera, grupo, estatutoespecial, z, studentorstaff, randomciclos,novoselementos);
					num_ent_removidas++;
				}
			}
		}
	}
	
	cout << endl << endl;
	cout << "ENTIDADES REMOVIDAS POR FALTA DE DINHEIRO:" << endl << endl;				//Pequena impressão na inicialização para comprovar o funcionamento da remoção
	for (int n = 0; n < num_ent_removidas; n++) {
		cout << entidadesRemovidas[n]->prim_nome << " " << entidadesRemovidas[n]->course << " " << entidadesRemovidas[n]->cargo << " grupo/departamento: " << entidadesRemovidas[n]->num_grupo_dep << " ciclos " << entidadesRemovidas[n]->ciclosrestantes << endl;
	}
	cout << endl << endl;
	Entidade **sistema = new Entidade*[50 + randomCantina];						//Vetores utilizado para ordenar por ordem alfabetica do ultimo nome os constituintes da cantina
	
	bool sair = false;
	char opcao;
	do
	{
		cout << "                                            Cantina EDA" << endl;
		cout << "(s)Seguinte   (e)Emergência   (g)Gravar   (c)Carregar Dados   (o)Opções   (0)Fechar Programa" << endl << endl;
		
		cout << "Refeição Actual:" << endl;
		cout << "      Entrada: " << Atual->entrada << endl;								//Impressão da Refeiçao
		cout << "      Prato: " << Atual->pratoprincipal << endl;
		cout << "      custo: " << Atual->custo << endl << endl;
		int interator1=0;
		int interator2 = 0;
		int interator3 = 0;
		while (interator1 < numeromesa-1) {
			cout << "MESA " << conjmesas[interator1].numdemesa << " (CAPACIDADE " << conjmesas[interator1].tamanho << "):" << endl;  
			if (conjmesas[interator1].lugaresocupados == 0) {																		//Impressão das mesas
				cout << "Não existem alunos sentados nesta mesa!" << endl << endl;
			}
			else if (conjmesas[interator1].lugaresocupados > 0) {
				while (interator2 < conjmesas[interator1].lugaresocupados) {
					cout << "      " << conjmesas[interator1].x[interator2]->prim_nome << ", " << conjmesas[interator1].x[interator2]->cargo << ", " << conjmesas[interator1].x[interator2]->course << ", Grupo " << conjmesas[interator1].x[interator2]->num_grupo_dep << ", " << conjmesas[interator1].x[interator2]->num_mec << " (ciclos restantes : " << conjmesas[interator1].x[interator2]->ciclosrestantes << ")" << endl;
					interator2++;
				}
				
			}
			cout << endl;
			interator1++;
			interator2 = 0;
		}
		
		cout << endl << endl;
		cout << "FILA DE ESPERA:" << endl;						//Impressão da fila (do último elemento para o primeiro a chegar, ou seja os ultimos elementos impressos foram os primeiros a chegar e primeiros a serem atendidos)
		while (interator3 <= 49) {
			if (filadeespera[interator3]->studentorstaff==true && filadeespera[interator3]->estatuto == false) {
				cout << filadeespera[interator3]->prim_nome << " " << filadeespera[interator3]->seg_nome << ", " << filadeespera[interator3]->cargo << ", Grupo: " << filadeespera[interator3]->num_grupo_dep << ", " << filadeespera[interator3]->num_mec << ", " << filadeespera[interator3]->course << ", Duração, " << filadeespera[interator3]->ciclosrestantes << ", Plafond: " << filadeespera[interator3]->plafond << "Euros" << endl;
			}
			if (filadeespera[interator3]->studentorstaff == false) {
				cout << filadeespera[interator3]->prim_nome << " " << filadeespera[interator3]->seg_nome << ", " << filadeespera[interator3]->cargo << ", Departamento: " << filadeespera[interator3]->num_grupo_dep << ", " << filadeespera[interator3]->num_mec << ", Duração, " << filadeespera[interator3]->ciclosrestantes << ", Plafond: " << filadeespera[interator3]->plafond <<"Euros" << endl;
			}
			else if (filadeespera[interator3]->studentorstaff == true && filadeespera[interator3]->estatuto == true) {
				cout << filadeespera[interator3]->prim_nome << " " << filadeespera[interator3]->seg_nome << ", " << filadeespera[interator3]->cargo << ", Grupo: Individual" << ", " << filadeespera[interator3]->num_mec << ", " << filadeespera[interator3]->course << ", Duração, " << filadeespera[interator3]->ciclosrestantes << ", Plafond: " << filadeespera[interator3]->plafond << "Euros" << endl;
			}
			interator3++;
		}
		cout << endl << endl;
		cout << "Dinheiro cobrado até ao momento pela Cantina EDA: " << ganhostotais << "Euros!!" << endl;     //Print de uma variável criada para provar que a cobrança dos alunos removidos
		cin >> opcao;																						   //tanto por emergência como por ciclos está a ocorrer
		cout << endl << endl;
		if (opcao == 's') {
			contaS++;                                   //ContaS começa a 0
		}

		switch (opcao) {
		case 's':
			if (contaS == 1) {							//ContaS=1 significa que se refere ao primeiro ciclo, então popula só as mesas com os alunos da fila
				populaMesas(filadeespera,conjmesas, numeromesa, randomCantina, vagasocupadas, grupo, elementosgrupo, randomcargo, randomciclos, randomcourse, curso, cursos, tamanhoy,primeirosnomes, ultimosnomes, studentorstaff, estatutoespecial);
				
			}
			else if (contaS > 1) {						//Caso se trate de ciclos posteriores (contaS >1) irá realizar as seguintes funções:

				for (int d = 0; d < numeromesa; d++) {
					for (int aux = 0; aux < conjmesas[d].tamanho; aux++) {
						conjmesas[d].x[aux]->ciclosrestantes = (conjmesas[d].x[aux]->ciclosrestantes) - 1;    //Decrementação de 1 valor nos ciclos restantes de cada aluno sentado
					}
					
				}

				for (int d = 0; d < numeromesa; d++) {
					for (int aux = 0; aux < conjmesas[d].tamanho; aux++) {
						if (conjmesas[d].x[aux]->ciclosrestantes == 0) {								//Verificação de pessoas com ciclos a 0, para essas Pessoas:
							conjmesas[d].x[aux]->plafond = conjmesas[d].x[aux]->plafond - Atual->custo; //É cobrado o custo atual no plafond
							ganhostotais = ganhostotais + Atual->custo;									//Ganhos totais aumentam no valor da refeição
							conjmesas[d].x[aux] = filadeespera[49];										//É sentado na nova vaga o próximo aluno a ser atendido na fila
							for (int y = 48; y >= 0; y--) {
								filadeespera[y + 1] = filadeespera[y];									//Andamos todas as posições da fila uma casa para a frente
								int l = 0;
								int m = 0;																//Cria-se uma pessoa no fim da fila nos lugares que forem desocupados
								do {
									grupo = 100 + (std::rand() % (500 - 100 + 1));
									elementosgrupo = 1 + (std::rand() % (10 - 1 + 1));
									randomcargo = 0 + (std::rand() % (2 - 0 + 1));
									randomciclos = 2 + (std::rand() % (5 - 2 + 1));
									randomcourse = 0 + (std::rand() % ((tamanhoy - 1) - 0 + 1));
									curso = cursos[randomcourse];

									if (randomcargo > 0) {
										studentorstaff = true;
									}
									else if (randomcargo == 0) {
										studentorstaff = false;
									}
									while (m < elementosgrupo && l < (49 - 48)) {
										int randomestatuto = 1 + (std::rand() % (100 - 1 + 1));
										if (randomestatuto <= 5) {
											estatutoespecial = true;
										}
										else if (randomestatuto > 5) {
											estatutoespecial = false;
										}
										criaEntidade(primeirosnomes, ultimosnomes, curso, filadeespera, grupo, estatutoespecial, l, studentorstaff, randomciclos, elementosgrupo);
										m++;
										l++;
									}
									m = 0;
								} while (l < (49 - 48));
							}
						}
					}

				}

		
				contaciclos++;																	//contaciclos é inicializado a 0, a cada 10 pede ao utilizador uma nova refeição
				if (contaciclos == 10) {
					cout << "A cantina EDA necessita de uma nova refeição." << endl;
					cout << "   1.Introduza a entrada:" << endl;
					cin >> entrada;
					cout << "   2.Introduza o prato principal:" << endl;
					cin >> pratoprincip;
					cout << "   3.Introduza o custo:" << endl;
					cin >> custo;

					Atual->entrada = entrada;
					Atual->pratoprincipal = pratoprincip;
					Atual->custo = custo;
					contaciclos=0;																//Chegando aos 10 temos que inicializar de novo o contaciclos a 0
				}
				
			}
			for (int x = 0; x <= 49; x++) {					//Nova verificação de entidades sem plafond, igual à feita anteriormente na inicialização
				if (filadeespera[x]->plafond < Atual->custo) {
					cout << "**************************************** ATENÇÃO ****************************************" << endl;
					cout << "A entidade " << filadeespera[x]->prim_nome << " com número mecanográfico " << filadeespera[x]->num_mec << " grupo " << filadeespera[x]->num_grupo_dep << " não tem plafond suficiente." << endl;
					cout << "   1.Remover entidade da fila;" << endl;
					cout << "   2.Remover grupo/departamento da fila;" << endl;
					cin >> resposta;
					if (resposta == 1) {
						removeSemPlafond(filadeespera, entidadesRemovidas, x, num_ent_removidas);
						criaEntidade(primeirosnomes, ultimosnomes, curso, filadeespera, grupo, estatutoespecial, x, studentorstaff, randomciclos, 1);
						num_ent_removidas++;
					}
					if (resposta == 2) {
						int z;
						int novoselementos = filadeespera[x]->numcosntgrupo;
						grupo = 100 + (std::rand() % (500 - 100 + 1));
						randomciclos = 2 + (std::rand() % (5 - 2 + 1));
						randomcourse = 0 + (std::rand() % ((tamanhoy - 1) - 0 + 1));
						curso = cursos[randomcourse];
						for (z = procuraGrupo(filadeespera, filadeespera[x]->num_grupo_dep); z >= (procuraGrupo(filadeespera, filadeespera[x]->num_grupo_dep) - (filadeespera[x]->numcosntgrupo - 1)); z--) {
							removeSemPlafond(filadeespera, entidadesRemovidas, z, num_ent_removidas);
							criaEntidade(primeirosnomes, ultimosnomes, curso, filadeespera, grupo, estatutoespecial, z, studentorstaff, randomciclos, novoselementos);
							num_ent_removidas++;
						}
					}
				}
			}
			break;
		case 'e':
			cout << "**************************************** EMERGÊNCIA ****************************************" << endl;   //Remoção de um utente ou grupo por emergência
			cout << "Situação de emergência:" << endl;
			cout << "   1.Remover entidade da cantina;" << endl;
			cout << "   2.Remover grupo/departamento da cantina;" << endl;
			cin >> emerg;
			cout << endl;
			if (emerg == 1) {
				cout << "Número mecanográfico da entidade:" << endl;
				cin >> aremover;
				for (int d = 0; d < numeromesa; d++) {
					for (int aux = 0; aux < conjmesas[d].tamanho; aux++) {
						if (conjmesas[d].x[aux]->num_mec == aremover) {
							pessoaencontrada = true;
							conjmesas[d].x[aux]->plafond = conjmesas[d].x[aux]->plafond - Atual->custo; //Procura, remove a pessoa, cobra o dinheiro e senta a proxima pessoa da fila no lugar
							ganhostotais = ganhostotais + Atual->custo;
							conjmesas[d].x[aux] = filadeespera[49];
							for (int y = 48; y >= 0; y--) {
								filadeespera[y + 1] = filadeespera[y];					//Anda a fila uma posição para frente
								int l = 0;
								int m = 0;
								do {
									grupo = 100 + (std::rand() % (500 - 100 + 1));
									elementosgrupo = 1 + (std::rand() % (10 - 1 + 1));
									randomcargo = 0 + (std::rand() % (2 - 0 + 1));
									randomciclos = 2 + (std::rand() % (5 - 2 + 1));
									randomcourse = 0 + (std::rand() % ((tamanhoy - 1) - 0 + 1));
									curso = cursos[randomcourse];

									if (randomcargo > 0) {
										studentorstaff = true;
									}
									else if (randomcargo == 0) {
										studentorstaff = false;
									}
									while (m < elementosgrupo && l < (49 - 48)) {
										int randomestatuto = 1 + (std::rand() % (100 - 1 + 1));      //Criação de uma nova entidade no lugar vago no fim da fila
										if (randomestatuto <= 5) {
											estatutoespecial = true;
										}
										else if (randomestatuto > 5) {
											estatutoespecial = false;
										}
										criaEntidade(primeirosnomes, ultimosnomes, curso, filadeespera, grupo, estatutoespecial, l, studentorstaff, randomciclos, elementosgrupo);
										m++;
										l++;
									}
									m = 0;
								} while (l < (49 - 48));
							}
						}
					}
				}
				if (pessoaencontrada == false) {
					cout << "Não existe de momento nenhuma entidade com número " << aremover << " a usufruir da cantina!" << endl << endl;
				}
				pessoaencontrada = false;
			}
			if (emerg == 2) {
				cout << "Grupo/Departamento da entidade:" << endl;
				cin >> aremover;
				for (int d = 0; d < numeromesa; d++) {
					for (int aux = 0; aux < conjmesas[d].tamanho; aux++) {
						if (conjmesas[d].x[aux]->num_grupo_dep == aremover) {
							pessoaencontrada = true;
							conjmesas[d].x[aux]->plafond = conjmesas[d].x[aux]->plafond - Atual->custo;
							ganhostotais = ganhostotais + Atual->custo;											//Procura, remove e cobra dinheiro a todas as pessoas do grupo a eliminar
							conjmesas[d].x[aux] = filadeespera[49];
							for (int y = 48; y >= 0; y--) {
								filadeespera[y + 1] = filadeespera[y];									//Anda a fila para a frente
								int l = 0;
								int m = 0;
								do {
									grupo = 100 + (std::rand() % (500 - 100 + 1));
									elementosgrupo = 1 + (std::rand() % (10 - 1 + 1));
									randomcargo = 0 + (std::rand() % (2 - 0 + 1));
									randomciclos = 2 + (std::rand() % (5 - 2 + 1));
									randomcourse = 0 + (std::rand() % ((tamanhoy - 1) - 0 + 1));
									curso = cursos[randomcourse];

									if (randomcargo > 0) {
										studentorstaff = true;											//Cria novos grupos para as novas posições livres no fim da fila
									}
									else if (randomcargo == 0) {
										studentorstaff = false;
									}
									while (m < elementosgrupo && l < (49 - 48)) {
										int randomestatuto = 1 + (std::rand() % (100 - 1 + 1));
										if (randomestatuto <= 5) {
											estatutoespecial = true;
										}
										else if (randomestatuto > 5) {
											estatutoespecial = false;
										}
										criaEntidade(primeirosnomes, ultimosnomes, curso, filadeespera, grupo, estatutoespecial, l, studentorstaff, randomciclos, elementosgrupo);
										m++;
										l++;
									}
									m = 0;
								} while (l < (49 - 48));
							}
						}
					}
				}
				if (pessoaencontrada == false) {
					cout << "Não existe de momento nenhum departamento/grupo " << aremover << " a usufruir da cantina!" << endl << endl;
				}
				pessoaencontrada = false;
			}
			
			break;
		case 'g':
			Gravada->custo = Atual->custo;
			Gravada->pratoprincipal = Atual->pratoprincipal;			//Basicamente copia para a refeição de gravação os dados da atual
			Gravada->entrada = Atual->entrada;									
			for (int b = 49; b >= 0; b--) {
				gravaçaofila[b] = filadeespera[b];
			}															//Copia cada posição dos vetores originais da fila e mesas para os de gravação
		
			for (int y = 0; y < numeromesa; y++)
				gravaçãomesas[y] = conjmesas[y];
			dadosgravados = true;
			break;
		case 'c':
			if (dadosgravados == false) {
				cout << "Não existem dados de cantina gravados!" << endl;					//Caso em que nada foi gravado
			}
			else if (dadosgravados == true) {
				Atual->custo = Gravada->custo;
				Atual->pratoprincipal = Gravada->pratoprincipal;						//Basicamente copia para a refeição atual os dados de gravação
				Atual->entrada = Gravada->entrada;
				for (int b = 49; b >= 0; b--) {
					filadeespera[b]=gravaçaofila[b];
				}
																						//Copia cada posição dos vetores gravação da fila e mesas para os originais
				for (int y = 0; y < numeromesa; y++)
					conjmesas[y]=gravaçãomesas[y];
			}
			break;
		case 'o':
			cout << "******************************* OPÇÕES *******************************" << endl << endl;
			cout << "   1.Visualizar todos os utentes da cantina;" << endl;
			cout << "   2.Visualizar todos os utentes ordenados alfabeticamente pelo sobrenome;" << endl;
			cout << "   3.Alterar Plafond de um utente que se encontre na Fila;" << endl;
			cin >> functions;
			if (functions == 1) {												//Impressão de todos os utentes da fila
				cout << "UTENTES NA FILA DE ESPERA:" << endl;
				for (int interator3 = 49; interator3 >= 0; interator3--) {
					if (filadeespera[interator3]->studentorstaff == true && filadeespera[interator3]->estatuto == false) {
						cout << "      " << filadeespera[interator3]->prim_nome << " " << filadeespera[interator3]->seg_nome << ", " << filadeespera[interator3]->cargo << ", Grupo: " << filadeespera[interator3]->num_grupo_dep << ", " << filadeespera[interator3]->course <<  ", Plafond: " << filadeespera[interator3]->plafond << "Euros." << endl;
					}
					if (filadeespera[interator3]->studentorstaff == false) {
						cout << "      " << filadeespera[interator3]->prim_nome << " " << filadeespera[interator3]->seg_nome << ", " << filadeespera[interator3]->cargo << ", Departamento: " << filadeespera[interator3]->num_grupo_dep <<  ", Plafond: " << filadeespera[interator3]->plafond << "Euros." << endl;
					}
					else if (filadeespera[interator3]->studentorstaff == true && filadeespera[interator3]->estatuto == true) {
						cout << "      " << filadeespera[interator3]->prim_nome << " " << filadeespera[interator3]->seg_nome << ", " << filadeespera[interator3]->cargo << ", Grupo: Individual" << ", " << filadeespera[interator3]->course <<  ", Plafond: " << filadeespera[interator3]->plafond << "Euros." << endl;
					}
				}
				cout << "UTENTES SENTADOS EM MESAS:" << endl;
				for (int interator1 = 0; interator1 < numeromesa;interator1++) {
					for (int interator2 = 0; interator2 < conjmesas[interator1].lugaresocupados;interator2++) {
								cout << "      " << conjmesas[interator1].x[interator2]->prim_nome << " " << conjmesas[interator1].x[interator2]->seg_nome << ", " <<conjmesas[interator1].x[interator2]->cargo << ", Grupo " << conjmesas[interator1].x[interator2]->num_grupo_dep << ", Plafond: " << conjmesas[interator1].x[interator2]->plafond << "Euros." << endl;

							}
				}
				cout << "UTENTES REJEITADOS POR FALTA DE PLAFOND:" << endl;
				for (int n = 0; n < num_ent_removidas; n++) {
					cout << "      " << entidadesRemovidas[n]->prim_nome << " " << entidadesRemovidas[n]->seg_nome << ", " << entidadesRemovidas[n]->cargo << ", grupo/departamento: " << entidadesRemovidas[n]->num_grupo_dep << ", Plafond: " << entidadesRemovidas[n]->plafond <<"Euros."<< endl;
				}
				cout << endl << endl;
			}
			if (functions == 2) {
				cout << "UTENTES ATUAIS DA CANTINA ORDENADOS ALFABETICAMENTE PELO SOBRENOME:" << endl;
				for (int i = 0; i < 50; i++) {
					sistema[i] = filadeespera[i];
				}
				while (ajudasistema < (50 + randomCantina)-1) {							//Primeiro guarda no vetor auxiliar todos os utentes na fila e sentados
					for (int x = 0; x < numeromesa; x++) {
						for (int aux = 0; aux < conjmesas[x].tamanho; aux++) {
							sistema[ajudasistema] = conjmesas[x].x[aux];
							ajudasistema++;
						}
					}
				}
				ajudasistema = 50;

				sorting = 0;
				swap = true;
				temp;
				while (swap)
				{
					swap = false;
					j++;
					for (int l = 0; l < (50 + randomCantina)-1; l++)
					{
						if (sistema[l]->seg_nome > sistema[l + 1]->seg_nome)
						{
							temp = sistema[l]->seg_nome;
							sistema[l]->seg_nome = sistema[l + 1]->seg_nome;			//É realizado um sort do vetor sistema
							sistema[l + 1]->seg_nome = temp;
							swap = true;
						}
					}
				}

				for (int printer = 0; printer < (50 + randomCantina)-1; printer++) {   //Imprime o vetor ordenado
					if (sistema[printer]->studentorstaff == true && sistema[printer]->estatuto == false) {
						cout << "      " << sistema[printer]->prim_nome << " " << sistema[printer]->seg_nome << ", "  << ", Grupo: " << sistema[printer]->num_grupo_dep << ", "<< sistema[printer]->course  << ", Plafond: " << sistema[printer]->plafond << "Euros" << endl;
					}
					if (sistema[printer]->studentorstaff == false) {
						cout << "      " << sistema[printer]->prim_nome << " " << sistema[printer]->seg_nome << ", "  << ", Departamento: " << sistema[printer]->num_grupo_dep << ", Plafond: " << sistema[printer]->plafond << "Euros" << endl;
					}
					else if (sistema[printer]->studentorstaff == true && sistema[printer]->estatuto == true) {
						cout << "      "<< sistema[printer]->prim_nome << " " << sistema[printer]->seg_nome << ", " << ", Grupo: Individual" <<  ", " << sistema[printer]->course << ", Plafond: " << sistema[printer]->plafond << "Euros" << endl;
					}
				}
			}
			if (functions == 3) {
				cout << "***************************** Alterar Plafond de Utente *****************************" << endl;
				cout << "Indique o número mecanográfico da entidade em questão:" << endl;
				cout << "Número mecanográfico da entidade:" << endl;
				cin >> aremover;
				for (int d = 0; d <= 49; d++) {
					if (filadeespera[d]->num_mec == aremover) {
						float novoplafond;												//Procura na fila a pessoa com número indicado pelo utilizador
						pessoaencontrada = true;
						cout << "Insira o novo Plafond:" << endl;
						cin >> novoplafond;
						filadeespera[d]->plafond = novoplafond;							//Altera Plafond
					}
					if (pessoaencontrada = false) {
						cout << "Não existe entidade com este número mecanográfico!" << endl;			//Se não existir o número em questão
					}
					pessoaencontrada = false;
				}
			}
				if (functions > 3) {
					cout << "Escolha uma opcao valida." << endl << endl;
				}
			break;

		case '0':
			cout << "Escolheu a opção Sair!" << endl << endl;
			sair = true;
			break;
		default:
			cout << "Escolha uma opcao valida." << endl << endl;
			break;
		}
	} while (!sair);

	system("PAUSE");
	cin.sync();
	cin.get();
	return 0;
}

	

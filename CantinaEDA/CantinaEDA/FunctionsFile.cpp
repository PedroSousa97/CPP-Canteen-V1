#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include "Entidade.h"
#include "Mesa.h"
#include "Refeiçao.h"
using namespace std;

int contaLinhas(string nomeFicheiro) {

	fstream myFile;
	string line;
	int conta = 0;
	myFile.open(nomeFicheiro, ios::in);						//Função que abre um fecheiro de texto e retorna a quantidade de linhas que foram lidas
	if (myFile.is_open()) {
		while (getline(myFile, line)) {
			conta++;

		}
	}
	myFile.close();
	return conta;
}

void preencheArray(string * vectorGuarda, string nomeFicheiro) {
	fstream myFile;
	string line;
	int conta = 0;
	myFile.open(nomeFicheiro, ios::in);
	if (myFile.is_open()) {
		while (getline(myFile, line)) {					//Função que a cada linha de texto do ficheiro irá corresponder a uma posição de memória de um dado vetor
			vectorGuarda[conta] = line;
			conta++;
		}
	}
	myFile.close();
}


void criaEntidade(string *v, string *z, string curso, Entidade **x, int grupo, bool estatutoespecial, int i,bool studentorstaff,int ciclos,int numconstgrup) {
	int tamanhov = contaLinhas("primeiro_nome.txt");
	int tamanhoz = contaLinhas("ultimo_nome.txt");								//Inteiros utilizados para criar os randoms de 0 até ao tamanho do vetor que guarda as informações relativas aos momes e cursos
	int tamanhoy = contaLinhas("cursos.txt");
	int randomfirstname = 0 + (std::rand() % ((tamanhov - 1) - 0 + 1));
	int randomsecondname = 0 + (std::rand() % ((tamanhoz - 1) - 0 + 1));		//Randoms própriamente ditos entre 0 e tamanho do vetor que nos dará nomes e cursos aleatórios
	int randomcourse = 0 + (std::rand() % ((tamanhoy - 1) - 0 + 1));
	int randomcargo = 0 + (std::rand() % (2 - 0 + 1));
	
	if (studentorstaff == true) {												//Se for aluno, que não seja de estatuto especial, a entidade será criada desta forma:
		Entidade *aluno = new Entidade;
		aluno->studentorstaff = true;
		aluno->estatuto = false;
		aluno->numcosntgrupo = numconstgrup;
		aluno->ciclosrestantes = ciclos;
		aluno->cargo = "Aluno";
		aluno->prim_nome = v[randomfirstname];
		aluno->seg_nome = z[randomsecondname];
		aluno->num_mec = 10000 + (std::rand() % (99999 - 10000 + 1));
		aluno->num_grupo_dep = grupo;
		aluno->course = curso;
		aluno->plafond = 1 + (std::rand() % (1 - 100 + 1));
		x[i] = aluno;
	} if (studentorstaff == false) {											//Se for staff, a entidade será criada desta forma:
		Entidade *staff = new Entidade;
		staff->studentorstaff = false;
		staff->estatuto = false;
		staff->numcosntgrupo = numconstgrup;
		staff->ciclosrestantes = ciclos;
		staff->cargo = "Staff";
		staff->prim_nome = v[randomfirstname];
		staff->seg_nome = z[randomsecondname];
		staff->num_mec = 10000 + (std::rand() % (99999 - 10000 + 1));
		staff->num_grupo_dep = grupo;
		staff->plafond = 1 + (std::rand() % (100 - 1 + 1));
		x[i] = staff;	
	}if (studentorstaff == true && estatutoespecial == true) {					//Se for aluno, que seja de estatuto especial, a entidade será criada desta forma:
		Entidade *especial = new Entidade;
		especial->estatuto = true;
		especial->studentorstaff = true;
		especial->numcosntgrupo = 1;
		especial->ciclosrestantes = ciclos;
		especial->cargo = "Aluno Estatuto Especial";
		especial->prim_nome = v[randomfirstname];
		especial->seg_nome = z[randomsecondname];
		especial->num_mec = 10000 + (std::rand() % (99999 - 10000 + 1));
		especial->course = curso;
		especial->num_grupo_dep = 0;
		especial->plafond = 1 + (std::rand() % (1 - 100 + 1));
		x[i] = especial;
	}
}

void criaMesa(int tamanho, int lugaresoc, int nummesa, Mesa *v, int i) {				//Função simples para criação das mesas
	Mesa *mesa = new Mesa;
	mesa->tamanho = tamanho;
	mesa->lugaresocupados = lugaresoc;
	mesa->numdemesa = nummesa;
	mesa->x = new Entidade*[tamanho];
	v[i] = *mesa;
	
}


int procuraGrupo(Entidade** x, int grupo) {
	int i = 49;
	while (i >= 0 && x[i]->num_grupo_dep!=grupo) {								//Dado um apontador para um vetor de apontadores para entidade, esta função procura e retorna a posição do primeiro elemento do grupo que procuramos
		i--;
	}
	return i;
}

int contaElementosGrupo(Entidade**x, int grupo) {
	int contador = 0;
	for (int i = 49; i >= 0; i--) {												//Dado um número de grupo este conta e retorna quantos elementos desse grupo tem na fila
		if (grupo == x[i]->num_grupo_dep) {
			contador++;
		}
	}
	return contador;
}

void removeSemPlafond(Entidade **x, Entidade** remoçao, int i, int j) {				//Função que basicamente copia um elemento de um dado vetor para outro tendo em conta as posições i e j desejadas
		remoçao[j] = x[i];																
}


void populaMesas(Entidade **x, Mesa*y, int numerodemesas, int capacidade, int lugaresocupados, int grupo, int elementosgrupo, int randomcargo, int randomciclos, int randomcourse, string curso, string * cursos, int tamanhoy, string * primeirosnomes, string * ultimosnomes, bool studentorstaff, bool estatutoespecial) {
	int i = 0;
	int k;
	int aux;
	int n = 49;
	while (lugaresocupados < capacidade) {								//Enquanto houverem lugares livres na cantina, o programa irá colocar novos alunos nessas cadeiras
		for (i = 0; i < numerodemesas; i++) {
			if (y[i].lugaresocupados == 0) {							//Se a mesa estiver vazia, então não existem restrições e enquanto houver luagres vagos irá colocar novos alunos nas cadeiras da mesa
				for (aux = 0; aux < y[i].tamanho; aux++) {
					y[i].x[aux] = x[n];
					y[i].lugaresocupados = y[i].lugaresocupados + 1;
					n--;
					lugaresocupados++;				//incrementação dos lugares ocupados (da totalidade de lugares existentes na cantina), ou seja diminuição das vagas por ocupar
				}
			}
			else if (y[i].lugaresocupados > 0) {			//Se já tiver alunos sentados
				if (x[n]->studentorstaff == true) {											//Se o próximo a ser atendido na fila for aluno:
					if (y[i].x[0]->course == x[n]->course) {								//Verifica se o curso sentado na mesa é o mesmo, se for senta os alunos na mesa
						for (aux = y[i].lugaresocupados; aux < y[i].tamanho; aux++) {
							y[i].x[aux] = x[n];
							y[i].lugaresocupados = y[i].lugaresocupados + 1;
							n--;
							lugaresocupados++;
						}
					}
					else if (y[i].x[0]->course != x[n]->course) {							//Caso não sejam do mesmo curso, sentam-se na mesa seguinte
						for (aux = y[i + 1].lugaresocupados; aux < y[i + 1].tamanho; aux++) {
							y[i + 1].x[aux] = x[n];
							y[i + 1].lugaresocupados = y[i + 1].lugaresocupados + 1;
							n--;
							lugaresocupados++;
						}
					}
				}
				if (x[n]->studentorstaff == false) {							//Se for staff faz exatamente a mesma função
					if (y[i].x[0]->num_grupo_dep == x[n]->num_grupo_dep) {		//Desta vez a restrição é o número de departamento e não o curso da entidade
						for (aux = y[i].lugaresocupados; aux < y[i].tamanho; aux++) { 
							y[i].x[aux] = x[n];
							y[i].lugaresocupados = y[i].lugaresocupados + 1;
							n--;
							lugaresocupados++;
						}
					}
					else if (y[i].x[0]->num_grupo_dep != x[n]->num_grupo_dep) {
						for (aux = y[i + 1].lugaresocupados; aux < y[i + 1].tamanho; aux++) {
							y[i + 1].x[aux] = x[n];
							y[i + 1].lugaresocupados = y[i + 1].lugaresocupados + 1;
							n--;
							lugaresocupados++;
						}
					}
				}
			}
		}
	}
	for ( k = n; k >= 0; k--) {						//K= n(número de alunos que foram sentados em mesas)
		x[k + (49-n)] = x[k];						//Anda todas as posições do vetor n posições para a frente, ou seja faz com que a fila se mova e elimine os alunos que já se sentaram
	}
	int l = 0;
	int m = 0;
	do {															//De 0 a n irá criar novos alunos para ocupar os lugares que ficaram vagos no fim da fila
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
		while (m < elementosgrupo && l < (49-n)) {
			int randomestatuto = 1 + (std::rand() % (100 - 1 + 1));
			if (randomestatuto <= 5) {
				estatutoespecial = true;
			}
			else if (randomestatuto > 5) {
				estatutoespecial = false;
			}
			criaEntidade(primeirosnomes, ultimosnomes, curso, x, grupo, estatutoespecial, l, studentorstaff, randomciclos, elementosgrupo);
			m++;
			l++;
		}
		m = 0;
	} while (l < (49-n));
}


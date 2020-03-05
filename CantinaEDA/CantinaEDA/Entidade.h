#pragma once
#ifndef ENTIDADE_H
#define ENTIDADE_H
#include <string>
using namespace std;

struct Entidade {
	bool studentorstaff;				//Booleano que caracteriza o usuário da cantina como aluno ou staff
	bool estatuto;						//Booleano que caracteriza se o aluno é ou não aluno de estatuto especial
	int numcosntgrupo;					//Número de elementos constituintes do grupo a que a pessoa pertence
	int ciclosrestantes;				//Tempo de duração da refeição
	string cargo;						//Guarda a informação relativa ao cargo da entidade (aluno/staff)
	string prim_nome;					//Primeiro Nome
	string seg_nome;					//Último nome
	long num_mec;						//Número mecanográfico
	int num_grupo_dep;					//Número do grupo/Departamento
	string course;						//Curso
	float plafond;						//Capacidade monetária da pessoa em questão
};

#endif 
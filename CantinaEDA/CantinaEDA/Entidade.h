#pragma once
#ifndef ENTIDADE_H
#define ENTIDADE_H
#include <string>
using namespace std;

struct Entidade {
	bool studentorstaff;				//Booleano que caracteriza o usu�rio da cantina como aluno ou staff
	bool estatuto;						//Booleano que caracteriza se o aluno � ou n�o aluno de estatuto especial
	int numcosntgrupo;					//N�mero de elementos constituintes do grupo a que a pessoa pertence
	int ciclosrestantes;				//Tempo de dura��o da refei��o
	string cargo;						//Guarda a informa��o relativa ao cargo da entidade (aluno/staff)
	string prim_nome;					//Primeiro Nome
	string seg_nome;					//�ltimo nome
	long num_mec;						//N�mero mecanogr�fico
	int num_grupo_dep;					//N�mero do grupo/Departamento
	string course;						//Curso
	float plafond;						//Capacidade monet�ria da pessoa em quest�o
};

#endif 
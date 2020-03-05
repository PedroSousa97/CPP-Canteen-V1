#pragma once
#ifndef MESA_H
#define MESA_H
#include <string>
using namespace std;

struct Mesa {
	int tamanho;					//Tamanho da mesa
	int lugaresocupados;			//Lugares ocupados por alunos/staff sentado na mesa
	int numdemesa;					//Número da mesa
	Entidade** x;					//Apontador para um futuro vetor de apontadores para Entidade
};


#endif 
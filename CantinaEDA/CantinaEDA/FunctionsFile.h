#pragma once
#ifndef FUNCITONFILE_H
#define FUNCTIONFILE_H
#include <string>
#include "Entidade.h"
#include "Mesa.h"
#include "Refeiçao.h"
using namespace std;

int contaLinhas(string nomeFicheiro);
void preencheArray(string * vectorGuarda, string nomeFicheiro);
void criaEntidade(string *v, string *z, string curso, Entidade **x, int grupo, bool estatutoespecial, int i, bool studentorstaff,int ciclos, int numconstgrup);
void criaMesa(int tamanho, int lugaresoc, int nummesa, Mesa *v, int i);
void removeSemPlafond(Entidade **x, Entidade** remoçao, int i, int j);
int procuraGrupo(Entidade** x, int grupo);
int contaElementosGrupo(Entidade**x, int grupo);
void populaMesas(Entidade **x, Mesa*y, int numerodemesas, int capacidade, int lugaresocupados, int grupo, int elementosgrupo, int randomcargo, int randomciclos, int randomcourse, string curso, string * cursos, int tamanhoy, string * primeirosnomes, string * ultimosnomes, bool studentorstaff, bool estatutoespecial);


#endif 
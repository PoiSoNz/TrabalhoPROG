#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <fstream>
#include "Cliente.h"
#include "Data.h"
#include "Produto.h"
#include "Vende++.h"

#include "defs.h"

using namespace std;


void clearScreen();

unsigned short int leUnsignedShortInt(unsigned short int min, unsigned short int max);

int leInteiro(int min, int max);

void checkFile(ifstream &stream, string nomeFicheiro);

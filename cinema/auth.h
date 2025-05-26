#pragma once
#include <iostream>
#include <string>
using namespace std;

extern string cashierUser[4];
extern string cashierPass[4];

void loadCashiersFromFile(const char* filename);
bool login(bool &admin);

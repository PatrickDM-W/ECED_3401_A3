#pragma once
/****************************************
Sept 26, 2022
Patrick Wain

ArcticSea-IceLoss.h
Header file containing common files and definitions
****************************************/

#pragma once

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>

#define BYTES_PER_EL 1
#define MAX_IN_REC 65

extern int check_region(char* search, char* area, int s1, int s2, int a2, int i, int j);
extern void copyto(char* inrec, char* destination, int row, int row_size);
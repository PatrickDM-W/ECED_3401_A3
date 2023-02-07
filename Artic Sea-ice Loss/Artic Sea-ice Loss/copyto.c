/****************************************
Sept 26, 2022
Patrick Wain

Check_Region.c
Contains function to copy record to
search and area arrays

Given:
inrecord, destination array, index location
****************************************/

#include "ArcticSea-IceLoss.h"

void copyto(char* inrec, char* destination, int row, int row_size) 
{
	int d_offset;
	char* d_ptr;

	for(int i = 0; i < row_size; i++)
	{
		d_offset = (row * row_size * BYTES_PER_EL) + (i * BYTES_PER_EL);
		d_ptr = destination + d_offset;

		*d_ptr = inrec[i];
	}
}
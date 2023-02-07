/****************************************
Sept 26, 2022
Patrick Wain

ArctucSea-IceLoss.c
Main program containing entry point
****************************************/

#include "ArcticSea-IceLoss.h"

FILE* infile;
char inrec[MAX_IN_REC];
int pos_search;

int main(int argc, char* argv[])
{
	/*
	- open file in argv[1], reads and checks sentences
	- at EOF, stop reading and close
	- if only one argument (.exe name), stop executing
	*/

	/* check number of arguments */
	if (argc == 1)
	{
		printf("Missing file name\n");
		getchar();
		return -1;
	}

	/* argc >= 1, attempt to open file */
	if (fopen_s(&infile, argv[1], "r") != 0)
	{
		printf("Error opening file >%s< - possibly missing\n", argv[1]);
		getchar();
		return -1;
	}

	/* search and area parameters */
	int s1, s2;
	int a1, a2;
	char* search;
	char* area;

	a1 = 1;
	a2 = 1;

	/* File exists and is open, now read and count chars in each record */
	/* First read, get values */
	fscanf_s(infile, "%d %d", &s1, &s2);

	while ((s1 != 0) && (s2 != 0) && (a1 != 0) && (a2 != 0))
	{
		/* allocate memory for search image */
		search = (char*)malloc(s1 * s2);

		fgetc(infile);		//clear \n

		for (int i = 0; i < s1; i++)	// image builder
		{
			/* copy specified number of lines */
			fgets(inrec, MAX_IN_REC, infile);
			copyto(inrec, search, i, s2);	//build function to copy to passed array, in this case image array
		}

		/* get area parameters */
		fscanf_s(infile, "%d %d", &a1, &a2);

		/* allocate memory for area */
		area = (char*)malloc(a1 * a2);

		/* clear \n */
		fgetc(infile);

		for (int i = 0; i < a1; i++)	// area builder
		{
			fgets(inrec, MAX_IN_REC, infile);
			copyto(inrec, area, i, a2);	//area array
		}

		/* reset pos_search */
		pos_search = 0;

		/* search and area now built, begin checking */
		/* this section checks the entire area */
		for (int strt_i = 0; strt_i <= (a1 - s1); strt_i++)
		{
			for (int strt_j = 0; strt_j <= (a2 - s2); strt_j++)
			{
				pos_search = pos_search + check_region(search, area, s1, s2, a2, strt_i, strt_j);	// function to check regions
			}
		}

		/* print results */
		printf("\n%d", pos_search);

		/* free memory */
		free(search);
		free(area);

		/* get next search parameters */
		fscanf_s(infile, "%d %d", &s1, &s2);
	}

	/* quit conditions, error messages */
	if (s1 == 0)
	{
		if (s2 == 0)
		{
			printf("\nProgram complete, waiting to quit");

			getchar();

			return 0;
		}
		else
		{
			printf("\nProgram incomplete, missing search parameter (%d, %d)", s1, s2);
			printf("\n0 is not a valid search parameter!");
			printf("\nwaiting to quit");

			getchar();
			return 1;
		}
	}
	else if (s2 == 0)
	{
		printf("\nProgram incomplete, missing search parameter (%d, %d)", s1, s2);
		printf("\n0 is not a valid search parameter!");
		printf("\nwaiting to quit");

		getchar();
		return 1;
	}
	else
	{
		printf("\nProgram incomplete, missing area parameter (%d, %d)", a1, a2);
		printf("\n0 is not a valid area parameter!");
		printf("\nwaiting to quit");

		getchar();
		return 1;
	}
}
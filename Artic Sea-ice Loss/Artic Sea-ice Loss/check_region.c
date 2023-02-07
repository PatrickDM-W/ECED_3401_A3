/****************************************
Sept 26, 2022
Patrick Wain

Check_Region.c
Contains function to check ice regions

Given:
Image array, Area array, image size, area width
start location x, start location y
****************************************/

#include "ArcticSea-IceLoss.h"

int check_region(char* search, char* area, int s1, int s2, int a2, int row_corn, int col_corn)
{
	char* s_ptr;
	char* a_ptr;
	int s_offset, a_offset;
	int index_row, index_col;

	index_row = 0;
	index_col = 0;

	/* area pointer points at top left corner of passed area */
	/* search pointer points to first element */
	s_offset = 0;
	a_offset = (row_corn * a2 * BYTES_PER_EL) + (col_corn * BYTES_PER_EL);

	s_ptr = search + s_offset;
	a_ptr = area + a_offset;

	while ((index_row < s1) && ((*s_ptr == '#' && *a_ptr == '#') || (*s_ptr == '.' && (*a_ptr == '#' || *a_ptr == '.'))))
	{
		index_col = 0;
		while ((index_col < s2) && ((*s_ptr == '#' && *a_ptr == '#') || (*s_ptr == '.' && (*a_ptr == '#' || *a_ptr == '.'))))
		{
			/* change pointers */
			s_offset = (index_row * s2 * BYTES_PER_EL) + (index_col * BYTES_PER_EL);
			a_offset = ((index_row + row_corn) * a2 * BYTES_PER_EL) + ((index_col + col_corn) * BYTES_PER_EL);

			s_ptr = search + s_offset;
			a_ptr = area + a_offset;

			index_col++;
		}

		index_row++;
	}

	/* matching complete, either unrecognized character, matching search, or unmatching*/
	if ((*s_ptr != '#') && (*s_ptr != '.'))
	{
		printf("\nUnrecognized character in search image");
	}

	if ((*a_ptr != '#') && (*a_ptr != '.'))
	{
		printf("\nUnrecognized character in area image");
	}

	/* match found */
	if (*s_ptr == '#' && *a_ptr == '#')
	{
		return 1;
	}
	else if(*s_ptr == '.' && (*a_ptr == '.' || *a_ptr == '#'))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
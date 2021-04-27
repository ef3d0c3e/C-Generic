/* C-Generic, generics in C
	Copyright (C) 2021  ef3d0c3e

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>. */

#include <stdio.h>

#define LIST_TYPE int // How the type is displayed
#define LIST_TYPE_T int // the type
#include "list.h"

#define LIST_TYPE string
#define LIST_TYPE_T const char*
#include "list.h"

void print_i(size_t pos, int val)
{
	printf("%d: %d\n", pos, val);
}

void print_s(size_t pos, const char* val)
{
	printf("%s ", val);
}

int main()
{
	List_int li;
	List_construct_int(&li, 0);
	List_insert_int(&li, 2);
	List_insert_int(&li, 3);
	List_insert_int(&li, 5);
	List_insert_int(&li, 7);
	List_insert_int(&li, 11);

	List_delete_int(&li, 2);

	List_exec_int(&li, print_i);

	List_destruct_int(&li);

	List_string ls;
	List_construct_string(&ls, "This");
	List_insert_string(&ls, "list");
	List_insert_string(&ls, "contains");
	List_insert_string(&ls, "strings!");

	List_exec_string(&ls, print_s);

	List_destruct_string(&ls);

	return 0;
}

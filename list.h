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

#ifndef LIST_TYPE
#error "LIST_TYPE is not defined"
#endif

#ifndef LIST_TYPE_T
#error "LIST_TYPE_T is not defined"
#endif

#include <stdlib.h>

#define _LIST CONCAT(List_, LIST_TYPE)
#define _NODE CONCAT(List_Node_, LIST_TYPE)
#define __CONCAT(x, y) x ## y
#define CONCAT(x, y) __CONCAT(x, y)

struct _NODE
{
	LIST_TYPE_T val;
	struct _NODE* next;
};
typedef struct _NODE _NODE;

struct _LIST
{
	struct _NODE* head;
	struct _NODE* tail;
};
typedef struct _LIST _LIST;

// Create a list
void CONCAT(List_construct_, LIST_TYPE)(_LIST* l, LIST_TYPE_T initial_value)
{
	l->head = malloc(sizeof(_NODE));
	l->head->val = initial_value;
	l->head->next = NULL;

	l->tail = l->head;
}

// Destroy a list
void CONCAT(List_destruct_, LIST_TYPE)(_LIST* l)
{
	_NODE* node = l->head->next;
	while (node != NULL)
	{
		_NODE* prevNode = node;
		node = node->next;
		free(prevNode);
	}
	free(l->head);
}

// Insert an element at the end
void CONCAT(List_insert_, LIST_TYPE)(_LIST* l, LIST_TYPE_T value)
{
	_NODE* node = malloc(sizeof(_NODE));
	node->val = value;
	node->next = NULL;

	l->tail->next = node;
	l->tail = node;
}

// Get an element at any given position
_NODE* CONCAT(List_get_, LIST_TYPE)(_LIST* l, size_t idx)
{
	size_t i = 0;
	_NODE* node = l->head;
	while (node != NULL)
	{
		if (i == idx)
			return node;
		node = node->next;
		++i;
	}

	return NULL;
}

// Find the first element with `value`
_NODE* CONCAT(List_find_, LIST_TYPE)(_LIST* l, LIST_TYPE_T value)
{
	_NODE* node = l->head;
	while (node != NULL)
	{
		if (node->val == value)
			return node;
		node = node->next;
	}

	return NULL;
}

// Remove an element
_NODE* CONCAT(List_remove_, LIST_TYPE)(_LIST* l, size_t idx)
{
	size_t i = 0;
	_NODE* node = l->head;
	_NODE* prev = l->head;
	while (node != NULL)
	{
		if (i == idx)
			break;
		prev = node;
		node = node->next;
		++i;
	}
	if (node == NULL)
		return NULL;

	prev->next = node->next;

	return node;
}

// Delete an element
void CONCAT(List_delete_, LIST_TYPE)(_LIST* l, size_t idx)
{
	size_t i = 0;
	_NODE* node = l->head;
	_NODE* prev = l->head;
	while (node != NULL)
	{
		if (i == idx)
			break;
		prev = node;
		node = node->next;
		++i;
	}
	if (node == NULL)
		return;

	prev->next = node->next;

	free(node);
}

// Execute a callback on the list
void CONCAT(List_exec_, LIST_TYPE)(_LIST* l, void(*callback)(size_t, LIST_TYPE_T))
{
	size_t i = 0;
	_NODE* node = l->head;	
	while (node != NULL)
	{
		callback(i, node->val);
		node = node->next;
		++i;
	}
}

#undef _NODE
#undef _LIST
#undef CONCAT
#undef __CONCAT
#undef LIST_TYPE_T
#undef LIST_TYPE

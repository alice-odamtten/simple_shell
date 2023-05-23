#include "main.h"

/**
 * insert_at_end - add node at the end of a linked list
 * @head: head node
 * @str: the string to insert
 * @sub_data: data
 */

void insert_at_end(l_node **head, char *str, char *sub_data)
{
	l_node *temp, *new_node, *prev;

	if (!str)
	{
		return;
	}

	new_node = malloc(sizeof(l_node));
	if (!new_node)
	{
		free(new_node);
		return;
	}
	new_node->data = _strdup(str);
	new_node->sub_data = sub_data ? _strdup(sub_data) : "\'\'";
	new_node->next = NULL;

	if (!new_node->data)
	{
		free(new_node);
		return;
	}

	temp = *head;
	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		while (temp != NULL)
		{
			prev = temp;
			temp = temp->next;
		}

		temp = new_node;
		prev->next = temp;
	}
}


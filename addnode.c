#include "main.h"

/**
 * insert_at_end - add node at the end of a linked list
 * @head: head node
 * @str: the string to insert
 * @sub_data: data
 */

void insert_at_end(l_node **head, char *str, char *sub_data)
{
	l_node *temp, *new, *prev;

	if (!str)
	{
		return;
	}

	new = malloc(sizeof(l_node));
	if (!new)
	{
		free(new);
		return;
	}
	new->data = _strdup(str);
	new->sub_data = sub_data ? _strdup(sub_data) : "\'\'";
	new->next = NULL;

	if (!new->data)
	{
		free(new);
		return;
	}

	temp = *head;
	if (*head == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp != NULL)
		{
			prev = temp;
			temp = temp->next;
		}

		temp = new;
		prev->next = temp;
	}
}

/**
 * _insertatbegin - add node t the begining
 * @head: head node
 * Return: Always a struct
 */
struct node *_insertatbegin(struct node *head)
{
	struct node *new;

	/*
	 * new = (struct node *)malloc(sizeof(struct node));
	 * printf("Enter data:");
	 * scanf("%d", &new->data);
	 */

	new->next = head;
	head = new;
	return (head);
}

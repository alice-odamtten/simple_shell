#include "main.h"

/**
 * getlength - find length of linked list
 * @key: head of linked list
 * Return: Always an int
 */

int getlength(struct node  *key)
{
	int count = 0;
	struct node *pointertemp;

	pointertemp = key;
	while (pointertemp != NULL)
	{
		count++;
		pointertemp = pointertemp->next;
	}
	return (count);
}

/**
 * print_list - print linked list
 * @head: head node
 */

void print_list(l_node *head)
{
	l_node *ptr = head;

	if (head == NULL)
		return;

	while (ptr != NULL)
	{
		_puts(ptr->data);
		ptr = ptr->next;
	}
}

/**
 * _posprint - get node at aparticular index
 * @head: head node
 * @pos: position of node you want
 */

void _posprint(struct node *head, int pos)
{
	int i = 1;
	struct node *temp;

	temp = head;
	while (i < pos)
	{
		temp = temp->next;
		i++;
	}
	/*printf("node of position %d is :%d\n", pos, temp->data);*/
}

/**
 * _delete - delete node at an index
 * @head: head node
 * @pos: position you want to delete
 * Return: Always a node
 */

struct node *_delete(struct node *head, int pos)
{
	struct node *temp, *new;
	int i = 1;

	temp = head;
	while (i < pos - 1)
	{
		temp = temp->next;
		i++;
	}
	new = temp->next;
	temp->next = new->next;
	free(new);
	return (temp);
}

/**
 * freeList - frees linked list
 * @head: head node
 */
void freeList(l_node **head)
{
	l_node *current = *head;
	l_node *next;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}

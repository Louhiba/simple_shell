#include "header.h"

/**
 * an_so_l - add node to the start of a list
 * @head: addr of pointer to the head node
 * @str: str field of the node
 * @num: node index used by the history
 *
 * Return: the size of the list
 */
lstt *an_so_l(lstt **head, const char *str, int num)
{
	lstt *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(lstt));
	if (!new_head)
		return (NULL);
	fmwcb((void *)new_head, 0, sizeof(lstt));
	new_head->num = num;
	if (str)
	{
		new_head->str = dupl_str(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * an_endo_l - add a node to the end of a list
 * @head: addr of pointer to the head node
 * @str: the str field of the node
 * @num: node index used by the history
 *
 * Return: the size of the list
 */
lstt *an_endo_l(lstt **head, const char *str, int num)
{
	lstt *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(lstt));
	if (!new_node)
		return (NULL);
	fmwcb((void *)new_node, 0, sizeof(lstt));
	new_node->num = num;
	if (str)
	{
		new_node->str = dupl_str(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * p_ostr_ll - print only str element of the lstt linked list
 * @h: the pointer to the first node
 *
 * Return: the size of the list
 */
size_t p_ostr_ll(const lstt *h)
{
	size_t i = 0;

	while (h)
	{
		p_inp_str(h->str ? h->str : "(nil)");
		p_inp_str("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * del_n_i - delete the node at given index
 * @head: addr of pointer to the first node
 * @index: the index of the node to delete
 *
 * Return: 1 success, or 0
 */
int del_n_i(lstt **head, unsigned int index)
{
	lstt *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * f_lst - clear all the nodes of a list
 * @head_ptr: addr of the pointer to the head node
 *
 * Return: void func
 */
void f_lst(lstt **head_ptr)
{
	lstt *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

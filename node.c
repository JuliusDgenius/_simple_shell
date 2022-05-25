#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "shell.h"
#include "parser.h"
#include "node.h"

/**
 * new_node - creates a new node and sets it's type field
 * @type: type to be created
 *
 * Return: returns new node
 */
struct node_s *new_node(enum node_type_e type)
{
	struct node_s *node = malloc(sizeof(struct node_s));

	if (!node)
	{
		return (NULL);
	}

	memset(node, 0, sizeof(struct node_s));
	node->type = type;

	return (node);
}

/**
 * add_child_node - expands the AST of a simple command
 * @parent: the parent node
 * @child: the child node
 *
 * Return: void
 */
void add_child_node(struct node_s *parent, struct node_s *child)
{
	if (!parent || !child)
	{
		return;
	}

	if (!parent->first_child)
	{
		parent->first_child = child;
	}
	else
	{
		struct node_s *sibling = parent->first_child;

		while (sibling->next_sibling)
		{
			sibling = sibling->next_sibling;
		}
		sibling->next_sibling = child;
		child->prev_sibling = sibling;
	}
	parent->children++;
}

/**
 * set_node_val_str - sets a node's value to the given string.
 * @node: node to set value of
 * @val: value of node
 *
 * Return: void
 */
void set_node_val_str(struct node_s *node, char *val)
{
	node->val_type = VAL_STR;

	if (!val)
	{
		node->val.str = NULL;
	}
	else
	{
		char *val2 = malloc(strlen(val) + 1);

		if (!val2)
		{
			node->val.str = NULL;
		}
		else
		{
			strcpy(val2, val);
			node->val.str = val2;
		}
	}
}

/**
 * free_node_tree - frees the memory used by a node structure
 * @node: node whose memory is freed
 *
 * Return: void
 */
void free_node_tree(struct node_s *node)
{
	if (!node)
	{
		return;
	}

	struct node_s *child = node->first_child;

	while (child)
	{
		struct node_s *next = child->next_sibling;

		free_node_tree(child);
		child = next;
	}

	if (node->val_type == VAL_STR)
	{
		if (node->val.str)
		{
		free(node->val.str);
		}
	}
free(node);
}

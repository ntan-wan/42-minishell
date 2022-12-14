/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_node_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:41:50 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/09 03:21:59 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"

t_node	*ms_node_init(t_node_type type)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	ft_memset(new_node, 0, sizeof(t_node));
	new_node->type = type;
	return (new_node);
}

void	ms_node_child_add(t_node *parent, t_node *child)
{
	t_node	*sibling;

	if (!parent || !child)
		return ;
	if (!parent->first_child)
		parent->first_child = child;
	else
	{
		sibling = parent->first_child;
		while (sibling->next_sibling)
			sibling = sibling->next_sibling;
		sibling->next_sibling = child;
		child->prev_sibling = sibling;
	}
	parent->childs_count++;
}

void	ms_set_node_val_str(t_node *node, char *val)
{
	char	*val2;

	node->val_type = VAL_STR;
	if (!val)
		node->val.str = NULL;
	else
	{
		val2 = malloc(ft_strlen(val) + 1);
		if (!val2)
			node->val.str = NULL;
		else
		{
			ft_strlcpy(val2, val, ft_strlen(val) + 1);
			node->val.str = val2;
		}
	}
}

char	**ms_node_to_argv(t_node *node)
{
	int		count;
	size_t	size;
	t_node	*child;
	char	**argv;

	if (!node)
		return (NULL);
	count = 1;
	size = sizeof(char *);
	argv = NULL;
	child = node->first_child;
	while (child)
	{
		argv = util_realloc(argv, count * size, (++count + 1) * size);
		argv[count - 2] = ft_strdup(child->val.str);
		argv[count - 1] = 0;
		child = child->next_sibling;
	}
	return (argv);
}

void	ms_node_tree_free(t_node *node)
{
	t_node	*child;
	t_node	*next;

	if (!node)
		return ;
	child = node->first_child;
	next = NULL;
	while (child)
	{
		next = child->next_sibling;
		ms_node_tree_free(child);
		child = next;
	}
	if (node->val_type == VAL_STR)
	{
		if (node->val.str)
			free(node->val.str);
	}
	free(node);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 18:26:22 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

t_list	*expand_lst_argv(char **envp, void *ptr_token)
{
	const t_token	*token = ptr_token;

	return (expand_arg(envp, token->value));
}

t_list	*ms_expander(char **envp, t_list *lst, t_ftexpand ft_expand)
{
	t_list	*lst_new;

	lst_new = NULL;
	while (lst != NULL)
	{
		ft_lstadd_back(&lst_new, ft_expand(envp, lst->content));
		lst = lst->next;
	}
	return (lst_new);
}

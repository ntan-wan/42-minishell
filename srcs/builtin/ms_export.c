/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/07 15:22:15 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_common.h"

void	export_log(char **envp);

static int	isvalid_identifier(const char *str)
{
	if (!(ft_isalpha(*str) || *str == '_'))
		return (0);
	while (ft_isnameletter(*str))
		str++;
	return (ft_isnameend(*str));
}

static void	export(t_list **lst_buffer, char **envp, const char *arg)
{
	char	**var;

	var = env_getaddress(envp, arg);
	if (var == NULL)
		ft_lstadd_back(lst_buffer, ft_lstnew(ft_strdup(arg)));
	else if (ft_strchr(arg, '='))
	{
		free(*var);
		*var = ft_strdup(arg);
	}
}

int	ms_export(char **argv, t_data *data)
{
	t_list	*lst_buffer;
	int		retval;

	lst_buffer = NULL;
	if (argv[1] == NULL)
	{
		export_log(data->envp);
		return (0);
	}
	retval = 0;
	while (*++argv != NULL)
	{
		if (!isvalid_identifier(*argv))
		{
			ms_errlog("export: `%s': not a valid identifier\n", *argv);
			retval = 1;
		}
		else
			export(&lst_buffer, data->envp, *argv);
	}
	if (lst_buffer != NULL)
		data->envp = ft_strlistcombine(data->envp,
				(char **)ft_lsttoaa_clear(&lst_buffer));
	return (retval);
}

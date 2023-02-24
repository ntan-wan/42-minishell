/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:10:40 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/12/20 12:29:01 by ntan-wan         ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#include "minishell.h"

void	leakcheck(const char *str)
{
	char	buffer[39];

	if (str != NULL)
		ft_printf("leakcheck: %s\n", str);
	snprintf(buffer, sizeof(buffer), "leaks -q %d >&2", getpid());
	system(buffer);
}

void	ms_signals_handler(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

/*
	Is oldpwd inherited for the program execution?
*/
int	main(int argc, char **argv, char **envp)
{
	ft_cleanterminal();
	ms_signals_handler();
	ms_input(envp);
	leakcheck("mainend");
}
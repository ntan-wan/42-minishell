/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_common.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 00:52:27 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/25 10:21:08 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_COMMON_H
# define MS_COMMON_H

# include "libft.h"

int	g_lastexit;

typedef struct s_data
{
	char	**envp;
	int		fd_std[2];
}			t_data;

# define MINISHELL	"🐚"

int		ft_isquote(int c);
int		ft_isnameletter(int c);
int		ft_dup3(int fd_attribute, int fd_value);
int		ms_errlog(const char *str, ...);
void	ms_perror(const char *name);
void	ms_waitall(void);
/* Forbidden */
void	leakcheck(const char *str);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 22:30:54 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/09 03:20:05 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "node.h"

/* token_utils */
char	*ms_strtok(char *str, char *delimiter);

/* path_utils */
char	*ms_path_search(char *cmd);

int		ms_executor(t_node *node);
void	ms_cmds_free(char ***argv);
#endif
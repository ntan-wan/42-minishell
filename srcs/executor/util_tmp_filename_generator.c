/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_tmp_filename_generator.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:15:24 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/16 16:20:28 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*file_name_create(char *file_name, char *file_num, char *file_ext)
{
	char	*file;
	char	*to_be_freed;

	file = ft_strjoin(file_name, file_num);
	to_be_freed = file;
	file = ft_strjoin(file, file_ext);
	free(to_be_freed);
	return (file);
}

static char	*get_cwd_path(void)
{
	char	*cwd;
	char	*path;

	cwd = getcwd(NULL, 0);
	path = ft_strjoin(cwd, "/");
	free(cwd);
	return (path);
}

static bool	file_exists_in_cwd(char *file_name)
{
	bool	file_exists;
	char	*cwd_path;
	char	*tmp_file_name;

	cwd_path = get_cwd_path();
	tmp_file_name = ft_strjoin(cwd_path, file_name);
	if (access(tmp_file_name, F_OK) == 0)
		file_exists = true;
	else
		file_exists = false;
	free(cwd_path);
	free(tmp_file_name);
	return (file_exists);
}

char	*tmp_filename_create(int file_num)
{
	char	*file_num_str;
	char	*tmp_filename;

	file_num_str = ft_itoa(file_num);
	tmp_filename = file_name_create("tmp_file", file_num_str, ".tmp");
	free(file_num_str);
	return (tmp_filename);
}

char	*tmp_filename_generator(void)
{
	int		i;
	char	*tmp_filename;

	i = 0;
	tmp_filename = NULL;
	while (++i < INT_MAX)
	{
		tmp_filename = tmp_filename_create(i);
		if (file_exists_in_cwd(tmp_filename) == false)
			break ;
		free(tmp_filename);
	}
	return (tmp_filename);
}

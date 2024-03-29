/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_path_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:18:22 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/16 19:10:46 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	@brief Check whether the file is contained in the given path.
 */
bool	file_in_path(char *dir_path, char *file_name)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(dir_path);
	if (!dir_path || !file_name || !dir)
		return (false);
	entry = readdir(dir);
	while (entry)
	{
		if (util_is_same_str(entry->d_name, file_name))
		{
			closedir(dir);
			return (true);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (false);
}

/* 
	@brief Find absolute path to the cmd.
	@note Eg: "ls" -> "/usr/bin/ls"
 */
char	*absolute_path_find(char *file_name)
{
	int		i;
	char	*tmp;
	char	**paths;
	char	*absolute_path;

	i = -1;
	absolute_path = NULL;
	paths = ft_split(env_value_get("PATH"), ':');
	while (paths[++i])
	{
		if (file_in_path(paths[i], file_name))
		{
			tmp = ft_strjoin(paths[i], "/");
			absolute_path = ft_strjoin(tmp, file_name);
			free(tmp);
			break ;
		}
	}
	if (file_name && !absolute_path)
		absolute_path = ft_strdup(file_name);
	util_arr_str_free(paths);
	return (absolute_path);
}

bool	file_in_path2(char *path, char *file_name)
{
	char	*tmp;
	char	*tmp_path;
	bool	result;

	tmp = ft_strjoin(path, "/");
	tmp_path = ft_strjoin(tmp, file_name);
	if (access(tmp_path, F_OK | X_OK) == 0)
		result = true;
	else
		result = false;
	free(tmp);
	free(tmp_path);
	return (result);
}

char	*absolute_path_find2(char *file_name)
{
	int		i;
	char	*tmp;
	char	*absolute_path;
	char	**paths;

	i = -1;
	absolute_path = NULL;
	paths = ft_split(env_value_get("PATH"), ':');
	while (paths[++i])
	{
		if (file_in_path2(paths[i], file_name))
		{
			tmp = ft_strjoin(paths[i], "/");
			absolute_path = ft_strjoin(tmp, file_name);
			break ;
		}
	}
	util_arr_str_free(paths);
	return (absolute_path);
}
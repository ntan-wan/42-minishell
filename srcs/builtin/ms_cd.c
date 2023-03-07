/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:05 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/07 15:22:15 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_common.h"

static int	cd_updatepath(char **envp, const char *path)
{
	char	cwd[831];

	if (!getcwd(cwd, sizeof(cwd)))
		ms_perror("getcwd in cd");
	else if (chdir(path) == -1)
		ms_perror(path);
	else
	{
		env_update(envp, "OLDPWD", cwd);
		env_update(envp, "PWD", path);
		return (0);
	}
	return (1);
}

static const char	*cd_getpath(char **envp, const char *varname)
{
	const char	*path = env_getvalue(envp, varname);

	if (path == NULL)
		ms_errlog("cd: %s not set\n", varname);
	return (path);
}

int	ms_cd(char **argv, t_data *data)
{
	const char	*path = argv[1];

	if (path == NULL)
		path = cd_getpath(data->envp, "HOME");
	else if (!ft_strcmp(path, "-"))
		path = cd_getpath(data->envp, "OLDPWD");
	if (path == NULL)
		return (1);
	return (cd_updatepath(data->envp, path));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:02:36 by qalpesse          #+#    #+#             */
/*   Updated: 2024/08/20 22:45:32 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../my_libft/libft.h"

void	ft_free_spl(char **spl)
{
	int	i;

	i = 0;
	if (spl == NULL)
		return ;
	while (spl[i] != NULL)
	{
		free(spl[i]);
		i++;
	}
	free(spl);
}

char	**ft_binpaths(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	paths = NULL;
	while (env[i])
	{
		if (!strncmp(env[i], "PATH", 4))
		{
			paths = ft_split(&env[i][5], ':');
			break ;
		}
		i ++;
	}
	return (paths);
}

char	*ft_path(char *exec, char **env)
{
	char	*path;
	char	**paths;
	int		i;

	path = NULL;
	paths = ft_binpaths(env);
	if (!paths)
		ft_error("env : no comand path");
	i = 0;
	while (paths[i])
	{
		if (!access(ft_strjoin(paths[i], ft_strjoin("/", exec)), X_OK))
		{
			path = ft_strjoin(paths[i], ft_strjoin("/", exec));
			ft_free_spl(paths);
			return (path);
		}
		i++;
	}
	ft_free_spl(paths);
	return (path);
}

void	ft_execute(char *exec, char **env)
{
	char	**grep_args;

	grep_args = ft_split(exec, ' ');
	if (execve(ft_path(grep_args[0], env), grep_args, env) == -1)
	{
		ft_free_spl(grep_args);
		ft_error("execve");
	}
	ft_free_spl(grep_args);
}

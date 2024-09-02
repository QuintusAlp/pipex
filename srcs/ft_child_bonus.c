/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:35:00 by qalpesse          #+#    #+#             */
/*   Updated: 2024/08/21 14:10:22 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include "../my_libft/libft.h"

void	ft_child(t_param param, char **argv, char **env, int pipefd[2])
{
	if (param.i == 2)
		ft_first_child(pipefd, argv[1], argv[param.i], env);
	else if (argv[param.i + 2] == NULL)
		ft_last_child(param, pipefd, argv, env);
	else
		ft_mid_child(param.dupfd, pipefd, argv[param.i], env);
}

void	ft_child_for_here_doc(t_param param, char **argv,
	char **env, int pipefd[2])
{
	if (param.i < 3)
		exit (1);
	if (param.i == 3)
		ft_first_child(pipefd, "/tmp/hd_file", argv[param.i], env);
	else if (argv[param.i + 2] == NULL)
		ft_last_child_for_here_doc(param, pipefd, argv, env);
	else
		ft_mid_child(param.dupfd, pipefd, argv[param.i], env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:04:43 by qalpesse          #+#    #+#             */
/*   Updated: 2024/08/15 16:08:44 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include "../my_libft/libft.h"

void	ft_first_child(int pipefd[2], char *file_name, char *exec, char **env)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		ft_error("open");
	if (dup2(fd, STDIN_FILENO) == -1)
		ft_error("dup2");
	close(fd);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		ft_error("dup2");
	close(pipefd[1]);
	close(pipefd[0]);
	ft_execute(exec, env);
}

void	ft_mid_child(int dupfd, int pipefd[2], char *exec, char **env)
{
	if (dup2(dupfd, STDIN_FILENO) == -1)
		ft_error("dup2");
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		ft_error("dup2");
	close(pipefd[1]);
	close(pipefd[0]);
	close(dupfd);
	ft_execute(exec, env);
}

void	ft_last_child(t_param param, int pipefd[2], char **argv, char **env)
{
	int	fdout;

	fdout = open(argv[param.i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdout == -1)
		ft_error("open");
	if (dup2(param.dupfd, STDIN_FILENO) == -1)
		ft_error("dup2");
	close(param.dupfd);
	close(pipefd[0]);
	close(pipefd[1]);
	if (dup2(fdout, STDOUT_FILENO) == -1)
		ft_error("dup2");
	close(fdout);
	ft_execute(argv[param.i], env);
}

void	ft_last_child_for_here_doc(t_param param, int pipefd[2],
	char **argv, char **env)
{
	int	fdout;

	fdout = open(argv[param.i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fdout == -1)
		ft_error("open");
	if (dup2(param.dupfd, STDIN_FILENO) == -1)
		ft_error("dup2");
	close(param.dupfd);
	close(pipefd[0]);
	close(pipefd[1]);
	if (dup2(fdout, STDOUT_FILENO) == -1)
		ft_error("dup2");
	close(fdout);
	ft_execute(argv[param.i], env);
}

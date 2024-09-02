/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:02:29 by qalpesse          #+#    #+#             */
/*   Updated: 2024/08/21 14:21:37 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../my_libft/libft.h"

void	first_child_process(int pipefd[2], char **argv, char **env)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_error("open");
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_error("dup2");
	}
	close (fd);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		ft_error("dup2");
	}
	close (pipefd[1]);
	close (pipefd[0]);
	ft_execute(argv[2], env);
}

void	second_child_process(int pipefd[2], char **argv, char **env)
{
	int	fdout;

	fdout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdout == -1)
	{
		ft_error("open");
	}
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		ft_error("dup2");
	}
	close (pipefd[0]);
	close (pipefd[1]);
	if (dup2(fdout, STDOUT_FILENO) == -1)
	{
		ft_error ("dup2");
	}
	close (fdout);
	ft_execute (argv[3], env);
}

void	ft_close_and_wait(int pipefd[2], int pids[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pids[0], NULL, 0);
	waitpid(pids[1], NULL, 0);
}

int	main(int argc, char **argv, char **env)
{
	int	pipefd[2];
	int	pids[2];

	if (argc != 5)
		return (perror("number of args"), 1);
	if (pipe(pipefd) == -1)
		ft_error("pipe");
	pids[0] = fork();
	if (pids[0] == -1)
		ft_error("fork");
	if (pids[0] == 0)
		first_child_process(pipefd, argv, env);
	pids[1] = fork();
	if (pids[1] == -1)
		ft_error("fork");
	if (pids[1] == 0)
		second_child_process(pipefd, argv, env);
	ft_close_and_wait(pipefd, pids);
	return (0);
}

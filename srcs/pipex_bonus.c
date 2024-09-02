/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:19:27 by qalpesse          #+#    #+#             */
/*   Updated: 2024/08/22 16:47:26 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include "../my_libft/libft.h"

void	ft_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

int	ft_strfind(char *str, char *str_to_find)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == str_to_find[i])
		i++;
	if (str_to_find[i] == '\0')
		return (1);
	else
		return (0);
}

void	ft_here_doc(char **argv)
{
	char	*str;
	int		fd;

	ft_printf("here_doc\n");
	fd = open("/tmp/hd_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_error("open");
	str = get_next_line(STDIN_FILENO);
	while (str && !ft_strfind(str, argv[2]))
	{
		if (write(fd, str, ft_strlen(str)) == -1)
		{
			free(str);
			ft_error("write");
		}
		free(str);
		str = get_next_line(STDIN_FILENO);
	}
}

void	ft_processing(int argc, char **argv, char **env,
	void (*ft_child)(t_param, char **, char **, int *))
{
	int		pipefd[2];
	t_param	param;

	param.i = 2;
	param.pid = 1;
	param.dupfd = -1;
	while (param.i < argc - 1)
	{
		ft_pipe(pipefd);
		param.pid = fork ();
		if (param.pid == 0)
			ft_child(param, argv, env, pipefd);
		if (param.dupfd != -1)
			close (param.dupfd);
		param.dupfd = dup(pipefd[0]);
		close (pipefd[0]);
		close(pipefd[1]);
		param.i++;
	}
	while (wait(NULL) > 0)
		;
}

int	main(int argc, char **argv, char **env)
{
	if (argc < 2)
		return (perror("number of args"), 1);
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		if (argc < 5)
			return (perror("number of args"), 1);
		ft_here_doc(argv);
		ft_processing(argc, argv, env, ft_child_for_here_doc);
		if (unlink("/tmp/hd_file") == -1)
			ft_error("unlink");
	}
	else
	{
		if (argc < 5)
			return (perror("number of args"), 1);
		ft_processing(argc, argv, env, ft_child);
	}
	return (0);
}

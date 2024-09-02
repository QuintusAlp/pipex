/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:36:08 by qalpesse          #+#    #+#             */
/*   Updated: 2024/08/15 16:08:16 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

typedef struct s_param
{
	int	i;
	int	pid;
	int	dupfd;
}	t_param;
void	ft_execute(char *exec, char **env);
void	ft_child(t_param param, char **argv, char **env, int pipefd[2]);
void	ft_child_for_here_doc(t_param param, char **argv,
			char **env, int pipefd[2]);
//type of child 
void	ft_first_child(int pipefd[2], char *file_name, char *exec, char **env);
void	ft_mid_child(int dupfd, int pipefd[2], char *exec, char **env);
void	ft_last_child(t_param param, int pipefd[2], char **argv, char **env);
void	ft_last_child_for_here_doc(t_param param, int pipefd[2],
			char **argv, char **env);
//error
void	ft_error(char *error_message);
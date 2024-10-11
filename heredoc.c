/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:21:30 by jomendes          #+#    #+#             */
/*   Updated: 2024/10/11 15:01:28 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_limiters(char **split)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	
	while (split[i])
	{
		if (ft_strncmp(split[i], "<<", 2) == 0)
		{
			if (split[i + 1])
				count++;
		}
		i++;
	}
	return (count);
}

void	free_array(char **array)
{
	int	i;
	
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	heredoc_lim_array(t_vars *mini)
{
	int		i;
	char	**split;
	int		j;

	i = 0;
	j = 0;
	split = ft_split(mini->input, ' ');
	mini->limiters = malloc(sizeof(char *) * (count_limiters(split) + 1));
	if (!mini->limiters)
		return;
	while (split[i])
	{
		if (ft_strncmp(split[i], "<<", 2) == 0)
		{
			i++;
			mini->limiters[j] = ft_strdup(split[i]);
			if (!mini->limiters[j])
			{
				free_array(mini->limiters);
				free_array(split);
				return;
			}
			j++;
		}
		i++;
	}
	mini->limiters[j] = NULL;
	free_array(split);
}

void	ft_putstr_newline(char *str, int fd)
{
	if (!str)
		return;
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

void	heredoc_input(int fd[2], char **limiters)
{
	char	*line;
	int		total_lim;
	int		i;

	i = 0;
	total_lim = 0;
	while (limiters[total_lim])
		total_lim++;
	while (1)
	{
		line = readline("> ");
		if (line == NULL ||
		(ft_strncmp(line, limiters[i], ft_strlen(limiters[i])) == 0
		&& ft_strlen(line) == ft_strlen(limiters[i])))
		{
			free(line);
			i++;
			if (i == total_lim)
				break;
			continue;
		}
		if (i < total_lim)
		{
			printf("aqui\n");
			ft_putstr_newline(line, fd[1]);
		}
		free(line);
	}
	close(fd[1]);
}

void	fork_error(void)
{
	perror("Error forking\n");
	exit(EXIT_FAILURE);
}

void	heredoc_child(int fd[2], char **limiters)
{
	// signal(SIGINT, heredoc_signal);
	close(fd[0]);
	heredoc_input(fd, limiters);
	// close unprotected fds();
	//free_minishell(mini);
	exit(EXIT_SUCCESS);
}

void	creat_pipe(int fd[2])
{
	if (pipe(fd) < 0)
	{
		perror("Error creating pipe\n");
		exit(EXIT_FAILURE);
	}
}

int		heredoc(t_vars *mini)
{
	pid_t	pid;
	int		fd[2];
	int		status;
	//int		exit_status;

	fd[0] = -1;
	fd[1] = -1;
	status = 0;
	heredoc_lim_array(mini);
	if (!mini->limiters)
		return (EXIT_FAILURE);
	creat_pipe(fd);
	pid = fork();
	if (pid < 0)
		fork_error();
	else if (pid == 0)
		heredoc_child(fd, mini->limiters);
	close(fd[1]);
	close(fd[0]);
	dup2(fd[0], STDIN_FILENO);
	wait(&status);
	if (WIFEXITED(status) && WEXITSTATUS(status) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	//exit_status = WEXITSTATUS(status);
	// if (exit_status == EXIT_FAILURE || xit_status == EXIT_HEREDOC_BREAK)
	//{
	//	free_minishell(mini);
	//	return (exit_status);
	//}
	return (EXIT_SUCCESS);
}

int		check_heredoc(t_vars *mini)
{
	int i;

	i = 0;
	while (mini->input[i])
	{
		if (mini->input[i] == '<' && mini->input[i + 1] == '<')
		{
			mini->heredoc_on = 1;
			return (0);
		}
		i++;
	}
	return (1);
}
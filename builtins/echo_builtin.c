/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:17:33 by jomendes          #+#    #+#             */
/*   Updated: 2024/07/06 16:56:25 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_flag(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-')
		{
			i++;
			if (str[i] == 'n')
			{
				while (str[i] == 'n')
					i++;
				if (str[i] != '\0')
					return (0);
			}
			else
				return (0);
		}
		else
			return (0);
	}
	return (1);
}

int	dollar_flag(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (0);
		i++;
	}
	return (1);
}

char *take_equal(char *str)
{
	int i;
	char *tmp;

	i = 0;
	tmp = malloc(sizeof(char) * ft_strlen(str));
	while (str[i] != '=')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

void	echo_dollar_finish(char *str, t_vars *mini)
{
	int i;
	char *result;
	int j;
	int u = 0;

	j = 0;
	i = 0;
	result = ft_strdup(str + 1);
	if (!result)
		return ;
	if (mini->env[i])
	{
		while (ft_strncmp(result, mini->env[i], ft_strlen(result)) != 0)
			i++;
		if (ft_strncmp(result, mini->env[i], ft_strlen(result)) == 0 \
		&& ft_strlen(result) == ft_strlen(take_equal(mini->env[i])))
		{
			str = mini->env[i];
			while (str[j++] == result[u++])
				;
			while (str[j] != '\0')
				printf("%c", str[j++]);
		}
		i++;
	}
	else 
		printf("\n");
}

int	echo_builtin(t_vars *mini)
{
	int		i;
	char	**split;
	int		new_line;
	
	i = 0;
	new_line = 1;
	split = ft_split(mini->input, ' ');
	if (ft_strchr(mini->input, ' '))
	{
		while (split && is_flag(split[++i]))
			new_line = 0;
	}
	if (dollar_flag(split[1]) == 0)
		echo_dollar_finish(split[1], mini);
	while (split[i] && dollar_flag(split[i]) != 0)
	{
		printf("%s", split[i]);
		if (split[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	return (0);
}

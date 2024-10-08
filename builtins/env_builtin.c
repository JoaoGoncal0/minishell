/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:26:12 by jomendes          #+#    #+#             */
/*   Updated: 2024/10/08 10:43:27 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_update1(t_vars *mini)
{
	int i;
	int j;
	char **temp;

	i = 0;
	j = 0;
	while (i < mini->env_len)
	{
		if (mini->env[i])
		{
			free(mini->env[i]);
			mini->env[i] = NULL;
		}
		i++;
	}
	i = 0;
	temp = realloc(mini->env, sizeof(char *) * (mini->env_len + 1));
	if (!temp)
		return;
	mini->env = temp;
	while (j < mini->env_len)
	{
		if (mini->new_env[j])
			mini->env[j] = ft_strdup(mini->new_env[j]);
		else
			mini->env[j] = NULL;
		j++;
	}
	mini->env[j] = NULL;
	//printf("\n\n----- UPDATED ENV ------\n\n\n");
	//j = -1;
	//while (++j < mini->env_len)
	//{
	//	if (!mini->new_env[j])
	//		continue;
	//	printf("%s\n", mini->new_env[j]);
	//}
}

void	env_update(t_vars *mini, char *str)
{
	int	i;
	int j;
	int k;

	i = 0;
	k = 0;
	while (k < mini->env_len)
	{
		if (mini->new_env[k])
		{
			free(mini->new_env[k]);
			mini->new_env[k] = NULL;
		}
		k++;
	}	
	while (i < mini->env_len)
	{
		if ((mini->env[i] && 
		ft_strncmp(mini->env[i], str, ft_strlen(str)) == 0) ||
		!mini->env[i])
		{
			printf("valor do iiiii = %d\n", i);
			i++;
			continue;
		}
		if (mini->env[i])
		{
			printf("valor do i = %d\n", i);
			mini->new_env[i] = ft_strdup(mini->env[i]);
			printf("mini->new_env = %s\n", mini->env[i]);
			i++;
		}
	}
	mini->new_env[i] = NULL;
	printf("\n\n----- UPDATED ENV ------\n\n\n");
	j = -1;
	while (++j < mini->env_len)
	{
		while (!mini->new_env[j])
			j++;
		printf("%s\n", mini->new_env[j]);
	}
	env_update1(mini);
}
		

void	init_env(char **env, t_vars *mini)
{
	int	i;
	
	i = 0;
	while (env[i])
		i++;
	mini->env = malloc(sizeof(char *) * (i + 1));
	mini->new_env = malloc(sizeof(char *) * (i + 10));
	if (!mini->env || !mini->new_env)
		return ;
	mini->env_len = i;
	i = 0;
	while (i < mini->env_len)
	{
		mini->env[i] = ft_strdup(env[i]);
		i++;
	}
	mini->env[i] = NULL;
}

void	env_builtin(t_vars *mini)
{
	int	i;

	i = 0;
	printf("len = %d\n", mini->env_len);
	while (i < mini->env_len)
	{
		if (!mini->env[i])
			i++;
		if (mini->env[i])
		{
			//printf("o %s existe em %p\n\n",mini->env[i], mini->env[i]);
			printf("%s\n", mini->env[i]);
			i++;
		}
	}
}

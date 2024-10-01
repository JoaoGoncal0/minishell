/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:46:26 by jomendes          #+#    #+#             */
/*   Updated: 2024/09/30 21:56:13 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// verificar o numero de argumentos e o formato dos mesmos
// só aceito letras ou o _ 
// seguidas de letras minus Maius ou numeros ou _
// adicionar ao export

int     export_check(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
		if (str[0] == '=')
		{
			printf("export: `%c': not a valid identifier\n", str[i]);
    		return (1);
		}
        if ((str[i] >= 'a' && str[i] <= 'z') || 
        (str[i] >= 'A' && str[i] <= 'Z') || (str[i] == '_') ||
		str[i] == '=')
            return (0);
        i++;
    }
	printf("export: `%c': not a valid identifier\n", str[i]);
    return (1);
}

void    export_var(t_vars *mini)
{
    int     i;
    char    **split;

    i = 1;
    split = ft_split(mini->input, ' ');
	mini->new_export = malloc(sizeof(char *) * (mini->exp_len + 10));
	if (!mini->new_export)
		return;
    while (split[i]) 
    {
		mini->exp_len = export_len(mini->export) + 1;
		printf("\nsplit = %s\n", split[i]);
        if (export_check(split[i]) == 0)
        {
			export_update(mini, split[i]);
			i++;
		}
    }
}

void	export_update(t_vars *mini, char *str)
{
	int	i;
	int k;
    int done;
    
	i = 0;
	k = 0;
    done = 0;
	if (!mini->new_export)
    {
        printf("Error: mini->new_export not initialized.\n");
        return;
	}
	while (k < mini->exp_len)
	{
		if (mini->new_export[k])
		{
			free(mini->new_export[k]);
			mini->new_export[k] = NULL;
		}
		k++;
	}
	while (i < mini->exp_len)
	{
		if (!mini->export[i] && done == 0)
		{
            done = 1;
            mini->new_export[i] = ft_strdup(str);
			printf("Inserido em new_export[%d]: %s\n", i, mini->new_export[i]);
			i++;
		}
		else if (mini->export[i])
		{
			mini->new_export[i] = ft_strdup(mini->export[i]);
			i++;
		}
	}
	mini->new_export[i] = NULL;
	export_update1(mini);
}

void	export_update1(t_vars *mini)
{
	int i;
	int j;
	char **temp;
    int s;

	i = 0;
	j = 0;
    //mini->exp_len = export_len(mini->new_export);
    printf("valor do lennnnn %d\n", mini->exp_len);
	while (i < mini->exp_len)
	{
		if (mini->export[i])
		{
			free(mini->export[i]);
			mini->export[i] = NULL;
		}
		i++;
	}
	printf("\n\n----- NULL EXPORT ------\n\n\n");
	s = -1;
	while (++s < mini->exp_len)
		printf("declare -x: %s\n", mini->export[s]);
	i = 0;
	printf("\n\n\nvalor do exp_len = %d\n\n\n", mini->exp_len);
	temp = realloc(mini->export, sizeof(char *) * (mini->exp_len + 1));
	if (!temp)
		return;
	mini->export = temp;
	while (j < mini->exp_len)
	{
        mini->export[j] = ft_strdup(mini->new_export[j]);
		j++;
    }
	mini->export[j] = NULL;
	sorting_export(mini);
	printf("\n\n----- UPDATED EXPORT ------\n\n\n");
	s = -1;
	while (++s < mini->exp_len)
		printf("fake -x %s\n", mini->export[s]);
}
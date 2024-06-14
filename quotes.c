#include "minishell.h"

int check_quotes(char *input)
{
    int i;
    int single_quote;
    int double_quote;

    i = 0;
    single_quote = 0;
    double_quote = 0;
    while (input[i])
    {
        if (input[i] == '\'' && single_quote == 0)
            single_quote = 1;
        else if (input[i] == '\"' && double_quote == 0)
            double_quote = 1;
        else if (input[i] == '\'' && single_quote == 1)
            single_quote = 0;
        else if (input[i] == '\"' && double_quote == 1)
            double_quote = 0;
        i++;
    }
    if (single_quote != 0 || double_quote != 0)
    {
        printf ("Quote error\n");
        printf("single = %d\n", single_quote);
        printf("double = %d\n", double_quote);
        return (1);
    }
    return (0);
}

void    remove_single_quote(char *cmd)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (cmd[i] != '\0')
    {  
        if (cmd[i] != '\'')
        { 
            cmd[j] = cmd[i];
            j++;
        }  
        i++;
    }
    cmd[j] = '\0';
}

void    remove_double_quote(char *cmd)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (cmd[i] != '\0')
    {  
        if (cmd[i] != '\"')
        { 
            cmd[j] = cmd[i];
            j++;
        }  
        i++;
    }
    cmd[j] = '\0';
}


#include "../includes/minishell.h"

static int	ft_init_file(t_list *lst, t_cmd *cmd)
{
	char	*file;

	lst->next->content = parse_line(lst->next->content);
	file = lst->next->content;
	if (!ft_strncmp(lst->content, "<", 1))
	{
		if (cmd->in_file)
			close(cmd->in_file);
		return (cmd->in_file = open(file, O_RDONLY));
	}
	else if (!ft_strncmp(lst->content, ">", 1))
	{
		if (cmd->out_file)
			close(cmd->out_file);
		return (cmd->out_file = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	}
	else if (!ft_strncmp(lst->content, "<<", 2))
	{
		if (cmd->in_file)
			close(cmd->in_file);
		return (cmd->in_file = open(file, O_RDONLY)); // ??? проверить
	}
	else if (!ft_strncmp(lst->content, ">>", 2))
	{
		if (cmd->in_file)
			close(cmd->in_file);
		return (cmd->out_file = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	}
	return (0);
}

static int	args_counter(t_list *lst)
{
	int		count;
	char	*token;

	count = 0;
	while (lst)
	{
		token = lst->content;
		if (*token == '<' || *token == '>')
			break ;
		if (*token == '|')
			break ;
		lst = lst->next;
		count++;
	}
	return (count);
}

static char	**init_cmd_args(t_list **lst)
{
	int		count_args;
	char	**args;
	int		i;

	i = 0;
	count_args = args_counter(*lst);
	args = (char**)malloc((sizeof(char *) * count_args) + 1);
	if (!args)
		return (NULL);
	memset(args, '\0', sizeof(char *) * count_args + 1);
	while (i < count_args)
	{
		(*lst)->content = parse_line((*lst)->content);
		args[i] = ft_strdup((*lst)->content);
		(*lst) = (*lst)->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

int	init_cmd(t_list *lst, t_mshl *mini)
{
	int		i;
	char	*token;

	i = 0;
	while (lst)
	{
		token = lst->content;
		if (!token)
			return (1);
		if (*token == '<' || *token == '>')
		{
			if ((ft_init_file(lst, &(mini->cmd[i]))) == -1)
			{
				strerror(-1); // Edit
				return (1);
			}
			lst = lst->next->next;
		}
		else if (*token == '|')
		{
			i++;
			lst = lst->next;
		}
		else
		{
			lst->content = parse_line(lst->content);
			mini->cmd[i].cmd = ft_strdup(lst->content);
			mini->cmd[i].arguments = init_cmd_args(&lst);
		}
	}
	return (0);
}

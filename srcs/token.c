#include "minishell.h"

t_token	*token_new(char *str, enum e_tokentype type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->value = str;
	token->type = type;
	return (token);
}

void	del_token(void *content)
{
	t_token	*token;

	token = content;
	free(token->value);
	free(token);
}

const char	*lstiter_tokenname(const char *newname)
{
	static const char	*name = "token";

	if (newname != NULL)
		name = newname;
	return (name);
}

void	lstiter_showtoken(int i, void *content)
{
	const t_token	*token = content;
	char			*str_type;

	if (isoperator_rdrt(token->type))
		str_type = "Redirect";
	else if (isoperator_ctrl(token->type))
		str_type = "Control";
	else if (isoperator_subsh(token->type))
		str_type = "Subshell";
	else
		str_type = "Default";
	ft_printf("%s[%d]: %s{%b}\n", lstiter_tokenname(NULL), i, str_type, token->value);
}
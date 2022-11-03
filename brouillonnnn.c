
// #include "minishell.h"

// void	ft_processus_pipe_1(t_list *tmp, t_data *x, t_list **cpenv)
// {
// 	t_list *cmd;
// 	t_list *redir;

// 	cmd = (t_list *)((t_cmdredir *)tmp->content)->cmd;
// 	redir = (t_list *)((t_cmdredir *)tmp->content)->redirection;
// 	close(((t_cmdredir *)tmp->next->content)->fd_cmd[0]);
// 	ft_catch_file_tekflemme(&redir,  x);
// 	if (((t_cmdredir *)tmp->content)->fd_cmd[0] != STDIN_FILENO)
// 	{
// 		dup2(((t_cmdredir *)tmp->content)->fd_cmd[0], STDIN_FILENO);
// 		close(((t_cmdredir *)tmp->content)->fd_cmd[0]);
// 	}
// 	if (((t_cmdredir *)tmp->content)->fd_cmd[1] != STDOUT_FILENO)
// 	{
// 		dup2(((t_cmdredir *)tmp->content)->fd_cmd[1], STDOUT_FILENO);
// 		close(((t_cmdredir *)tmp->content)->fd_cmd[1]);
// 	}
// 	ft_cmd_constructor(&cmd, x, cpenv);
// 	if (x->pc != NULL)
// 	{
// 		//dprintf(2, "1) fd_cmd = (%i, %i)\n", ((t_cmdredir *)tmp->content)->fd_cmd[0], ((t_cmdredir *)tmp->content)->fd_cmd[1]);
// 		execve(x->pc, x->option, x->env);
// 	}
// 	free(x->pc);
// 	free(x->option);
// }

// void	ft_processus_pipe_2(t_list *tmp, t_data *x, t_list **cpenv)
// {
// 	t_list *cmd;
// 	t_list *redir;

// 	cmd = (t_list *)((t_cmdredir *)tmp->content)->cmd;
// 	redir = (t_list *)((t_cmdredir *)tmp->content)->redirection;
// 	ft_catch_file_tekflemme(&redir,  x);
// 	if (((t_cmdredir *)tmp->content)->fd_cmd[0] != STDIN_FILENO)
// 	{
// 		dup2(((t_cmdredir *)tmp->content)->fd_cmd[0], STDIN_FILENO);
// 		close(((t_cmdredir *)tmp->content)->fd_cmd[0]);
// 	}
// 	if (((t_cmdredir *)tmp->content)->fd_cmd[1] != STDOUT_FILENO)
// 	{
// 		dup2(((t_cmdredir *)tmp->content)->fd_cmd[1], STDOUT_FILENO);
// 		close(((t_cmdredir *)tmp->content)->fd_cmd[1]);
// 	}
// 	ft_cmd_constructor(&cmd, x, cpenv);
// 	if (x->pc != NULL)
// 	{
// 		//dprintf(2, "2) fd_cmd = (%i, %i)\n", ((t_cmdredir *)tmp->content)->fd_cmd[0], ((t_cmdredir *)tmp->content)->fd_cmd[1]);
// 		execve(x->pc, x->option, x->env);
// 	}
// 	free(x->pc);
// 	free(x->option);
// }

// void	ft_processus_pipe_3(t_list *tmp, t_data *x, t_list **cpenv)
// {
// 	t_list *cmd;
// 	t_list *redir;

// 	cmd = (t_list *)((t_cmdredir *)tmp->content)->cmd;
// 	redir = (t_list *)((t_cmdredir *)tmp->content)->redirection;
// 	ft_catch_file_tekflemme(&redir,  x);
// 	if (((t_cmdredir *)tmp->content)->fd_cmd[0] != STDIN_FILENO)
// 	{
// 		dup2(((t_cmdredir *)tmp->content)->fd_cmd[0], STDIN_FILENO);
// 		close(((t_cmdredir *)tmp->content)->fd_cmd[0]);
// 	}
// 	if (((t_cmdredir *)tmp->content)->fd_cmd[1] != STDOUT_FILENO)
// 	{
// 		dup2(((t_cmdredir *)tmp->content)->fd_cmd[1], STDOUT_FILENO);
// 		close (((t_cmdredir *)tmp->content)->fd_cmd[1]);
// 	}
// 	ft_cmd_constructor(&cmd, x, cpenv);
// 	if (x->pc != NULL)
// 	{
// 		//dprintf(2, "3) fd_cmd = (%i, %i)\n", ((t_cmdredir *)tmp->content)->fd_cmd[0], ((t_cmdredir *)tmp->content)->fd_cmd[1]);
// 		execve(x->pc, x->option, x->env);
// 	}
// 	free(x->pc);
// 	free(x->option);
// }


// void	ft_execution_pipe(t_list **after_doll, t_list **cpenv, t_data *x, int nb_cmd)
// {
// 	t_list *tmp;

// 	pid_t *processus;
// 	int	i;

// 	processus = malloc(sizeof(pid_t) * nb_cmd);
// 	i = 0;
// 	(void)x;
// 	(void)cpenv;
// 	tmp = *after_doll;
// 	///////////////PIPE///////////////
// 	if (pipe(x->fd_pipe) == -1)
// 		return (perror("Minimichel: pipe: "));
// 	signal(SIGQUIT, handle_sig_child);
//     signal(SIGINT, handle_sig_child);
// 	////////////////MAILLON 1/////////////////
// 	((t_cmdredir *) tmp->content)->fd_cmd[0] = STDIN_FILENO;
// 	((t_cmdredir *)tmp->content)->fd_cmd[1] = x->fd_pipe[1];
// 	((t_cmdredir *)tmp->next->content)->fd_cmd[0] = x->fd_pipe[0];
// 	processus[i] = fork();//////////////////////////////////////////////////FORK 1
// 	if (processus[i] < 0)
// 		return (perror("Minimichel: fork: "));
// 	if (processus[i] == 0)
// 		ft_processus_pipe_1(tmp, x, cpenv);///////////////////////////////APPEL PROCESSUS 1
// 	close(((t_cmdredir *)tmp->content)->fd_cmd[1]);

// 	ft_free_array(x->option);
// 	tmp = tmp->next;
// 	i++;
// 	while (tmp && tmp->next)
// 	{
// 		if (pipe(x->fd_pipe) == -1)
// 			return (perror("Minimichel: pipe: "));
// 		((t_cmdredir *)tmp->content)->fd_cmd[1] = x->fd_pipe[1];
// 		((t_cmdredir *)tmp->next->content)->fd_cmd[0] = x->fd_pipe[0];
// 		///////////////MAILLON 2///////////////////////
// 		processus[i] = fork();/////////////////////////////////////////////////FORK 2
// 		if (processus[i] < 0)
// 			return (perror("Minimichel: fork: "));
// 		if (processus[i] == 0)
// 		{
// 			ft_processus_pipe_2(tmp, x, cpenv);///////////////////////////////////APPEL PROCESSUS 2
// 		}
// 		close(((t_cmdredir *)tmp->content)->fd_cmd[0]);
// 		close(((t_cmdredir *)tmp->content)->fd_cmd[1]);
// 		ft_free_array(x->option);
// 		tmp = tmp->next;

// 		i++;
// 	}
// 	((t_cmdredir *)tmp->content)->fd_cmd[1] = STDOUT_FILENO;
// 	/////////////////MAILLON 3////////////////////////////
// 	processus[i] = fork();///////////////////////////////////////////////////////FORK 3
// 	if (processus[i] < 0)
// 		return (perror("Minimichel: fork: "));
// 	if (processus[i] == 0)
// 	{
// 		ft_processus_pipe_3(tmp, x, cpenv);//////////////////////////////////////////APPEL PROCESSUS 3
// 	}
// 	else
// 	{
// 		close(((t_cmdredir *)tmp->content)->fd_cmd[0]);
// 		i = 0;
// 		while (i < nb_cmd)
// 		{
// 			waitpid(processus[i], &g_status, 0);
// 			if (WIFEXITED(g_status))
// 				g_status = WEXITSTATUS(g_status);
// 			if (WIFSIGNALED(g_status))
// 				g_status = WTERMSIG(g_status) + 128;
// 			i++;
// 		}
// 		signal(SIGQUIT, SIG_IGN);
// 	    signal(SIGINT, handle_sig_parent);
// 		ft_free_array(x->option);
// 	}
// }

// void	ft_processus_pipe_1(t_list *tmp, t_data *x, t_list **cpenv)
// {
// 	t_list *cmd;
// 	t_list *redir;

// 	dprintf(2, "je rentre dans processus 1 ! \n");
// 	cmd = (t_list *)((t_cmdredir *)tmp->content)->cmd;
// 	redir = (t_list *)((t_cmdredir *)tmp->content)->redirection;
// 	close(((t_cmdredir *)tmp->next->content)->fd_cmd[0]);
// 	if (ft_is_builtin(&tmp, x, cpenv) == 0)
// 		return ;
// 	ft_catch_file_tekflemme(&tmp,  x);
// 	if (((t_cmdredir *)tmp->content)->fd_cmd[0] != STDIN_FILENO)
// 	{
// 		dup2(((t_cmdredir *)tmp->content)->fd_cmd[0], STDIN_FILENO);
// 		close(((t_cmdredir *)tmp->content)->fd_cmd[0]);
// 	}
// 	if (((t_cmdredir *)tmp->content)->fd_cmd[1] != STDOUT_FILENO)
// 	{
// 		dup2(((t_cmdredir *)tmp->content)->fd_cmd[1], STDOUT_FILENO);
// 		close(((t_cmdredir *)tmp->content)->fd_cmd[1]);
// 	}
// 	ft_cmd_constructor(&cmd, x, cpenv);
// 	if (x->pc != NULL)
// 	{
// 		//dprintf(2, "1) fd_cmd = (%i, %i)\n", ((t_cmdredir *)tmp->content)->fd_cmd[0], ((t_cmdredir *)tmp->content)->fd_cmd[1]);
// 		execve(x->pc, x->option, x->env);
// 	}
// 	free(x->pc);
// 	free(x->option);
// }

// void	ft_processus_pipe_3(t_list *tmp, t_data *x, t_list **cpenv)
// {
// 	t_list *cmd;
// 	t_list *redir;

// 	//dprintf(2, "je rentre dans processus 3 ! \n");
// 	ft_catch_file_tekflemme(&tmp,  x);
// 	cmd = (t_list *)((t_cmdredir *)tmp->content)->cmd;
// 	redir = (t_list *)((t_cmdredir *)tmp->content)->redirection;
// 	if (ft_is_builtin(&tmp, x, cpenv) == 0)
// 		return ;
// 	if (((t_cmdredir *)tmp->content)->fd_cmd[0] != STDIN_FILENO)
// 	{
// 		dup2(((t_cmdredir *)tmp->content)->fd_cmd[0], STDIN_FILENO);
// 		close(((t_cmdredir *)tmp->content)->fd_cmd[0]);
// 	}
// 	if (((t_cmdredir *)tmp->content)->fd_cmd[1] != STDOUT_FILENO)
// 	{
// 		dup2(((t_cmdredir *)tmp->content)->fd_cmd[1], STDOUT_FILENO);
// 		close (((t_cmdredir *)tmp->content)->fd_cmd[1]);
// 	}
// 	ft_cmd_constructor(&cmd, x, cpenv);
// 	if (x->pc != NULL)
// 	{
// 		//dprintf(2, "3) fd_cmd = (%i, %i)\n", ((t_cmdredir *)tmp->content)->fd_cmd[0], ((t_cmdredir *)tmp->content)->fd_cmd[1]);
// 		execve(x->pc, x->option, x->env);
// 	}
// 	free(x->pc);
// 	free(x->option);
// }



// void	ft_dup_stdin_pipe(t_data *x, t_list *tmp)
// {
// 	((t_cmdredir *) tmp->content)->fd_cmd[0] = x->fd_pipe[0];
// 	close(x->fd_pipe[0]);
// }

// void	ft_dup_stdout_pipe(t_data *x, t_list *tmp)
// {
// 	((t_cmdredir *)tmp->content)->fd_cmd[1] = x->fd_pipe[1];
// }


/*t_words *ft_init_words_kezako(char *word)
{
	t_words *new_cp_env;

	new_cp_env = malloc(sizeof(t_words));
	if (!new_cp_env)
		return (NULL);
	new_cp_env->word = ft_strdup(word);
	return (new_cp_env);
}

t_words *ft_init_words(char *word, int token)
{
	t_words *new_cp_env;
	(void)token;
	(void)word;

	new_cp_env = malloc(sizeof(t_words));
	// if (!new_cp_env)
	// 	return (NULL);
	// new_cp_env->word = ft_strdup(word);
	return (new_cp_env);
}*/


// t_list **ft_dupcmd(t_list *portion)
// {
//     t_list **dup;
//     t_list *new;

//     dup = malloc(sizeof(t_list*));
//     if (!dup)
//         return (NULL);
//     *dup = NULL;
//     if (!portion)
//         return (NULL);
//     while (portion)
//     {
//         // if (((t_words *)portion->content)->token == TOK_FRFR || ((t_words *)portion->content)->token == TOK_FROM || ((t_words *)portion->content)->token == TOK_TO || ((t_words *)portion->content)->token == TOK_TOTO)
//         //     portion = portion->next;
//         if ((((((t_words *)portion->content)->token != TOK_DOLL)) && (((t_words *)portion->content)->token != TOK_WORD)) && (!(portion->next->next)))
//             break; //C'est que y'as plus rien derriere a continuer d'organiser
//         if ( ((t_words *)portion->content)->token != TOK_WORD && ((t_words *)portion->next->content)->token == TOK_DOLL && ((t_words *)portion->next->next->content)->token == TOK_WORD && portion->next->next->next)
//             portion = portion->next->next->next;
//         if ( ((t_words *)portion->content)->token != TOK_WORD && ((t_words *)portion->next->content)->token == TOK_DOLL && ((t_words *)portion->next->next->content)->token == TOK_WORD)
//             break;
//         if ((((((t_words *)portion->content)->token != TOK_DOLL)) && ((t_words *)portion->content)->token != TOK_WORD) && portion->next->next)
//             portion = portion->next->next;
//         else
//         {
//             new = ft_lstnew((void *) words_init(((t_words *)portion->content)->word, ((t_words *)portion->content)->token));
//             dup = (t_list **)ft_lstadd_back2(dup, new);
//             portion = portion->next;
//         }
//         //portion = portion->next;
//     }
//     if (!(*dup))
//         (*dup) = ft_lstnew(NULL);
//}



// t_list **ft_dupredir(t_list *portion)
// {
//     t_list **dup;
//     t_list *new;
//     char *doll = NULL;
//     int     tok_doll;

//     tok_doll = 0;
//     dup = malloc(sizeof(t_list*));
//     if (!dup)
//         return (NULL);
//     *dup = NULL;
//     if (!portion)
//         return (NULL);
//     while (portion)
//     {
//         if (!(portion->next))
//             break;
// 		dprintf(2, "-----> %s\n", ((t_words *)portion->content)->word);
//         if (((t_words *)portion->content)->token != TOK_WORD && ((t_words *)portion->next->content)->token == TOK_DOLL)
//         {
// 			dprintf(2, "if 1=> %s\n", ((t_words *)portion->content)->word);
//             doll = ((t_words *)portion->next->next->content)->word;
//             tok_doll = ((t_words *)portion->next->next->content)->token;
//         }
//         if (((t_words *)portion->content)->token != TOK_WORD && ((t_words *)portion->content)->token != TOK_DOLL)
//         {
// 			dprintf(2, "if 2=> %s\n", ((t_words *)portion->content)->word);
//             new = ft_lstnew((void *) words_init(((t_words *)portion->content)->word, ((t_words *)portion->content)->token));
//             dup = (t_list **)ft_lstadd_back2(dup, new);
//             portion = portion->next;
//             new = ft_lstnew((void *) words_init(((t_words *)portion->content)->word, ((t_words *)portion->content)->token));
//             dup = (t_list **)ft_lstadd_back2(dup, new);
//             if (doll != NULL)
//             {
// 				dprintf(2, "je pass epar ici\n");
//                 new = ft_lstnew((void *) words_init(doll, tok_doll));
//                 dup = (t_list **)ft_lstadd_back2(dup, new);
//             }
//         }
//         portion = portion->next;
//     }
//     if (!(*dup))
//         (*dup) = ft_lstnew(NULL);
//     return (dup);
// }

// t_list **ft_dupppppppredir(t_list *portion)
// {
//     t_list **dup;
// 	  //  t_list *new;
//  //   char *doll = NULL;
//  //   int     tok_doll;

//   //  tok_doll = 0;
//     dup = malloc(sizeof(t_list*));
//     if (!dup)
//         return (NULL);
//     *dup = NULL;
//     if (!portion)
//         return (NULL);
//     while (portion)
//     {
//         if (!(portion->next))
//             break;
// 		//dprintf(2, "-----> %s\n", ((t_words *)portion->content)->word);
//         // if (((t_words *)portion->content)->token != TOK_WORD && ((t_words *)portion->next->content)->token == TOK_DOLL)
//         // {
// 		// 	dprintf(2, "if 1=> %s\n", ((t_words *)portion->content)->word);
//         //     doll = ((t_words *)portion->next->next->content)->word;
//         //     tok_doll = ((t_words *)portion->next->next->content)->token;
//         // }
//         if (((t_words *)portion->content)->token != TOK_WORD && ((t_words *)portion->content)->token != TOK_DOLL)
//         {
// 			dprintf(2, "if 2=> %s\n", ((t_words *)portion->content)->word);

//             // new = ft_lstnew((void *) words_init(((t_words *)portion->content)->word, ((t_words *)portion->content)->token));
//             // dup = (t_list **)ft_lstadd_back2(dup, new);
// 			*dup = ft_return_dupcmd(portion, *dup);
//             portion = portion->next;
// 			*dup = ft_return_dupcmd(portion, *dup);
//             // new = ft_lstnew((void *) words_init(((t_words *)portion->content)->word, ((t_words *)portion->content)->token));
//             // dup = (t_list **)ft_lstadd_back2(dup, new);
//             // if (doll != NULL)
//             // {
// 			// 	dprintf(2, "je pass epar ici\n");
//             //     new = ft_lstnew((void *) words_init(doll, tok_doll));
//             //     dup = (t_list **)ft_lstadd_back2(dup, new);
//             // }
//         }
//         portion = portion->next;
//     }
//     if (!(*dup))
//         (*dup) = ft_lstnew(NULL);
//     return (dup);
// }

// t_list **ft_dupcmd(t_list *portion)
// {
//     t_list **dup;
//     t_list *new;

//     dup = malloc(sizeof(t_list*));
//     if (!dup)
//         return (NULL);
//     *dup = NULL;
//     if (!portion)
//         return (NULL);
//     while (portion)
//     {
//         //dprintf(2, "~~~~~~ : %s\n", ((t_words *)portion->content)->word);
//         // if (((t_words *)portion->content)->token == TOK_FRFR || ((t_words *)portion->content)->token == TOK_FROM || ((t_words *)portion->content)->token == TOK_TO || ((t_words *)portion->content)->token == TOK_TOTO)
//         //     portion = portion->next;
//         if ((((((t_words *)portion->content)->token != TOK_DOLL)) && (((t_words *)portion->content)->token != TOK_WORD)) && (!(portion->next->next)))
// 			{
// 				dprintf(2, "je passe par ici");
// 				break; //C'est que y'as plus rien derriere a continuer d'organiser
// 			}
//         if ( ((t_words *)portion->content)->token != TOK_WORD && ((t_words *)portion->next->content)->token == TOK_DOLL && ((t_words *)portion->next->next->content)->token == TOK_WORD && portion->next->next->next)
//            {
// 				dprintf(2, "je passe par ici 2\n");
// 		    	portion = portion->next->next->next;
// 		   }
//         if ( ((t_words *)portion->content)->token != TOK_WORD && ((t_words *)portion->next->content)->token == TOK_DOLL && ((t_words *)portion->next->next->content)->token == TOK_WORD)
//             {
// 				dprintf(2, "je passe par ici 3\n");
// 				break;
// 			}
//         if ((((((t_words *)portion->content)->token != TOK_DOLL)) && ((t_words *)portion->content)->token != TOK_WORD) && portion->next->next)
//             {
// 				dprintf(2, "je passe par ici 4\n");
// 				portion = portion->next->next;
// 			}
//         else
//         {
// 			dprintf(2, "je passe par ici 5\n");
//             new = ft_lstnew((void *) words_init(((t_words *)portion->content)->word, ((t_words *)portion->content)->token));
//             dup = (t_list **)ft_lstadd_back2(dup, new);
//             portion = portion->next;
//         }
//         //portion = portion->next;
//     }
//     if (!(*dup))
//         (*dup) = ft_lstnew(NULL);
//     return (dup);
// }


//////////////////


// t_list	*ft_returnnnnn_dupcmd(t_list *portion, t_list *dup)
// {
// 	t_list **tmp_dup;
// 	t_list *new;

// 	tmp_dup = &dup;
// 	new = ft_lstnew((void *) words_init(((t_words *)portion->content)->word,
// 		((t_words *)portion->content)->token));
// 	tmp_dup = (t_list **)ft_lstadd_back2(tmp_dup, new);
// 	return (*tmp_dup);
// }

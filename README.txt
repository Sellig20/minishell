# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    README.txt                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: evsuits <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/22 18:50:56 by evsuits           #+#    #+#              #
#    Updated: 2022/08/22 19:21:56 by evsuits          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

------------------------------------CHEVRON-----------------------------------
> ne peux pas etre suivi de rien 
		->Erreur (bash: syntax error near unexpected token 'newline')
> ne peux pas etre suivi d'un dossier 
		->Erreur (bash: repo_name/: Is a diretory)





------------------------------------BUILD-IN-----------------------------------

1. ECHO (option -n):

l'option -n equivaut a l'option -nnnnnnnnnnnnnnnnnnnnnn et copie les arguments suivant sur stdout. Si pas d'arguments rien est copier mais le fichier de reception est ouvert si necessaire.
echo prends autant d'argument que tu veux (texte a copier)

s'il est suivi d'un > le stdout est transforme au fd suivant le >




2. CD:
cd prend UN argument (PATH absolu ou relatif)
		->Erreur si mauvaise lecture de fichier (No Such file or directory / Permission denied)
		->Erreur si trop d'arguments (too many arguments)



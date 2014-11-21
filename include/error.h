/*
** error.h for  in /home/collio_v/rendu_svn/42.sh/42
**
** Made by vincent colliot
** Login   <collio_v@epitech.net>
**
** Started on  Sat May  4 12:44:30 2013 vincent colliot
** Last update Thu May 23 14:52:51 2013 vincent colliot
*/

#ifndef ERROR_H_
# define ERROR_H_

# define UNMATCHED_TOKEN "(sh): unexpected EOS while looking for matching `"
# define ERROR_AFTER_ECHAP_CHAR "(sh): unexpected EOS after echappment character"
# define UNMATCHED_PARENTS "(sh): unexpected EOS while looking for matching `)'"
# define UNMATCHED_BACKMACHIN "(sh): syntax error near unexpected token ``'"
# define ERROR_NEAR_TOKEN "(sh): syntax error near unexpected token: "
# define ERROR_NEAR_PARENTS "(sh): syntax error near unexpected token: )"
# define UNKNOW_CMD "(sh): command not found : "
# define WRONG_SEP_TOKEN "(sh): syntax error near unexpected token `"
# define WRONG_REDIR "(sh): wrong redirection"
# define ERROR_IN_REDIR "(sh): unexpected EOS after redirection"
# define FILE_ERROR "(sh): no such file: "
# define DIR_ERROR "(sh): no such directory: "
# define IS_DIR_ERROR1 "(sh):error : "
# define IS_DIR_ERROR2 " : is a directory"
# define INVALID_ALIAS "(sh): alias error: invalid character in sentence: "

#endif

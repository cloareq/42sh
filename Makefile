## Makefile for make_my in /u/all/collio_v/rendu/piscine/Jour_13/cat
##
## Made by vincent colliot
## Login   <collio_v@epitech.net>
##
## Started on Thu Oct 25 22:06:03 2012 vincent colliot
## Last update Sun May 26 11:11:48 2013 pierre-yves thomas
##

NAME    = Sla.sh

RM      = rm -f

FO	=./

SRCF	=$(FO)src/

########################

DIRF	=$(SRCF)directory/
DIR	=$(DIRF)directory_in.c

EXECF	=$(SRCF)exec/
EXEC	=$(EXECF)exec.c\
	$(EXECF)begin_exec.c\
	$(EXECF)to_tab.c\
	$(EXECF)exec_form.c\
	$(EXECF)pré-exec.c\
	$(EXECF)redir.c\
	$(EXECF)redir_d_left.c

ENVF	=$(SRCF)env/
ENV	=$(ENVF)get_env.c

XMALLOC=$(LIBF)xmalloc.c\

LIBF	=$(SRCF)lib/
LIB	=$(LIBF)s_alloc.c\
	$(LIBF)my_getnbr.c\
	$(LIBF)s_match.c\
	$(LIBF)s_comp.c\
	$(LIBF)s_lenth.c\
	$(LIBF)s_print.c\
	$(LIBF)match.c\
	$(LIBF)s_history.c\
	$(LIBF)s_memset.c\

XLIBF	=$(SRCF)xlib/
XLIB	=$(XLIBF)xfork.c\

MAINF	=$(SRCF)main/
MAIN	=$(MAINF)main.c\

PARSF	=$(SRCF)parsing/
PARS	=$(PARSF)subdiv.c\
	$(PARSF)echappment.c\
	$(PARSF)comment.c\
	$(PARSF)get_next_line.c\
	$(PARSF)alias.c\
	$(PARSF)var.c\
	$(PARSF)hist.c

PROMPTF	=$(SRCF)prompt/
PROMPT	=$(PROMPTF)prompt.c\

SCANF	=$(SRCF)scan_file/
SCAN	=$(SCANF)scan.c

###### Parsing #########

ORGAF	=$(SRCF)organize/

CMDF	=$(ORGAF)cmd/
CMD	=$(CMDF)cmd.c\
	$(CMDF)seek_cmd.c\
	$(CMDF)list_cmd.c\
	$(CMDF)cmd_part.c\
	$(CMDF)interpret_cmd.c\
	$(CMDF)interpret_params.c\
	$(CMDF)redir.c

JEXEF	=$(ORGAF)jobs_exec/
JEXE	=$(JEXEF)exec.c\
	$(JEXEF)jobs.c\
	$(JEXEF)match_them.c\
	$(JEXEF)match_them_help.c

ORJF	=$(ORGAF)orga/
ORJ	=$(ORJF)orga.c\
	$(ORJF)parenthesys.c\

NULLF	=$(ORGAF)nullify/
NULL	=$(NULLF)null1.c\
	$(NULLF)null2.c\
	$(NULLF)null3.c\

PIPEF	=$(ORGAF)pipe/
PIPE	=$(PIPEF)pipes.c\

ORGA	=$(CMD)\
	$(JEXE)\
	$(ORJ)\
	$(PIPE)\
####### EDIT-LINE ######

EDITF	=$(SRCF)edit_line/

FED_AFF	=$(EDITF)aff_cmd/
ED_AFF	=$(FED_AFF)show_cmd.c\

FED_GET	=$(EDITF)get_cmd/
ED_GET	=$(FED_GET)read_cmds.c\

FED_HIST=$(EDITF)history/
ED_HIST	=$(FED_HIST)take_cmd_from_history.c\

FED_MOD	=$(EDITF)modif_cmd/
ED_MOD	=$(FED_MOD)auto_completion.c\
	$(FED_MOD)change_reverse_place.c\
	$(FED_MOD)clean_screen.c\
	$(FED_MOD)edit_line.c\
	$(FED_MOD)finish_usr_cmd.c\
	$(FED_MOD)load_term_settings.c\
	$(FED_MOD)modify_line.c\
	$(FED_MOD)move_to_word_fct.c\
	$(FED_MOD)reverse_to_begin_end.c\
	$(FED_MOD)save_and_copy_part_str.c\
        $(FED_MOD)swap_chars_on_cmd.c\
        $(FED_MOD)upper_lower_case_letters.c\

FED_SAVE=$(EDITF)save_datas/
ED_SAVE	=$(FED_SAVE)remain_datas.c\

FED_SIG	=$(EDITF)signals/
ED_SIG	=$(FED_SIG)configure_signals.c\

EDIT	=$(ED_AFF)\
	$(ED_GET)\
	$(ED_HIST)\
	$(ED_MOD)\
	$(ED_SAVE)\
	$(ED_SIG)\

###### BUILTS-IN #######

BUILTF	=$(SRCF)builtins/

FALIAS	=$(BUILTF)alias/
ALIAS	=$(FALIAS)alias.c\
	$(FALIAS)mod_alias.c\
	$(FALIAS)unalias.c\

FECHO	=$(BUILTF)echo/
ECHO	=$(FECHO)my_echo.c\
	$(FECHO)seq.c\

FCD	=$(BUILTF)cd/
CD	=$(FCD)cd.c\

FENV	=$(BUILTF)env/
B_ENV	=$(FENV)env_cmd.c\
	$(FENV)env_exec.c\
	$(FENV)env_copy.c\

FEXIT	=$(BUILTF)exit/
EXIT	=$(FEXIT)exit.c

FSET	=$(BUILTF)setenv/
BSET	=$(FSET)setenv.c\

FUSET	=$(BUILTF)unsetenv/
BUSET	=$(FUSET)unsetenv.c\

CALLF	=$(BUILTF)call/
CALL	=$(CALLF)parse_built.c\

BUILT_IN=$(ALIAS)\
	$(ECHO)\
	$(CD)\
	$(B_ENV)\
	$(EXIT)\
	$(BSET)\
	$(BUSET)\
	$(CALL)

########################

SRC     =$(MAIN)\
	$(LIB)\
	$(PARS)\
	$(XMALLOC)\
	$(ORGA)\
	$(NULL)\
	$(ENV)\
	$(EDIT)\
	$(DIR)\
	$(XLIB)\
	$(EXEC)\
	$(BUILT_IN)\
	$(PROMPT)\
	$(SCAN)\

########################

INC	=-I $(FO)include/ -lncurses

CFLAGS	= -Wall -Wextra $(INC)

DOTO    = $(SRC:.c=.o)

all: $(NAME)

.c.o:
	@ $(CC) $(CFLAGS) -c -o $@ $< \
	&& echo -e "[\e[35mGCC\e[m]\e[33m" $< "\e[m=>\e[36m" $@ "\e[m" \
	|| echo -e "[\e[35mGCC\e[m]\e[33m" $< "\e[m=>" "\e[31mERROR\e[m"

$(NAME): $(DOTO)
	@ cc -o $(NAME) $(DOTO) $(CFLAGS)
	@ echo -e "\e[32m"$(NAME)"\e[m" "is alive !"
	@ echo -e "\e[37mActivated CFLAGS :\e[m" $(CFLAGS)

debug: fclean
	cc -o $(NAME) $(SRC) $(INC) -g3

clean:
	$(RM) $(DOTO)

fclean: clean
	$(RM) $(NAME)

re: fclean all clean
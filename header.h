#ifndef HEADER_H
#define HEADER_H
#include <stddef.h>
#include <stddef.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

/* r/w buff */
#define R_BUFF_S 1024
#define W_BUFF_S 1024
#define BUFF_FL -1

/* cmd chaining */
#define CMD_N	0
#define CMD_O		1
#define CMD_A		2
#define CMD_C	3

/* num converter */
#define CONV_L	1
#define CONV_U	2

/* 1 getline() */
#define USE_G 0
#define USE_S 0

#define HST_F	".simple_shell_history"
#define HST_M	4096

extern char **environ;


/**
 * struct llstr - singly linked list
 * @num: number field
 * @str: string
 * @next: points to next node
 */
typedef struct llstr
{
	int num;
	char *str;
	struct llstr *next;
} lstt;
/**
 *struct pinfo - pseudo-arguements to pass into a function,
 *              allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: string path for the current command
 *@argc: argument count
 *@err_c: error count
 *@errcfe: error code for exit()s
 *@lcf: if on count this line of input
 *@fname: program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: history node
 *@alias: alias node
 *@envc: on if environ was changed
 *@sts: return sts of last exec'd command
 *@c_b: address of pointer to c_b, on if chaining
 *@cbt: CMD_type ||, &&, ;
 *@rdfd: fd from which to read line input
 *@hstc: history line number count
 */
typedef struct pinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int err_c;
	int errcfe;
	int lcf;
	char *fname;
	lstt *env;
	lstt *history;
	lstt *alias;
	char **environ;
	int envc;
	int sts;

	char *c_b; /* pointer to cmd ; chain buffer, for memory mangement */
	int cbt; /* CMD_type ||, &&, ; */
	int rdfd;
	int hstc;
} inft;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - string and related function
 *@type: builtin command flag
 *@func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(inft *);
} blt_t;


/* cmdloop.c */
int msl(inft, char *);
int fbuild(inft *);
void fcmd(inft *);
void fkcmd(inft *);

/* parser.c */
int is_cmd(inft *, char *);
char *dp_c(char *, int, int);
char *f_path(inft *, char *, char *);

/* cmdsh.c */
int loophsh(char **);

/* errors.c */
void pais(char *);
int w_to_stdr(char);
int wc_to_fd(char c, int fd);
int pains(char *str, int fd);

/* str.c */
int str_l(char *);
int str_c(char *, char *);
char *starts_with(const char *, const char *);
char *con_s(char *, char *);

/* string1.c */
char *str_copy(char *, char *);
char *dupl_str(const char *);
void p_inp_str(char *);
int w_to_std_out(char);

/* exit.c */
char *str_cpys(char *, char *, int);
char *con_too_str(char *, char *, int);
char *lcis(char *, char);

/* tkn.c */
char **str_spl_2(char *, char *);
char **str_spl(char *, char);

/* rlc.c */
char *fmwcb(char *, char, unsigned int);
void fsos(char **);
void *rabom(void *, unsigned int, unsigned int);

/* mem.c */
int fr_p_a(void **);

/* atoi.c */
int inter(inft *);
int dlm(char, char *);
int alph(int);
int cnv(char *);

/* errors1.c */
int str_to_int(char *);
void p_error(inft *, char *);
int p_d_num(int, int);
char *conv_num(long int, int, int);
void rm_comm(char *);

/* built.c */
int mexit(inft *);
int mcd(inft *);
int mhelp(inft *);

/* built1.c */
int myhistory(inft *);
int myaliases(inft *);

/*getl.c */
ssize_t g_inp(inft *);
int g_ln(inft, char *, size_t *);
void b_cntr_c(int);

/* geti.c */
void clr_inf(inft *);
void s_inf(inft, char *);
void fr_inf(inft *, int);

/* env.c */
char *g_env_v(inft *, const char *);
int p_cur_v(inft *);
int init_envv_or_m(inft *);
int raev(inft *);
int pell(inft *);

/* gete.c */
char **rsa_of_env(inft *);
int mr_env_v(inft *, char *);
int init_new_env(inft *, char *, char *);

/* history.c */
char *g_hst_f(inft *info);
int w_hst(inft *info);
int r_hst(inft *info);
int b_hst_l(inft *info, char *buf, int linecount);
int remu_hst(inft *info);

/* list.c */
lstt *an_so_l(lstt *, const char *, int);
lstt *an_endo_l(lstt *, const char *, int);
size_t p_ostr_ll(const lstt *);
int del_n_i(lstt **, unsigned int);
void f_lst(lstt **);

/* list1.c */
size_t len_lst(const lstt *);
char **arr_of_str(lstt *);
size_t p_all_ll(const lstt *);
lstt *nsw(lstt *, char *, char);
ssize_t gion(lstt *, lstt *);

/* vrs.c */
int is_cd(inft *, char *, size_t *);
void ckc(inft *, char *, size_t *, size_t, size_t);
int r_al(inft *);
int r_vrs(inft *);
int r_str(char **, char *);

#endif

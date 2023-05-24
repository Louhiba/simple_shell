#include "header.h"

/**
 * input_buf - the buffers chained cmd
 * @info: the param struct
 * @buf: the addr of buffer
 * @len: the addr of len var
 *
 * Return: the bytes read
 */
ssize_t input_buf(inft *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* nothing left in buffer, fill it */
	{
		/*fr_p_a((void **)info->c_b);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, b_cntr_c);
#if USE_G
		r = getline(buf, &len_p, stdin);
#else
		r = g_ln(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* rm trailing newline */
				r--;
			}
			info->lcf = 1;
			rm_comm(*buf);
			b_hst_l(info, *buf, info->hstc++);
			/* if (lcis(*buf, ';')) is this a cmd chain? */
			{
				*len = r;
				info->c_b = buf;
			}
		}
	}
	return (r);
}

/**
 * g_inp - get the line minus newline
 * @info: the param struct
 *
 * Return: the bytes read
 */
ssize_t g_inp(inft *info)
{
	static char *buf; /* the ';' cmd chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	w_to_std_out(BUFF_FL);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* we have cmd left in the chain buffer */
	{
		j = i; /* init new iterator to the current buf position */
		p = buf + i; /* get the pointer for return */

		ckc(info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_cd(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* to increment past nulled ';'' */
		if (i >= len) /* reached the end of buffer? */
		{
			i = len = 0; /* reset the position and length */
			info->cbt = CMD_N;
		}

		*buf_p = p; /* pass back the pointer to the current cmd position */
		return (str_l(p)); /* return length of the current cmd */
	}

	*buf_p = buf; /* else not chain, pass back the buffer from g_ln() */
	return (r); /* return the length of buffer from g_ln() */
}

/**
 * read_buf - read buffer
 * @info: param struct
 * @buf: the buffer
 * @i: the size
 *
 * Return: the var r
 */
ssize_t read_buf(inft *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->rdfd, buf, R_BUFF_S);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * g_ln - get next line of the input from STDIN
 * @info: param struct
 * @ptr: the addr of pointer to the buffer, preallocated or NULL
 * @length: the size of preallocated ptr buffer if not NULL
 *
 * Return: the var s
 */
int g_ln(inft *info, char **ptr, size_t *length)
{
	static char buf[R_BUFF_S];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = lcis(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = rabom(p, s, s ? s + k : k + 1);
	if (!new_p) /* the MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		con_too_str(new_p, buf + i, k - i);
	else
		str_cpys(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * b_cntr_c - the blocks ctrl-C
 * @sig_num: signal number
 *
 * Return: void func
 */
void b_cntr_c(__attribute__((unused))int sig_num)
{
	p_inp_str("\n");
	p_inp_str("$ ");
	w_to_std_out(BUFF_FL);
}

#include <errno.h>
#include "shell.h"
#include "source.h"

/** unget_char - returns the last character retrieved from input back to the input source
 * @src: pointer to the source
 * Return: returns input string
 */
void unget_char(struct source_s *src)
{
	if (src->curpos < 0)
	{
		return;
	}

	src->curpos--;
}

/**
 * next_char - returns the next character input and updates the source pointer
 * @src: source pointer
 *
 * Return: the next character
 */
char next_char(struct source_s *src)
{
	if (!src || !src->buffer)
	{
		errno = ENODATA;
		return (ERRCHAR);
	}

	char c1 = 0;
	if (src->curpos == INIT_SRC_POS)
	{
		src-.curpos = -1;
	}
	else
	{
		c1 = src->buffer[src->curpos];
	}

	if (++src->curpos >= src->bufsize)
	{
		src->curpos = src->bufsize;
		return (EOF);
	}

	return (src->buffer[src->curpos]);
}

/**
 * peek_char - returns next character of input
 * @src: input source
 *
 * Return: returns the next input character
 */
char peek_char(struct source_s *src)
{
	if (!src || !src->buffer)
	{
		errno = ENODATA;
		return (ERRCHAR);
	}

	long pos = src->curpos;

	if (pos == INIT_SRC_POS)
	{
		pos++;
	}
	pos++;

	if (pos >= src->bufsize)
	{
		return (EOF);
	}

	return (src->buffer[pos]);
}

/**
 * skip_white_spaces - skips all white spaces
 * @src: input source
 *
 * Return: void
 */
void skip_white_spaces(struct source_s *src)
{
	char c;

	if (!src || !src->buffer)
	{
		return;
	}

	while (((c = peek_char(src)) != EOF) && (c == ' ' || c == '\t'))
	{
		next_char(src);
	}
}

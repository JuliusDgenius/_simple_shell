#ifndef SCANNER_H
#define SCANNER_H

/**
 * struct token_s - structure of token input
 * @src: pointer to source input
 * @text_len: length of token text
 * @text: token text
 */
struct token_s
{
	/* struct source_s - source of input */
	struct source_s *src;		/* source of input */
	int	text_len;		/* length of token text */
	char	*text;		/* token text */
};

/* special token to indicate end of file */
extern struct token_s eof_token;

/**
 * tokenize - retrieves the next token from input
 * @src: pointer to the source holding input
 *
 * Return: returns the next token from input
 */
struct token_s *tokenize(struct source_s *src);

/**
 * free_token - frees token memory
 * @tok: pointer to token
 * Return: void
 */
void free_token(struct token_s *tok);

#endif

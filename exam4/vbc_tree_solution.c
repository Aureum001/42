/*
 * VBC - Tree-based solution (using the intended structures from given.c)
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node {
	enum {
		ADD,
		MULTI,
		VAL
	}   type;
	int val;
	struct node *l;
	struct node *r;
}   node;

/* Provided functions from given.c */
node    *new_node(node n)
{
	node *ret = calloc(1, sizeof(n));
	if (!ret)
		return (NULL);
	*ret = n;
	return (ret);
}

void    destroy_tree(node *n)
{
	if (!n)
		return ;
	if (n->type != VAL)
	{
		destroy_tree(n->l);
		destroy_tree(n->r);
	}
	free(n);
}

void    unexpected(char c)
{
	if (c)
		printf("Unexpected token '%c'\n", c);
	else
		printf("Unexpected end of input\n");
}

int accept(char **s, char c)
{
	if (**s == c)
	{
		(*s)++;
		return (1);
	}
	return (0);
}

int expect(char **s, char c)
{
	if (accept(s, c))
		return (1);
	unexpected(**s);
	return (0);
}

int eval_tree(node *tree)
{
	switch (tree->type)
	{
		case ADD:
			return (eval_tree(tree->l) + eval_tree(tree->r));
		case MULTI:
			return (eval_tree(tree->l) * eval_tree(tree->r));
		case VAL:
			return (tree->val);
	}
	return (0);
}

/* ========== YOUR CODE STARTS HERE ========== */

/* Forward declarations */
node *factor(char **s);
node *term(char **s);
node *expression(char **s);

/* Parse a factor: digit or (expression)
 * 
 * Grammar: factor → digit | '(' expression ')'
 * 
 * Examples:
 * - "5" → VAL node with val=5
 * - "(2+3)" → parse the expression inside
 */
node *factor(char **s)
{
	node *result;

	/* Case 1: It's a digit */
	if (isdigit(**s))
	{
		char digit = **s;
		(*s)++;
		if (isdigit(**s))
		{
			unexpected(**s);
			return (NULL);
		}
		/* Create a VALUE node with the digit */
		result = new_node((node){
			.type = VAL,
			.val = digit - '0'
		});
		if (!result)
			return (NULL);
		return (result);
	}
	
	/* Case 2: It's (expression) */
	if (**s == '(')
	{
		(*s)++;  /* Consume '(' */
		result = expression(s);  /* Parse the expression inside */
		if (!result)
			return (NULL);
		if (!expect(s, ')'))  /* Must have closing ')' */
		{
			destroy_tree(result);
			return (NULL);
		}
		return (result);
	}
	/* Unexpected character */
	unexpected(**s);
	return (NULL);
}

/* Parse a term: factor (* factor)*
 * 
 * Grammar: term → factor (('*') factor)*
 * 
 * Handles multiplication with proper left-to-right evaluation
 * 
 * Examples:
 * - "3*4" → MULTI node with l=3, r=4
 * - "2*3*4" → MULTI(MULTI(2,3),4) = ((2*3)*4)
 */
node *term(char **s)
{
	node *left = factor(s);  /* Parse first factor */
	if (!left)
		return (NULL);

	/* While we see '*', keep building MULTI nodes */
	while (**s == '*')
	{
		(*s)++;  /* Consume '*' */
		
		node *right = factor(s);  /* Parse next factor */
		if (!right)
		{
			destroy_tree(left);
			return (NULL);
		}
		
		/* Create MULTI node: left * right */
		left = new_node((node){
			.type = MULTI,
			.l = left,
			.r = right
		});
		if (!left)
		{
			destroy_tree(right);
			return (NULL);
		}
		/* Now 'left' is the MULTI node, loop continues */
	}
	return (left);
}

/* Parse an expression: term (('+') term)*
 * 
 * Grammar: expression → term (('+') term)*
 * 
 * Handles addition with proper left-to-right evaluation
 * 
 * Examples:
 * - "2+3" → ADD node with l=2, r=3
 * - "1+2+3" → ADD(ADD(1,2),3) = ((1+2)+3)
 * - "2*3+4*5" → ADD(MULTI(2,3), MULTI(4,5))
 */
node *expression(char **s)
{
	node *left = term(s);  /* Parse first term */
	if (!left)
		return (NULL);

	/* While we see '+', keep building ADD nodes */
	while (**s == '+')
	{
		(*s)++;  /* Consume '+' */
		
		node *right = term(s);  /* Parse next term */
		if (!right)
		{
			destroy_tree(left);
			return (NULL);
		}
		
		/* Create ADD node: left + right */
		left = new_node((node){
			.type = ADD,
			.l = left,
			.r = right
		});
		if (!left)
		{
			destroy_tree(right);
			return (NULL);
		}
		/* Now 'left' is the ADD node, loop continues */
	}
	return (left);
}

/* Main parser function
 * 
 * Parses the entire string and ensures nothing is left over
 */
node *parse_expr(char *s)
{
	node *ret = expression(&s);
	
	if (!ret)
		return (NULL);
	/* Check if we consumed the entire string */
	if (*s)  /* Something left unparsed */
	{
		unexpected(*s);
		destroy_tree(ret);
		return (NULL);
	}
	return (ret);
}

/* ========== YOUR CODE ENDS HERE ========== */

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	node *tree = parse_expr(argv[1]);
	if (!tree)
		return (1);
	printf("%d\n", eval_tree(tree));
	destroy_tree(tree);
	return (0);
}

/*
 * EXAMPLE TRACE: "2+3*4"
 * 
 * parse_expr("2+3*4")
 *   → expression(&s)
 *     → term(&s)  // s = "2+3*4"
 *       → factor(&s)
 *         → sees '2', creates VAL(2), s = "+3*4"
 *         → returns VAL(2)
 *       → sees '+' (not '*'), returns VAL(2)
 *     → left = VAL(2), s = "+3*4"
 *     → sees '+', consume it, s = "3*4"
 *     → term(&s)  // s = "3*4"
 *       → factor(&s)
 *         → sees '3', creates VAL(3), s = "*4"
 *         → returns VAL(3)
 *       → left = VAL(3), sees '*', consume it, s = "4"
 *       → factor(&s)
 *         → sees '4', creates VAL(4), s = ""
 *         → returns VAL(4)
 *       → creates MULTI(VAL(3), VAL(4)), s = ""
 *       → returns MULTI(VAL(3), VAL(4))
 *     → right = MULTI(VAL(3), VAL(4))
 *     → creates ADD(VAL(2), MULTI(VAL(3), VAL(4)))
 *     → s = "", no more '+', returns tree
 *   → s = "" (consumed all), returns tree
 * 
 * Tree structure:
 *       ADD
 *      /   \
 *    VAL   MULTI
 *     2    /   \
 *        VAL  VAL
 *         3    4
 * 
 * eval_tree(tree):
 *   ADD: eval(VAL(2)) + eval(MULTI(VAL(3), VAL(4)))
 *      = 2 + (3 * 4)
 *      = 2 + 12
 *      = 14
 * 
 * Output: 14
 */

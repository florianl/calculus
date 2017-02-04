%{
        #include "calculus.h"
%}
TXT_GCD         [Gg][Cc][Dd]
TXT_LCM         [Ll][Cc][Mm]
CONST_PI        [Pp][Ii]
DIGIT_BIN       [01]
DIGIT_OCT       [0-7]
DIGIT_DIGIT     [0-9]
DIGIT_HEX       [0-9a-fA-F]
SIGN_BIN        [bB]
SIGN_OCT        [oO]
SIGN_HEX        [xX]
NUM_BIN         {SIGN_BIN}{DIGIT_BIN}+
NUM_OCT         {SIGN_OCT}{DIGIT_OCT}+
NUM_DIG         [1-9]{DIGIT_DIGIT}*
NUM_HEX         {SIGN_HEX}{DIGIT_HEX}+
WHITESPACE      [ \t]*
%option prefix="calculus_"
%option warn
%option noyywrap
%option nounput
%option noinput
%%
{TXT_GCD}               {return _CALCULUS_FUNC_GCD;}
{TXT_LCM}               {return _CALCULUS_FUNC_LCM;}
{CONST_PI}              {return _CALCULUS_CONST_PI;}
{NUM_BIN}               {return _CALCULUS_NUM_BIN;}
{NUM_OCT}               {return _CALCULUS_NUM_OCT;}
{NUM_DIG}               {return _CALCULUS_NUM_DIG;}
{NUM_HEX}               {return _CALCULUS_NUM_HEX;}
("("|"["|"{")?          {return _CALCULUS_BRACE_OPEN;}
(")"|"]"|"}")?          {return _CALCULUS_BRACE_CLOSE;}
("+")?                  {return _CALCULUS_ADD;}
("-")?                  {return _CALCULUS_SUB;}
("*")?                  {return _CALCULUS_MUL;}
("/")?                  {return _CALCULUS_DIV;}
("^")?                  {return _CALCULUS_POW;}
{WHITESPACE}            /*      Ignore whitespaces              */
[\n]                    {return -1;}
.                       /*      Eat up unrecognized patterns    */
%%

int parse (unsigned int flags)
{
        stack_t         *values = NULL;
        stack_t         *operators = NULL;
        int             type = -1;
        int             inum = 0;
        void            *mem;
        int             *iptr;
        _d("\n");

        values = calloc (1, sizeof(stack_t));
        operators = calloc (1, sizeof(stack_t));

        yyin = stdin;

        while (1)
        {
                type = calculus_lex ();
                _d ("%2d %s\n", (int) calculus_leng, calculus_text);
                if (type == -1)
                {
                        _d ("\n");
                        break;
                } else if ((type & _CALCULUS_CONST_MASK) == type)
                {
                        _d ("\n");
                        stackPush (&values, NULL, type);
                } else if ((type & _CALCULUS_FUNC_MASK) == type)
                {
                        _d ("\n");
                        stackPush (&operators, NULL, type);
                } else if ((type & _CALCULUS_OP_MASK) == type)
                {
                        _d ("\n");
                        stackPush (&operators, NULL, type);
                } else if ((type & _CALCULUS_ORG_MASK) == type)
                {
                        if (type == _CALCULUS_BRACE_OPEN)
                                stackPush (&operators, NULL, type);
                        _d ("\n");
                } else if ((type & _CALCULUS_NUM_MASK) == type)
                {
                        switch (type)
                        {
                                case _CALCULUS_NUM_BIN:
                                        _d ("bin\n");
                                        type = _CALCULUS_INT;
                                        inum = bin2dez(calculus_text);
                                        break;
                                case _CALCULUS_NUM_OCT:
                                        _d ("oct\n");
                                        type = _CALCULUS_INT;
                                        inum = uni2dez(calculus_text, 8);
                                        break;
                                case _CALCULUS_NUM_DIG:
                                        _d ("dig\n");
                                        type = _CALCULUS_INT;
                                        inum = atoi(calculus_text);
                                        break;
                                case _CALCULUS_NUM_HEX:
                                        _d ("hex\n");
                                        type = _CALCULUS_INT;
                                        inum = hex2dez(calculus_text);
                                        break;
                                default:
                                        _d ("unkown\n");
                                        type = 0xBADC0DE;
                                        inum = -1;
                                        break;
                        }
                        if ((type & _CALCULUS_INT) == type)
                        {
                                mem = calloc(1, sizeof(int));
                                iptr = (int*) mem;
                                *iptr = inum;
                        } else {
                                break;
                        }
                        stackPush (&values, mem, type);
                } else {
                        _d ("\n");
                        fprintf (stderr, "Unknown input [%d]: %s\n", type, calculus_text);
                        break;
                }
        }

        stackFree (&operators);
        stackFree (&values);

        return 0;
}

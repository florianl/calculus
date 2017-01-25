%{
        #include "calculus.h"
%}
TXT_GCD         [Gg][Cc][Dd]
TXT_LCM         [Ll][Cc][MM]
DIGIT_BIN       [01]
DIGIT_OCT       [0-7]
DIGIT_DIGIT     [0-9]
DIGIT_HEX       [0-9a-fA-F]
SIGN_BIN        [bB]
SIGN_OCT        [cC]
SIGN_HEX        [xX]
NUM_BIN         {SIGN_BIN}{DIGIT_BIN}+
NUM_OCT         {SIGN_OCT}{DIGIT_OCT}+
NUM_DIG         [1-9]{DIGIT_DIGIT}*
NUM_HEX         {SIGN_HEX}{DIGIT_HEX}+
WHITESPACE      [ \t]*
%option prefix="calculus_"
%option warn
%option noyywrap
%%
{TXT_GCD}               {return _CALCULUS_FUNC_GCD;}
{TXT_LCM}               {return _CALCULUS_FUNC_LCM;}
{NUM_BIN}               {return _CALCULUS_NUM_BIN;}
{NUM_OCT}               {return _CALCULUS_NUM_OCT;}
{NUM_DIG}               {return _CALCULUS_NUM_DIG;}
{NUM_HEX}               {return _CALCULUS_NUM_HEX;}
("("|"["|"{")?          {return _CALCULUS_BRACE_OPEN;}
(")"|"]"|"}")?          {return _CALCULUS_BRACE_CLOSE;}
{WHITESPACE}            /*      Ignore whitespaces              */
[\n]                    {return -1;}
.                       /*      Eat up unrecognized patterns    */
[\0]                    {fprintf(stderr, "EoW\n");}
%%

int parse (unsigned int flags)
{
        stack_t         *values = NULL;
        stack_t         *operators = NULL;
        int             type = -1;
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
                } else if ((type & _CALCULUS_FUNC_MASK) == type)
                {
                        _d ("\n");
                } else if ((type & _CALCULUS_ORG_MASK) == type)
                {
                        _d ("\n");
                } else if ((type & _CALCULUS_NUM_MASK) == type)
                {
                        switch (type)
                        {
                                case _CALCULUS_NUM_BIN:
                                        _d ("bin\n");
                                        break;
                                case _CALCULUS_NUM_OCT:
                                        _d ("oct\n");
                                        break;
                                case _CALCULUS_NUM_DIG:
                                        _d ("dig\n");
                                        break;
                                case _CALCULUS_NUM_HEX:
                                        _d ("hex\n");
                                        break;
                                default:
                                        _d ("unkown\n");
                                        break;
                        }
                
                } else {
                        _d ("\n");
                        fprintf (stderr, "Unknown input [%d]: %s\n", type, calculus_text);
                        break;
                }
        }

        return 0;
}

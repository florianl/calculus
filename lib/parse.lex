%{
        #include "parse.h"
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
NUM_DIG         {DIGIT_DIGIT}*
NUM_HEX         {SIGN_HEX}{DIGIT_HEX}+
WS              [ \t]*
%option prefix="calculus_"
%option warn
%option noyywrap
%option nounput
%option noinput
%%
{TXT_GCD}{WS}("("|"["|"{")?     {return _CALCULUS_FUNC_GCD;}
{TXT_LCM}{WS}("("|"["|"{")?     {return _CALCULUS_FUNC_LCM;}
{CONST_PI}                      {return _CALCULUS_CONST_PI;}
{NUM_DIG}(","|"."){NUM_DIG}?    {return _CALCULUS_NUM_REAL;}
{NUM_BIN}                       {return _CALCULUS_NUM_BIN;}
{NUM_OCT}                       {return _CALCULUS_NUM_OCT;}
{NUM_DIG}                       {return _CALCULUS_NUM_DIG;}
{NUM_HEX}                       {return _CALCULUS_NUM_HEX;}
("("|"["|"{")?                  {return _CALCULUS_BRACE_OPEN;}
(")"|"]"|"}")?                  {return _CALCULUS_BRACE_CLOSE;}
("+")?                          {return _CALCULUS_ADD;}
("-")?                          {return _CALCULUS_SUB;}
("*")?                          {return _CALCULUS_MUL;}
("/")?                          {return _CALCULUS_DIV;}
("^"|"*"{WS}"*")?               {return _CALCULUS_POW;}
(";")?                          {return _CALCULUS_SEPERATOR;}
("!")?                          {return _CALCULUS_NUM_FACTORIAL;}
{WS}                            /*      Ignore whitespaces              */
[\n]                            {return -1;}
.                               /*      Eat up unrecognized patterns    */
%%

int parse (unsigned int flags, double *result, const char *pattern)
{
        stack_t         *values = NULL;
        stack_t         *operators = NULL;
        int             type = -1;
        int             inum = 0;
        int             topOp = 0;
        double          dnum = 0.0;
        int             noe = 0;
        void            *mem;
        double          *ptr;
        char            *s = NULL;
        size_t          len = strlen(pattern);
        _d("\n");

        values = calloc (1, sizeof(stack_t));
        values->type = 0xBADC0DE;
        operators = calloc (1, sizeof(stack_t));
        operators->type = 0xBADC0DE;

        s = (char*) calloc(len+2, sizeof(char));
        if (!s)
                return -1;
        s = strncpy(s, pattern, len);
        s[len] = '\n';

        yy_switch_to_buffer(yy_scan_string(s));

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
                        topOp = stackTop(operators);
                        if ((topOp & _CALCULUS_POINT_OP) == topOp)
                        {
                                _d ("0x%x\n", topOp);
                                applyOperation(&values, topOp);
                                stackPop(&operators);
                        }
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
                        {
                                _d ("\n");
                                stackPush (&operators, NULL, type);
                        } else if (type == _CALCULUS_BRACE_CLOSE)
                        {
                                _d ("\n");
                                topOp = stackTop(operators);
                                applyOperation(&values, topOp);
                                stackPop(&operators);
                        } else {
                                _d ("\n");
                        }
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
                                case _CALCULUS_NUM_REAL:
                                        _d ("real\n");
                                        type = _CALCULUS_DOUBLE;
                                        dnum = strtod(calculus_text, NULL);
                                        _d ("%f\n", dnum);
                                        break;
                                case _CALCULUS_NUM_FACTORIAL:
                                        _d ("factorial\n");
                                        type = _CALCULUS_DOUBLE;
                                        if (getValue(&values, &dnum) < 0)
                                                cleanLeave(0, &operators, &values);
                                        if (factorial(dnum, &dnum) < 0)
                                                cleanLeave(0, &operators, &values);
                                        break;
                                default:
                                        _d ("unkown\n");
                                        type = 0xBADC0DE;
                                        inum = -1;
                                        break;
                        }
                        if ((type & _CALCULUS_INT) == type)
                        {
                                mem = (void*) calloc(1, sizeof(double));
                                ptr = (double*) mem;
                                *ptr = (inum * 1.0);
                                type = _CALCULUS_DOUBLE;
                        } else if ((type & _CALCULUS_DOUBLE) == type)
                        {
                                mem = (void*) calloc(1, sizeof(double));
                                ptr = (double*) mem;
                                *ptr = dnum;
                        } else {
                                _d ("\n");
                                break;
                        }
                        stackPush (&values, mem, type);

                        topOp = stackTop(operators);
                        if ((topOp & _CALCULUS_POINT_OP) == topOp)
                        {
                                _d ("0x%x\n", topOp);
                                applyOperation(&values, topOp);
                                stackPop(&operators);
                        }
                } else {
                        _d ("\n");
                        fprintf (stderr, "Unknown input [%d]: %s\n", type, calculus_text);
                        break;
                }
        }

        yy_delete_buffer(YY_CURRENT_BUFFER);

        topOp = stackTop(operators);
        while(topOp != 0xBADC0DE)
        {
                applyOperation(&values, topOp);
                stackPop(&operators);
                topOp = stackTop(operators);
        }
        stackFree (&operators);

        topOp = stackTop(values);
        noe = 0;
        while(topOp != 0xBADC0DE)
        {
                noe++;
                if (getValue(&values, &dnum) < 0)
                        return -1;
                topOp = stackTop(values);
        }
        stackFree (&values);

        free(s);

        if(noe != 1)
        {
                fprintf(stderr, "Invalid Number of elements.\n");
                return -1;
        } else {
                *result = dnum;
        }
        return 0;
}

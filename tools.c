#include "calculus.h"

/**
 * Remove all items from the stack.
 **/
int stackFree (stack_t **s)
{
        stack_t         *item = *s;
        stack_t         *next;
        int             progress = 0;
#ifdef CALCULUS_DEBUG
        double          *ptr;
#endif

        while (item)
        {
                next = item->next;
                if (item->value != NULL)
                {
#ifdef CALCULUS_DEBUG
                        if(item->type == _CALCULUS_DOUBLE)
                        {
                                ptr = (item->value);
                                _d("%f\n", (double) *ptr);
                        }
#endif
                        free ((void*)item->value);
                }
                item->type = 0xBADC0DE;
                free (item);
                progress++;
                item = next;
        }

        return progress;
}

/**
 * Get the type of the top item from the stack.
 **/
unsigned int stackTop (stack_t *s)
{
        return s->type;
}

/**
 * Save an item on the stack.
 **/
int stackPush (stack_t **s, void *value, unsigned int type)
{
        stack_t         *item;
#ifdef CALCULUS_DEBUG
        double          *ptr;
#endif

        item = (stack_t*) calloc (1, sizeof(stack_t));
        if (!item)
        {
                _d ("%s\n", strerror (errno));
                return -1;
        }

        item->value = value;
        item->type = type;
        item->next = *s;

#ifdef CALCULUS_DEBUG
        if(item->type == _CALCULUS_DOUBLE)
        {
                ptr = (item->value);
                _d ("%f\n", (double) *ptr);
        }
#endif

        *s = item;

        return 0;
}

/**
 * Get the top item from the stack.
 **/
void *stackPop (stack_t **s)
{
        stack_t         *item = *s;
        void            *value = item->value;

        *s = item->next;
        free (item);
        return value;
}

/**
 * Convert a binary-value from char to its integer correspondent.
 **/
int bin2dez(char *t)
{
        int             value = 0;
        int             power = 1;
        int             len = strlen(t);
        int             i = 0;

        if (len<2)
                return -1;

        for (i=len-1; i>=1; i--)
        {
                if (t[i] == '1')
                {
                        value += power;
                }
                power <<= 1;
        }

        return value;
}

/**
 * Convert a value from char to its integer correspondent.
 * $multi represents the factor for the transformation.
 **/
int uni2dez(char *t, int multi)
{
        int             value = 0;
        int             power = 1;
        int             len = strlen(t);
        int             i = 0;

        if (len<2)
                return -1;

        for (i=len-1; i>=1; i--)
        {
                value += (t[i] - 48) * power;
                power *= multi;
        }

        return value;
}

/**
 * Convert a hex-value from char to its integer correspondent.
 **/
int hex2dez(char *t)
{
        int             value = 0;
        int             power = 1;
        int             len = strlen(t);
        int             i = 0;
        int             element = 0;


        if (len<2)
                return -1;

        for (i=len-1; i>=1; i--)
        {
                if ( t[i] <= 57 && t[i] >= 48)
                        /*      numbers                 */
                        element = t[i] - 48;
                else if ( t[i] <= 70 && t[i] >= 65)
                        /*      uppercase letters       */
                        element = t[i] - 55;
                else if ( t[i] <= 102 && t[i] >= 97)
                        /*      lowercase letters       */
                        element = t[i] - 87;
                else
                        break;
                value += element * power;
                power *= 16;
        }

        return value;
}

/**
 * Get the top value from the stack.
 **/
int getValue(stack_t **s, double *ret)
{
        int             type = 0;
        double          *ptr;

        type = stackTop(*s);
        _d ("0x%x\n", type);
        if (type == _CALCULUS_DOUBLE)
        {
                ptr = (double *) stackPop(s);
                *ret = *ptr;
        }
        else if (type == _CALCULUS_CONST_PI)
        {
                *ret = 3.141592;
        } else
        {
                return -1;
        }

        return 0;
}

/**
 * Factorial calculation
 **/
int factorial(double a, double *f)
{
        double          b = 0;

        if (a == 0)
        {
                *f = a;
                return 0;
        }

        /**
         * It works just for positive integers
         **/
        if ((a - ((int) a)  != 0.0) || (a < 0))
        {
                _d ("%f is not a positive integer.\n", a);
                return -1;
        }

        b = a;
        while(a > 1)
        {
                a -= 1.0;
                _d ("%f * %f\n", b,a);
                b = b * a;
        }
        *f = b;

        return 0;
}

/**
 * GCD calculation based on euclidean algorithm
 **/
int euclideanGCD(double a, double b, double *f)
{
        if (a == 0)
        {
                *f = b;
                return 0;
        }

        while (b != 0)
        {
                if (a >b)
                {
                        a = a - b;
                } else
                {
                        b = b - a;
                }
        }
        *f = a;

        return 0;
}

/**
 * Apply an operation to a stack.
 **/
int applyOperation(stack_t **s, int op)
{
        double          x = 0.0;
        double          y = 0.0;
        double          z = 0.0;
        void            *mem;
        double          *ptr;

        if (getValue(s, &y) < 0)
                return -1;
        _d ("y = %f\n", y);
        if (getValue(s, &x) < 0)
                return -1;
        _d ("x = %f\n", x);

        switch(op)
        {
                case _CALCULUS_ADD:
                        z = x + y;
                        break;
                case _CALCULUS_SUB:
                        z = x - y;
                        break;
                case _CALCULUS_MUL:
                        z = x * y;
                        break;
                case _CALCULUS_DIV:
                        z = x / y;
                        break;
                case _CALCULUS_FUNC_GCD:
                        euclideanGCD(x,y, &z);
                        break;
                case _CALCULUS_FUNC_LCM:
                        euclideanGCD(x,y, &z);
                        z = (x*y)/z;
                        break;
                default:
                        _d ("unknown operation 0x%x\n", op);
                        return -1;
        }
        mem = (void*) calloc(1, sizeof(double));
        ptr = (double*) mem;
        *ptr = z;
        stackPush (s, mem, _CALCULUS_DOUBLE);

        return 0;
}

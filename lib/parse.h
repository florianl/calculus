#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define _CALCULUS_OP_MASK               0xFF01
#define _CALCULUS_ADD                   0x0101
#define _CALCULUS_SUB                   0x0201
#define _CALCULUS_POINT_OP              0xF001
#define _CALCULUS_MUL                   0x1001
#define _CALCULUS_DIV                   0x2001
#define _CALCULUS_POW                   0x4001

#define _CALCULUS_ORG_MASK              0xFF02
#define _CALCULUS_BRACE_OPEN            0x0102
#define _CALCULUS_BRACE_CLOSE           0x0202
#define _CALCULUS_SEPERATOR             0x0402

#define _CALCULUS_FUNC_MASK             0xFF04
#define _CALCULUS_FUNC_GCD              0x0104
#define _CALCULUS_FUNC_LCM              0x0204

#define _CALCULUS_NUM_MASK              0xFF08
#define _CALCULUS_NUM_BIN               0x0108
#define _CALCULUS_NUM_OCT               0x0208
#define _CALCULUS_NUM_DIG               0x0408
#define _CALCULUS_NUM_HEX               0x0808
#define _CALCULUS_NUM_REAL              0x1008
#define _CALCULUS_NUM_FACTORIAL         0x2008

#define _CALCULUS_TYPE_MASK             0xFF10
#define _CALCULUS_INT                   0x0110
#define _CALCULUS_DOUBLE                0x0210

#define _CALCULUS_CONST_MASK            0xFF20
#define _CALCULUS_CONST_PI              0x0120

//#define CALCULUS_DEBUG
/**
 *      This is a very simple way, to do debugging.
 **/
#ifdef CALCULUS_DEBUG
        #define _d(...)         {fprintf (stderr, "%s():%d\t", __func__, __LINE__); \
                                        fprintf (stderr, __VA_ARGS__);}
#else
        #define _d(...)         {do { } while (0);}
#endif

/**
 * Universal struct for different stacks.
 **/
typedef struct stack {
        void            *value;
        unsigned int    type;
        struct stack    *next;
} stack_t;

int stackFree (stack_t **s);
void *stackPop (stack_t **s);
int stackPush (stack_t **s, void *value, unsigned int type);
unsigned int stackTop (stack_t *s);

int bin2dez(char *t);
int hex2dez(char *t);
int uni2dez(char *t, int multi);

int factorial(double a, double *f);

int applyOperation(stack_t **s, int op);
int getValue(stack_t **s, double *ret);
int cleanLeave(int err, stack_t **s, stack_t **t);
int handleBrackets(stack_t **o, stack_t **v);

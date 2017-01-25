#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>


#define _CALCULUS_ORG_MASK              0xFF02
#define _CALCULUS_BRACE_OPEN            0x0102
#define _CALCULUS_BRACE_CLOSE           0x0202


#define _CALCULUS_FUNC_MASK             0xFF04
#define _CALCULUS_FUNC_GCD              0x0104
#define _CALCULUS_FUNC_LCM              0x0204

#define _CALCULUS_NUM_MASK              0xFF08
#define _CALCULUS_NUM_BIN               0x0108
#define _CALCULUS_NUM_OCT               0x0208
#define _CALCULUS_NUM_DIG               0x0408
#define _CALCULUS_NUM_HEX               0x0808


#define CALCULUS_DEBUG

#ifdef CALCULUS_DEBUG
        #define _d (...)         {fprintf (stderr, "%s():%d\t", __func__, __LINE__); \
                                        fprintf (stderr, __VA_ARGS__);}
#else
        #define _d (...)         {do { } while (0);}
#endif

typedef struct stack {
        void            *value;
        unsigned int    type;
        struct stack    *next;
} stack_t;

int parse (unsigned int flags);

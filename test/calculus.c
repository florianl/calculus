#include <stdlib.h>
#include <stdio.h>
#include <calculus.h>

int main (int argc, char **argv)
{
        unsigned int            flags = 0;
        double                  result = 0.0;

        if (parse (flags, &result, "1 + 2") == 0)
        {
                fprintf(stdout, "%f\n", result);
        }
        if (parse (flags, &result, "1 * 2") == 0)
        {
                fprintf(stdout, "%f\n", result);
        }
        if (parse (flags, &result, "1 / 2") == 0)
        {
                fprintf(stdout, "%f\n", result);
        }
        if (parse (flags, &result, "2 ** 2") == 0)
        {
                fprintf(stdout, "%f\n", result);
        }
        if (parse (flags, &result, "gcd(7 21)") == 0)
        {
                fprintf(stdout, "%f\n", result);
        }
        if (parse (flags, &result, "lcm(7 22)") == 0)
        {
                fprintf(stdout, "%f\n", result);
        }
        if (parse (flags, &result, "3*3+3*(2+2+2)") == 0)
        {
                fprintf(stdout, "%f\n", result);
        }
        if (parse (flags, &result, "3*3+3(2+2+2)") == 0)
        {
                fprintf(stdout, "%f\n", result);
        }


        return EXIT_SUCCESS;
}

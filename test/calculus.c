#include <stdlib.h>
#include <stdio.h>
#include <calculus.h>

int main (int argc, char **argv)
{
        unsigned int            flags = 0;
        double                  result = 0.0;
        char                    input[256];

        sprintf(input, "1 + 2");
        if (parse (flags, &result, input) == 0)
        {
                fprintf(stdout, "%s = %f\n", input, result);
        }
        sprintf(input, "1 * 2");
        if (parse (flags, &result, input) == 0)
        {
                fprintf(stdout, "%s = %f\n", input, result);
        }
        sprintf(input, "1 / 2");
        if (parse (flags, &result, input) == 0)
        {
                fprintf(stdout, "%s = %f\n", input, result);
        }
        sprintf(input, "2 ** 2");
        if (parse (flags, &result, input) == 0)
        {
                fprintf(stdout, "%s = %f\n", input, result);
        }
        sprintf(input, "gcd(7 21)");
        if (parse (flags, &result, input) == 0)
        {
                fprintf(stdout, "%s = %f\n", input, result);
        }
        sprintf(input, "lcm(7 22)");
        if (parse (flags, &result, input) == 0)
        {
                fprintf(stdout, "%s = %f\n", input, result);
        }
        sprintf(input, "fib(7)");
        if (parse (flags, &result, input) == 0)
        {
                fprintf(stdout, "%s = %f\n", input, result);
        }
        sprintf(input, "3*3+3*(2+2+2)");
        if (parse (flags, &result, input) == 0)
        {
                fprintf(stdout, "%s = %f\n", input, result);
        }
        sprintf(input, "3*3+3(2+2+2)");
        if (parse (flags, &result, input) == 0)
        {
                fprintf(stdout, "%s = %f\n", input, result);
        }
        sprintf(input, "0xF * 0xF");
        if (parse (flags, &result, input) == 0)
        {
                fprintf(stdout, "%s = %f\n", input, result);
        }
        sprintf(input, "0xF + 0xF");
        if (parse (flags, &result, input) == 0)
        {
                fprintf(stdout, "%s = %f\n", input, result);
        }
        sprintf(input, "0xF ** 0xF");
        if (parse (flags, &result, input) == 0)
        {
                fprintf(stdout, "%s = %f\n", input, result);
        }
        sprintf(input, "0xF * b110");
        if (parse (flags, &result, input) == 0)
        {
                fprintf(stdout, "%s = %f\n", input, result);
        }
        sprintf(input, "0xF");
        if (parse (flags, &result, input) == 0)
        {
                fprintf(stdout, "%s = %f\n", input, result);
        }
        sprintf(input, "xFFFF");
        if (parse (flags, &result, input) == 0)
        {
                fprintf(stdout, "%s = %f\n", input, result);
        }
        sprintf(input, "b110");
        if (parse (flags, &result, input) == 0)
        {
                fprintf(stdout, "%s = %f\n", input, result);
        }
        sprintf(input, "b110 * b111");
        if (parse (flags, &result, input) == 0)
        {
                fprintf(stdout, "%s = %f\n", input, result);
        }
        sprintf(input, "b110 ** b111");
        if (parse (flags, &result, input) == 0)
        {
                fprintf(stdout, "%s = %f\n", input, result);
        }
        sprintf(input, "0xFF / b100");
        if (parse (flags, &result, input) == 0)
        {
                fprintf(stdout, "%s = %f\n", input, result);
        }
        return EXIT_SUCCESS;
}

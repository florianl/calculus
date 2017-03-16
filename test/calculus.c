#include <stdlib.h>
#include <calculus.h>

int main (int argc, char **argv)
{
        unsigned int            flags = 0;

        parse (flags, "1 + 2");
        parse (flags, "1 * 2");
        parse (flags, "1 / 2");
        parse (flags, "1 ** 2");
        parse (flags, "gcd(7 21)");
        parse (flags, "lcm(7 22)");

        return EXIT_SUCCESS;
}

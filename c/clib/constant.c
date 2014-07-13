#include <stdio.h>

int main()
{
    double R_Zero = 0.0;
    double R_PosInf = 1.0/R_Zero;
    double R_NegInf = -1.0/R_Zero;
    double R_Nan = R_Zero/R_Zero;

    printf("%f\n", R_Zero);
    printf("%f\n", R_PosInf);
    printf("%f\n", R_NegInf);
    printf("%f\n", R_Nan);
    return 0;
}


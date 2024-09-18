int power(int b, int e)
{
    if (e == 0)
    {
        b = 1;
    }

    else if (e > 0)
    {
        for (int i = 0; i < (e-1); i++)
        {
            b = b * b;
        }
    }

    return b;
}
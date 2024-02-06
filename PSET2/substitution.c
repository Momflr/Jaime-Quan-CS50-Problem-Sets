#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char makelower(char x);
int main(int argc, string argv[])
{
    // validate key
    if (argc != 2)
    {
        printf("Usage: ./subsitution key\n");
        return 1;
    }
    int keylength = strlen(argv[1]);
    string key = argv[1];
    if (keylength != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0; i < keylength; i++)
    {
        if (isalpha(key[i]))
        {
            if (isupper(key[i]))
            {
                key[i] = makelower(key[i]);
            }
            for (int o = 0; o < keylength; o++)
            {
                if (i != o)
                {
                    if (key[i] == key[o])
                    {
                        printf("Characters must not be repeated.\n");
                        return 1;
                    }
                }
            }
        }
        else
        {
            printf("Key must be completely alphabetic.\n");
            return 1;
        }
    }
    // ask for input
    string plaintext = get_string("Plaintext: ");
    // encipher
    for (int i = 0, plaintextlength = strlen(plaintext); i <= plaintextlength; i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                int o = plaintext[i] - 65;
                plaintext[i] = key[o] - 32;
            }
            else
            {
                int o = plaintext[i] - 97;
                plaintext[i] = key[o];
            }
        }
    }
    printf("ciphertext: %s\n", plaintext);
}

char makelower(char x)
{
    return x + 32;
}

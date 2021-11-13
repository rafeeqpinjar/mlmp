#include<stdlib.h>
#include<math.h>
#include<string.h>
long int gcd(long int a, long int b)
{
if(a == 0)
return b;
if(b == 0)
return a;
return gcd(b, a%b);
}
long int isprime(long int a)
{
int i;
for(int i = 2; i < a; i++)
{

if(a%i == 0)
return 0;
}
return 1;
}
long int encrypt(long int ch, long int n, long int e)
{
long int i,temp = ch;
for(i = 1; i < e; i++)
{
temp = (temp * ch) % n;
}
return temp;
}
long int decrypt(long int ch, long int n, long int d)
{
long int i,temp = ch;
for(i = 1; i < d; i++)
{
temp = (temp * ch) % n;
}
return temp;
}
int main()
{
long int i;
int len;
long int p, q, n, phi, e, d, cipher[50];
char text[50];
printf("Enter the text to be encrypted:\n");
scanf("%s",text);
len = strlen(text);
do {
p = rand() % 30;
} while (!isprime(p));
do {
q = rand() % 30;
} while (!isprime(q));

n = p * q;
phi = (p - 1) * (q - 1);
do {
e = rand() % phi;
} while (gcd(phi, e) != 1);
do {
d = rand() % phi;
} while (((d * e) % phi) != 1);
printf("Two prime numbers (p and q) are: %ld and %ld\n", p,q);
printf("n(p * q) = %ld * %ld = %ld", p, q, p*q);
printf("(p - 1) * (q - 1) = %ld\n", phi);
printf("Public key (n, e): (%ld, ,%ld)\n",n,e);
printf("Private key (n, d): (%ld, %ld)\n", n, d);
for (i = 0; i < len; i++)
cipher[i] = encrypt(text[i], n, e);
printf("Encrypted message: \n");
for (i = 0; i < len; i++)
printf("%ld", cipher[i]);
for (i = 0; i < len; i++)
text[i] = decrypt(cipher[i], n, d);
printf("\n");
printf("Decrypted message: \n");
for (i = 0; i < len; i++)
printf("%c", text[i]);
printf("\n");
return 0;
}

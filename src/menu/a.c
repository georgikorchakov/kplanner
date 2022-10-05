#include <stdio.h>

struct b
{
  char *a;
};

void asd(char *s)
{
  struct b str;
  str.a = s;
  struct b *strp = &str;

  printf("String = %s\n", strp->a);
}

int main()
{

  asd("Hello world");

  return 0;
}

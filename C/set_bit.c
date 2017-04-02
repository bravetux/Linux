#include <stdio.h>
int set_field(int ovalue, int nvalue, int offset, int width);

int main()
{
 int result;

  result = set_field(0x0349b829, 5, 18, 4);
  printf("Res: %x \n",result);

  return 0;
}
int set_field(int ovalue, int nvalue, int offset, int width)
{
        int mask, field, result;
        mask = ( 1 << width) - 1;
        field = (~(mask << offset)) & ovalue;
        result = field | (nvalue << offset);
        return result;
}


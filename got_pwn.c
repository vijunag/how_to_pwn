#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void *_GLOBAL_OFFSET_TABLE_;


int main()
{
  char buf[100], buf1[100];
  void *strcpy_plt = &strncpy;
  unsigned long long a1, a2;

  strncpy(buf,"Hello!", sizeof(buf));

  strncpy(buf1, "/bin/sh", sizeof(buf1));

  system("touch vnag");
  printf("strcpy_plt addr :%p\n",strcpy_plt);
  printf("GOT=%p, &GOT=%p\n", _GLOBAL_OFFSET_TABLE_, &_GLOBAL_OFFSET_TABLE_);
  printf("strcpy@plt:%p\n", (void*)(((unsigned long long)_GLOBAL_OFFSET_TABLE_)+0x18));
  printf("Address at strcpy:%p\n",(void*)*(unsigned long long*)(((unsigned long long)_GLOBAL_OFFSET_TABLE_)+0x18));
  printf("%s%s\n",buf,buf1);

  printf("Enter address of strncpy@plt\n");
  scanf("%p", (void **)&a1);
//  printf("strcpy.got@plt: %p\n",(void*)a1);
  printf("Enter address of system@plt\n");
  scanf("%p", (void **)&a2);

  *(unsigned long long*)a1 = *(unsigned long long*)a2;
  strncpy(buf1,"touch vnag1",sizeof(buf1));
  printf("Hello world\n");
}

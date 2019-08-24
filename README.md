# CSE-406-Computer-Security 

ASLR:

sysctl -a --pattern 'randomize'

to change it to 0 => sudo sysctl -w kernel.randomize_va_space=0

`gcc -z execstack -fno-stack-protector -o stack buffer_overflow_user_input.c`

`sudo chown root stack`
`sudo chmod 4755 stack`

`gcc -g -z execstack -fno-stack-protector -o objfile_name buffer_overflow_user_input.c`

`gdb --nx objfile_name`

breakpoint set using -> `b func_name`
then run using -> `run`

address of something -> `p &var_name`, `p $ebp` for stack pointer

ls -l /bin | grep sh

sudo ln -sf /bin/zsh /bin/sh
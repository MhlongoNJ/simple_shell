#include "shell.h"

/**
* _my_exit - this function exits out of the shell
* @info: the Structure that is containing potential arguments. Used to maintain
*          constant function prototypes.
*  Return: exits with a given exit status
*         (0) if info.argv[0] != "exit"
*/

int _my_exit(info_t *info)

{
int exitcheck;

if (info->argv[1])

{
exitcheck = _conv_str_int(info->argv[1]);
if (exitcheck == -1)

{
info->status = 2;
print_error(info, "Illegal number: ");
_eputs(info->argv[1]);
_eputchar('\n');
return (1);
}

info->err_num = _conv_str_int(info->argv[1]);
return (-2);
}

info->err_num = -1;
return (-2);
}

/**
* _my_cd -  this function changes current directory of a process
* @info: Structure that is containing potential arguments.
* that are Used to maintain
*          constant function prototype.
*  Return: Always 0
*/

int _my_cd(info_t *info)

{
char *s, *dir, buffer[1024];
int chdir_ret;
s = getcwd(buffer, 1024);
if (!s)
_puts("TODO: >>getcwd failure emsg here<<\n");
if (!info->argv[1])
{
dir = _getenv(info, "HOME=");
if (!dir)
chdir_ret =
chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
else
chdir_ret = chdir(dir);
}
else if (_strcmp(info->argv[1], "-") == 0)
{
if (!_getenv(info, "OLDPWD="))
{
_puts(s);
_putchar('\n');
return (1);
}
_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
chdir_ret =
chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
}
else
chdir_ret = chdir(info->argv[1]);
if (chdir_ret == -1)
{
print_error(info, "can't cd to ");
_eputs(info->argv[1]), _eputchar('\n');
}
else
{
_setenv(info, "OLDPWD", _getenv(info, "PWD="));
_setenv(info, "PWD", getcwd(buffer, 1024));
}
return (0);
}

/**
* _my_help - this function changes current directory of a process
* @info: the Structure which is containing potential arguments.
* that are Used to maintain
*          constant function prototype.
*  Return: Always 0
*/

int _my_help(info_t *info)
{
char **arg_array;
arg_array = info->argv;
_puts("help call works. Function not yet implemented \n");
if (0)
_puts(*arg_array);
return (0);
}

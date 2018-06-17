#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_CMD 32

struct cmd_line_t{
    int argc;
    char *argv[MAX_CMD];
};

struct cmd_line_t g_cmd_arg;
char g_cmd_line[MAX_LINE+1];
char g_av_line[MAX_LINE+1];
char g_pwd[128+1];
char g_host_name[128+1];
char g_login[128+1];

void init();
void clear();
void shell_loop();
int cmd_read();
int cmd_parser();
int cmd_execute();

#endif

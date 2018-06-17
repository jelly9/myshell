#include "parser.h"

static void sig_init(){
    signal(SIGINT, SIG_IGN);
//    signal(SIGQUIT, SIG_IGN);
}

//初始化信号
static void print_g_cmd_arg(){
    int i = 0;
    printf("argument count: %d\n", g_cmd_arg.argc);
    printf("argument value: ");
    while(g_cmd_arg.argv[i] != NULL)
        printf("%s ", g_cmd_arg.argv[i++]);
    printf("\n");
}

//初始化程序
void init(){
    //初始化信号
    sig_init();
    //初始化接收缓冲区
    clear();
    //初始化命令行提示符
    memset(g_pwd, 0x00, 128+1);
    memset(g_host_name, 0x00, 128+1);
    memset(g_login, 0x00, 128+1);
    getcwd(g_pwd, 128);
    gethostname(g_host_name, 128);
    getlogin_r(g_login, 128);
}

void clear(){
    memset(g_cmd_line, 0x00, MAX_CMD+1);
    memset(g_av_line, 0x00, MAX_CMD+1);
}

//shell
void shell_loop(){
    while(1){
        printf("%s@%s: %s# ", g_login, g_host_name, g_pwd);
        clear();
        if(cmd_read() == 0) break;
        cmd_parser();
        print_g_cmd_arg();
        cmd_execute();
    }

}

//读取命令
int cmd_read(){
    return fgets(g_cmd_line, MAX_LINE, stdin) == NULL ? 0 : 1;
}

//解析命令
int cmd_parser(){
    char *pCur = g_cmd_line;
    char *pPre = g_av_line;
    
    g_cmd_arg.argc = 0;
    while(*pCur != '\0'){
        while(*pCur != '\0' && (*pCur == ' ' || *pCur == '\n')){
            pCur++;
        }
        if(*pCur == '\0') return 0;
        g_cmd_arg.argv[g_cmd_arg.argc++] = pPre;
        while(*pCur != ' ' && *pCur != '\n' && *pCur != '\0' && *pCur != '\t') {
            *pPre++ = *pCur++;
        }
        *pPre++ = '\0';
    }
    g_cmd_arg.argv[g_cmd_arg.argc++] = NULL;

    return 0;
}

//执行命令
int cmd_execute(){
    if(fork() == 0){
        execvp(g_cmd_arg.argv[0], g_cmd_arg.argv);
        exit(EXIT_FAILURE);
    }
    wait(NULL);
    return 0;
}

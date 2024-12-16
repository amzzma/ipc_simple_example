#include "msg_type.h"
#include <stdio.h>

void get_msg_arg(struct msg * m);
void prase_ret_msg(struct msg * m);

int main(void)
{
    struct msg m;
    int qid;
    int pid;

    pid = getpid();
    qid = msgget(KEY, 0777|IPC_CREAT);
    printf("pid=%d, qid=%d\n", pid, qid);

    m.mtype=1;
    m.send_pid=pid;
    strcpy(m.text, "Hello Server :)");
    get_msg_arg(&m);
    
    if (msgsnd(qid, &m, mlen, 0) == -1) {
        perror("msgsnd");
        exit(1);
    }
    msgrcv(qid, &m, mlen, pid, 0);

    prase_ret_msg(&m);

    return 0;
}

void get_msg_arg(struct msg * m)
{
    printf("mode: func_name:\n");
    scanf("%d %d", &m->mode, &m->func_name);
    if(&m->mode == 0)
    {
        m->func_name=-1;
        return;
    }
    for(int i=0; i < m->mode; ++i) 
    {
        scanf("%lf", &m->arg_list[i]);
    }
    printf("get ok\n");
}
void prase_ret_msg(struct msg * m)
{
    printf("-----------------\n");
    printf("return text:\n%s\n", m->text);
    printf("return num(status=%d): \n", m->status);
    for (int i = 0; i < m->status; ++i) 
    {
        printf("%lf ", m->ret_num[i]);
    }
    printf("\n-----------------\n");
}
#include "msg_type.h"
#include <stdio.h>
#include "utils.h"

void service_handle(struct msg *m);
void tri_op(struct msg *m, enum func_name fn, double *arg_list);
void di_op(struct msg *m, enum func_name fn, double *arg_list);
void mono_op(struct msg *m, enum func_name fn, double *arg_list);

int main(void)
{
    struct msg m;
    int qid;
    int pid;

    pid = getpid();
    qid = msgget(KEY, 0666 | IPC_CREAT);
    printf("pid=%d, qid=%d\n", pid, qid);

    while (1)
    {
        printf("wait\n");
        msgrcv(qid, &m, mlen, 1, 0);
        printf("receive from pid=%d: text=%s\n", m.send_pid, m.text);

        m.mtype = m.send_pid;
        m.send_pid = pid;
        service_handle(&m);

        msgsnd(qid, &m, mlen, 0);
    }

    return 0;
}

void service_handle(struct msg *m)
{
    /*
        mode = 0: return Hello
        mode = 1: mono op
        mode = 2: di op
        mode = 3: tri op
    */

    if (m->mode == 3)
    {
        tri_op(m, m->func_name, m->arg_list);
    }
    else if (m->mode == 2)
    {
        di_op(m, m->func_name, m->arg_list);
    }
    else if (m->mode == 1)
    {
        mono_op(m, m->func_name, m->arg_list);
    }
    else if (m->mode == 0)
    {
        sprintf(m->text, "Hello, this server, pid=%d.", m->send_pid);
        m->status = 0;
    }
    else
    {
        strcpy(m->text, "error: not this op");
        m->status = -1;
    }
}
void tri_op(struct msg *m, enum func_name fn, double *arg_list)
{
    if (fn == solve_quadratic_equation)
    {
        printf("solve_quadratic_equation\n");
        solve_quadratic_equation_func(m, arg_list);
    }
    else
    {
        strcpy(m->text, "error: not this function");
        m->status = -1;
    }
}
void di_op(struct msg *m, enum func_name fn, double *arg_list)
{
    if (fn == find_prime)
    {
        printf("find_prime\n");
        find_prime_func(m, arg_list);
    }
    else
    {
        strcpy(m->text, "error: not this function");
        m->status = -1;
    }
}
void mono_op(struct msg *m, enum func_name fn, double *arg_list)
{
    if (fn == prime_factors)
    {
        printf("find_prime\n");
        prime_factors_func(m, arg_list);
    }
    else
    {
        strcpy(m->text, "error: not this function");
        m->status = -1;
    }
}

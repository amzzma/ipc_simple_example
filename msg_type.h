#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <string.h>
#include <stdlib.h>


#ifndef MSG_TYPE_H
#define MSG_TYPE_H

#define KEY 8888
#define MAX_MSGS 10

struct msg
{
    long mtype;
    pid_t send_pid;
    char text[128];

    int mode;
    int func_name;
    int status;
    double arg_list[10];
    double ret_num[100];
    
};

static int mlen = sizeof(struct msg) - sizeof(long);

enum func_name
{
    solve_quadratic_equation,  // ax^2 + bx + c = 0
    find_prime, // [min, max]
    prime_factors, // number
};

#endif
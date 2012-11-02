#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dbs_basopr.h"

T_DbsEnv *gptDbsEnv = NULL;

int main(int argc, char *argv[])
{
    gptDbsEnv = dbsConnect("aicdb", "Tiger", "haha");
    if (gptDbsEnv == NULL) {
        fprintf(stderr, "dbsConnect Failed!\n");
        return -1;
    }

    dbsDisconnect(gptDbsEnv);

    return 0;
}


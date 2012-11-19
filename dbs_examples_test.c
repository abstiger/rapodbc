#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dbs_basopr.h"

T_DbsEnv *dbsenv = NULL;

static int dbsRuleCur_test(T_DbsEnv *dbsenv);
static int dbsDatasrcFieldDefSel_test(T_DbsEnv *dbsenv);

int main(int argc, char *argv[])
{
    char  hszDBName[128];
    char  hszDBUser[128];
    char  hszDBPass[32];

    if (getenv("DBUSER") != NULL) {    
        strncpy(hszDBUser, getenv("DBUSER"), sizeof(hszDBUser));
    }
    if (getenv("DBPASS") != NULL) {    
        strncpy(hszDBPass, getenv("DBPASS"), sizeof(hszDBPass));
    }
    if (getenv("DBNAME") != NULL) {    
        strncpy(hszDBName, getenv("DBNAME"), sizeof(hszDBName));
    }

    printf("DBNAME:[%s], DBUSER:[%s], DBPASS:[%s].\n", \
            hszDBName, hszDBUser, hszDBPass);

    dbsenv = dbsConnect(hszDBName, hszDBUser, hszDBPass);
    if (dbsenv == NULL) {
        fprintf(stderr, "dbsConnect Failed!\n");
        return -1;
    }

    dbsRuleCur_test(dbsenv);
    dbsDatasrcFieldDefSel_test(dbsenv);

    dbsDisconnect(dbsenv);
    return 0;
}


int dbsRuleCur_test(T_DbsEnv *dbsenv)
{
#include "rule_cur.h"
    int nRet = 0;
    int iResult = 0;
    int iCnt = 0;
    T_RuleCur stRuleCur = {0};
    T_RuleCur *ptRuleCur = &stRuleCur;

    dbsRuleCur(dbsenv, KR_DBCUROPEN, &stRuleCur);

    while(1)
    {
        iResult=dbsRuleCur(dbsenv, KR_DBCURFETCH, &stRuleCur);
        if (iResult != KR_DBNOTFOUND && iResult != KR_DBOK) {
            fprintf(stderr, "dbsRuleCur Fetch Error[%d]!\n", iResult);
            nRet = -1;
            break;
        } else if (iResult == KR_DBNOTFOUND) {
            printf("Get [%d] Rules Totally!\n", iCnt);
            break;
        }

        printf("  lRuleId=[%ld], caRuleName=[%s], caRuleDesc=[%s], caRuleType=[%s] \n", ptRuleCur->lOutRuleId, ptRuleCur->caOutRuleName, ptRuleCur->caOutRuleDesc, ptRuleCur->caOutRuleType);
        printf("  lRuleWeight=[%ld], caThreshIsConfig=[%s] \n", ptRuleCur->lOutRuleWeight, ptRuleCur->caOutThreshIsConfig);
        printf("  caRuleString=[%s] \n", ptRuleCur->caOutRuleString);

        iCnt++;
    }

    dbsRuleCur(dbsenv, KR_DBCURCLOSE, &stRuleCur);

    return nRet;
}


int dbsDatasrcFieldDefSel_test(T_DbsEnv *dbsenv)
{
#include "datasrc_field_def_sel.h"
    int iResult = 0;
    T_DatasrcFieldDefSel stDatasrcFieldDefSel = {0};

    stDatasrcFieldDefSel.lInDatasrcId = 1;
    stDatasrcFieldDefSel.lInFieldId = 4;
    iResult = dbsDatasrcFieldDefSel(dbsenv, KR_DBSELECT, &stDatasrcFieldDefSel);
    if (iResult != KR_DBOK) {
        fprintf(stderr, "dbsDatasrcFieldDefSel [%ld],[%ld] Error!",\
                stDatasrcFieldDefSel.lInDatasrcId, \
                stDatasrcFieldDefSel.lInFieldId);
        return -1;
    }

    printf("fieldid:[%ld], name:[%s], length:[%ld]\n", \
            stDatasrcFieldDefSel.lInFieldId,
            stDatasrcFieldDefSel.caOutFieldName,
            stDatasrcFieldDefSel.lOutFieldLength);

    return 0;
}

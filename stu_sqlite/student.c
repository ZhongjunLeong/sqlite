#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#define DATABASE "stu.db"
int do_insert(sqlite3 *db)
{
    int id;
    char name[32] = {};
    int score;
    char sql[128] = {};
    char *errmsg;
    printf("inpute id:");
    scanf("%d",&id);
    getchar();

    printf("inpute name:");
    scanf("%s",name);
    getchar();
    printf("inpute score:");
    scanf("%d",&score);
    getchar();
    sprintf(sql,"insert into stu values(%d,'%s',%d);",id,name,score);
    if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
    {
        printf("%s\n",errmsg);
    }
    else
    {

        printf("insert done.\n");
    }
    return 0;
}
int do_delete(sqlite3 *db)
{
    int id;
    char name[32] = {};
    int score;
    char sql[128] = {};
    char *errmsg;
    printf("inpute id:");
    scanf("%d",&id);
    getchar();
    sprintf(sql,"delete from stu where id =%d",id);

    if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
    {
        printf("%s\n",errmsg);
    }
    else
    {

        printf("delete done.\n");
    }
    return 0;
}
int do_update(sqlite3 *db)
{
    int id;
    char name[32] = {};
    int score;
    char sql[128] = {};
    char *errmsg;
    printf("inpute update id:");
    scanf("%d",&id);
    getchar();
    printf("update score:");
    scanf("%d",&score);
    getchar();

    sprintf(sql,"update stu set score=%d where id =%d",score,id);

    if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
    {
        printf("%s\n",errmsg);
    }
    else
    {

        printf("update done.\n");
    }
    return 0;

}
/*
int callback(void *para,int f_num,char**f_value,char **f_name)
{
    int i =0;
    for(i = 0; i < f_num; i++)
    {
        printf("%-11s ",f_value[i]);
    }
    putchar(10);



    return 0;
}
int do_query(sqlite3 *db)
{
    char sql[128] = {};
    char *errmsg;
    sprintf(sql,"select * from stu;");

    if(sqlite3_exec(db,sql,callback,NULL,&errmsg) != SQLITE_OK)
    {
        printf("%s\n",errmsg);
    }
    else
    {

        printf("qurey done.\n");
    }
    return 0;
}
*/
int do_query1(sqlite3 *db)
{
    char sql[128] = {};
    char *errmsg;
    char ** resultp;
    int nrow;
    int ncloum;
    int i,j;
    int index;
    sprintf(sql,"select * from stu;");

    if(sqlite3_get_table(db,sql,&resultp,&nrow,&ncloum,&errmsg) != SQLITE_OK)
    {
        printf("%s\n",errmsg);
    }
    else
    {

        printf("qurey done.\n");
    }
   index = ncloum;
//printf("index don%d\n",index);
    for( i = 0; i < nrow; i++)
    {
        for(j = 0; j < ncloum; j++)
        {
            printf("%-11s",resultp[index++]);
        //    printf("here\n");
        }
        putchar(10);
    }
    return 0;
}
int main()
{
        sqlite3 *db;
        char *errmsg;
        int cmd;
        if(sqlite3_open(DATABASE,&db) != SQLITE_OK)
        {
            printf("%s\n",sqlite3_errmsg(db));
            return -1;
        }
        else
        {
            printf("open DATABASE success.\n");
        }

       //create a schema 
        if(sqlite3_exec(db,"create table stu(id Integer,name char,score Integer);",NULL,NULL,&errmsg) != SQLITE_OK)
        {
            printf("%s\n",errmsg);
        }
        else
        {
            printf("create table or open sucesses\n");
        }
        while(1)
        {
            printf("*************\n");

            printf("1:insert;2:delete;3:query;4:update;5:quit.\n");
            printf("*************\n");
            scanf("%d",&cmd);
            getchar();
            switch(cmd)
            {
                case 1:
                    do_insert(db);
                    break;
                case 2:
                    do_delete(db);
                    break;
                case 3:
                    do_query1(db);
                    break;
                case 4:
                    do_update(db);
                    break;
                case 5:
                    sqlite3_close(db);
                    exit(0);
                defalut:
                    printf("error cmd\n");
            }
        }
        return 0;
}

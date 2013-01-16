#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#define LINEBUF 256
#define USERFILE "/etc/passwd"

#define FI_TIME 20
#define FI_USER 32
#define FI_GRP  32

#define ATIME 1
#define CTIME 2
#define MTIME 3

#define UID 1
#define GID 2

struct file_info {
    char user[FI_USER];
    char group[FI_GRP];
    char atime[FI_TIME];
    char ctime[FI_TIME];
    char mtime[FI_TIME];
};

typedef struct file_info file_info;

int getTime(time_t timep, int flag, file_info *fi)
{
    struct tm *p;
    p = localtime((time_t *)&timep);

    int year,mon,mday,hour,min;       //转换时间
    year = 1900 + p->tm_year;
    mon = 1 + p->tm_mon;
    mday = p->tm_mday;
    hour = p->tm_hour ;
    min = p->tm_min;

    switch(flag)
    {
        case ATIME:
            sprintf(fi->atime, "%d-%d-%d %d:%d", year, mon, mday, hour, min);
            break;
        case CTIME:
            sprintf(fi->ctime, "%d-%d-%d %d:%d", year, mon, mday, hour, min);
            break;
        case MTIME:
            sprintf(fi->mtime, "%d-%d-%d %d:%d", year, mon, mday, hour, min);
            break;
        default:
            return -1;
    }

    return 0;
}

int getID(int id, int flag, file_info *fi)
{

    /* open the file */
	FILE *fp = fopen(USERFILE,"r");
	if(!fp){
	    printf("Open the file error!\n");
	    return -1;
	}

    //read the file by the line
    char buf[LINEBUF];
    char user[FI_USER];
    char pwd[2];
    char uid[FI_GRP];
    char gid[FI_GRP];

    int found = 0;
	while(fgets(buf, LINEBUF, fp) != NULL){
        //get the user's and group's name
        sscanf(buf, "%[^:]:%[^:]:%[^:]:%[^:]", user, pwd, uid, gid);
        if(flag == UID && atoi(uid) == id) {
            strcpy(fi->user, user);
            found = 1;
            break;
        }
        else if(flag == GID && atoi(gid) == id) {
            strcpy(fi->group, user);
            found = 1;
            break;
        }
	}

	fclose(fp);

	if(!found)
        return -1;

	return 0;
}


int getFileinfo(char *filename, file_info *fi)
{
     struct stat stbuf;
	 int res = lstat(filename, &stbuf);
	 if (res == -1)
	 {
        printf("There is no file named %s!\n", filename);
        return -1;
	 }

	 int uid  = stbuf.st_uid;      //user  id
	 int gid  = stbuf.st_gid;      //group id

	 time_t atime = stbuf.st_atime;  //最后访问时间
	 time_t mtime = stbuf.st_mtime;  //修改时间—文件内容
	 time_t ctime = stbuf.st_ctime;  //改变时间—inode

	 getTime(atime, ATIME, fi);
	 getTime(ctime, CTIME, fi);
	 getTime(mtime, MTIME, fi);

	 getID(uid, UID, fi);
	 getID(gid, GID, fi);

	 return 0;
}

int main(int argc, char **argv)
{
    file_info fi;
    getFileinfo(argv[1], &fi);

    printf("%s\n", fi.user);
    printf("%s\n", fi.group);
    printf("%s\n", fi.atime);
    printf("%s\n", fi.ctime);
    printf("%s\n", fi.mtime);

    return 0;
}

#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*
 * config example
 * valid char: [0-9] [a-zA-Z] [.]
 * IPADDR = 192.168.1.71
 * NETMASK = 255.255.255.0
 * GATEWAY = 192.168.1.1
 */

#define ADDRSIZE 16
#define MASKLEN  16
#define GATEWAYSIZE 16
#define LINESIZE 100

struct netconfig {
    char ip[ADDRSIZE];
    char mask[MASKLEN];
    char gateway[GATEWAYSIZE];
};

typedef struct netconfig netconfig;

/* ȥ��ǰ��Ŀո� */
void trim(char *s)
{
    char *tmp = s;

    /* trim left size */
    while(isspace(*tmp)) tmp++;
    strcpy(s, tmp);

    /* trim right side */
    tmp = s + strlen(s) - 1;
    while(isspace(*tmp)) tmp--;
    *(tmp+1) = '\0';
}

/* �ж��Ƿ�Ϊ�����ַ� */
int is_config_word(char c)
{
    return (isdigit(c) || isalpha(c) || c == '.');
}

void set_values(char* key, char* value, netconfig* config)
{
    if(!strcmp(key, "IPADDR")) {
        strcpy(config->ip, value);
    }
    else if(!strcmp(key, "NETMASK")) {
        strcpy(config->mask, value);
    }
    else if(!strcmp(key, "GATEWAY")) {
        strcpy(config->gateway, value);
    }
}

int parse_line(char* line, char delim, netconfig* config)
{
    /* ״̬�Ķ��� */
    enum state {
        STAT_INIT,
        STAT_KEY,
        STAT_VALUE,
        STAT_DELIM
    }state = STAT_INIT;

    char* start_key = NULL;
    char* start_value = NULL;

    char *p = line;
    int j = 0;
    for(; *p != '\0'; p++) {
        switch(state) {
            case STAT_INIT: {
                /* ���������ַ�������STAT_KEY״̬������סkey����ʼλ��*/
                if(is_config_word(*p)) {
                    state = STAT_KEY;
                    start_key = p;
                }
                break;
            }
            case STAT_KEY: {
                /* �����������ַ���˵��key�Ѿ�������
                 * ת�����ָdelim��״̬����key�Ľ���λ����Ϊ������
                 */
                if(!is_config_word(*p)) {
                    *p = '\0';
                    state = STAT_DELIM;
                }
                break;
            }
            case STAT_DELIM: {
                /* ���������ַ�������STAT_VALUE״̬������סvalue����ʼλ��*/
                if(is_config_word(*p)) {
                    state = STAT_VALUE;
                    start_value = p;
                }
                break;
            }
            case STAT_VALUE: {
                /* �����������ַ���˵��value�Ѿ������� ��סvalue�Ľ���λ��
                 * ���ֱ������û�������������ַ���ĩβ�����Ѿ��ǽ�����
                 */
                if(!is_config_word(*p)) {
                    *p = '\0';
                }
                break;
            }
            default:
                break;
        }
    }

    set_values(start_key, start_value, config);
}

int parse_file(char *filename, netconfig *config)
{
    FILE* fp = fopen(filename, "r");
    if(fp == NULL) {
        return -1;
    }

    char line[LINESIZE];
    while(fgets(line, LINESIZE, fp) != NULL) {
        trim(line);
        if(line[0] == '#')
            continue;
        parse_line(line, '=', config);
    }

    return 0;
}

int main()
{
    netconfig config;
    parse_file("config.txt", &config);
    printf("IPADDR = %s\n", config.ip);
    printf("NETMASK = %s\n", config.mask);
    printf("GATEWAY = %s\n", config.gateway);

    return 0;
}

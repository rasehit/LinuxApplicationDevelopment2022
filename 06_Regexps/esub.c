#include <regex.h>     
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXGR 10

int check_substitution(char * substitution, int match_num)
{
    char * indexer = substitution;
    while(*indexer)
    {
        if (*indexer == '\\') 
        {
            indexer++;
            if ((*indexer) > '9' || (*indexer) < '0' || (*indexer)-'0' >= match_num)
            {
                return 1;
            }
        }
        indexer++;
    }
    return 0;
}

int main(int argc, char ** argv)
{
    regex_t regex;
    regmatch_t pmatch[MAXGR];

    int reti, match_num = 0;
    char msgbuf[100];
    char ** rows = (char **)malloc(sizeof(char*)*MAXGR);
    char * regexp = argv[1], * substitution = argv[2], * input_string = argv[3];
    char * indexer;

    reti = regcomp(&regex, regexp, REG_EXTENDED);
    if (reti) 
    {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, input_string, MAXGR, pmatch, 0);
    if (!reti) 
    {
        for(int i = 0; i < MAXGR && pmatch[i].rm_so>=0; i++)
        {
            rows[match_num] = (char *)malloc(sizeof(char)*(pmatch[i].rm_eo-pmatch[i].rm_so+1));
            memcpy(rows[match_num], input_string+pmatch[i].rm_so*sizeof(char), pmatch[i].rm_eo-pmatch[i].rm_so);
            rows[match_num][pmatch[i].rm_eo-pmatch[i].rm_so] = '\0';
            match_num++;
        }

    }
    else if (reti == REG_NOMATCH) 
    {
        puts("No match");
    }
    else 
    {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    if (check_substitution(substitution, match_num))
    {
        printf("There is no such packet (max number of packet is %d)", match_num-1);
        exit(1);
    }

    printf("%.*s", (int)pmatch[0].rm_so, input_string);

    indexer = substitution;
    while(*indexer)
    {
        if (*indexer == '\\') 
        {
            indexer++;
            if ((*indexer) > '9' || (*indexer) < '0' || (*indexer)-'0' >= match_num)
            {
                printf("There is no such packet");
                exit(1);
            }
            printf("%s", rows[(*indexer)-'0']);
            
        }
        else 
            printf("%c", *indexer);
        indexer++;
    }

    printf("%s\n", input_string + pmatch[0].rm_eo);

    // for (int i = 0; i < match_num; i++)
    // {
    //     printf("Match %d is %s\n", i, rows[i]);
    // }

    for (int i = 0; i < match_num; i++)
    {
        free(rows[i]);
    }
    free(rows);

    regfree(&regex);
    return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
 *可能用上的函数：strtok、strstr，好像前一个好用一些！！
 * strcpy一下原串？如果需要保留其的话
 *
 * 先把keywords变成一个列表，然后遇到了就highlight？
 */

// split函数
void split(char *src,const char *separator,char **dest,int *num) 
{
    char *pNext;
    int count = 0;
    // 做一些特判，边界处理
    if (src == NULL || strlen(src) == 0)
        return;
    if (separator == NULL || strlen(separator) == 0)
        return;    
    //利用strtok循环获得拆分的字符串
    pNext = strtok(src,separator);
    while(pNext != NULL) 
    {
         *dest++ = pNext;// 先执行*dest，将值赋为pNext，再++
         ++count;
         pNext = strtok(NULL,separator); // strtok的第一个参数为NULL时，默认使用之前分割的指针
    }  
    *num = count;
}     

// 完成高亮的操作
void highlight(char** sentences, int sentences_num, char** keywords, int keywords_num)
{
    printf("highlighted sentences are as follows:\n");

    const char* prefix = "<font color=#c60a00>";
    const char* suffix = "</font>";

    for(int i = 0; i < sentences_num; ++i)
    {
        // 首先把当前句：sentences[i]给切分成词串
        char* words[100];
        int words_num = 0;
        split(sentences[i], " ", words, &words_num);

        // 依次比对， 看keywords是否在当前句子中出现、出现了几次,
        // 并且保存对应的关键词，在当前句子里面的下标
        int occur_num = 0;
        int* occur_index = (int*)malloc(16*keywords_num);

        for (int k = 0; k < words_num; ++k)
            for(int j = 0; j < keywords_num; ++j)
                if(strcmp(words[k],keywords[j]) == 0)
                {
                    occur_index[occur_num++] = k;
                    break;
                }

        // 没有关键词出现的直接跳过
        if(occur_num == 0)
            continue;

        // 考虑有关键词的句子的输出控制：
        // 在输出的时候，如果不是关键词，那么直接输出
        // 如果是关键词，需要考虑关键词的位置是否连续
        // 如果不连续，那么单个词的前后加prefix和suffix
        // 如果前后连续，那么开头加prefix,结尾点加suffix


        // 目前已经知道当前这句话里面有keywords
        int left_is_key = 0;
        int kw_ptr = 0;
        for(int j = 0; j < words_num; ++j)
        {
            // 首先判断当前的词是不是关键词
            if (occur_index[kw_ptr] != j)
            {
                // 当前的词不是关键词，但是前一个是，那么要补一个suffix
                if(left_is_key)
                {
                    printf("%s ", suffix);
                    left_is_key = 0;
                }
                printf("%s ",words[j]);
            }
            else
            {
                //当前的词是关键词, 判断prefix应该如何输出
                ++kw_ptr;
                if(left_is_key)
                {
                    // 前面一个和当前都是关键词，那么只需要正常输出
                    printf("%s ", words[j]);
                }
                else
                {
                    //是船新的关节词连串
                    printf("%s %s ", prefix, words[j]);
                    left_is_key = 1;
                }
            }


        }

        free(occur_index);
        printf("\b.\n");
    }

}

int main()
{
    // 程序的输入和元数据
    const char* input_query = "information retrieve";
    const char* input_doc_text = "There are tons of information for us to retrieve on Internet.We can search Internet for answers.Especially when we can not tackle the problem independently.So it is essential for us to master some skills about information retrieve likewise.Right?";

    // 复制一个副本,用于操作
    char* query = (char*)malloc(2*strlen(input_query));
    char* doc_text = (char*)malloc(2*strlen(input_doc_text));
    memset(query,0,2*strlen(input_query));
    memset(doc_text,0,2*strlen(input_doc_text));
    strcpy(query,input_query);
    strcpy(doc_text,input_doc_text);

    // 首先将doc分句
    char* sentences[100];
    int sentences_num = 0;
    split(doc_text, ".", sentences, &sentences_num);
    
    // 然后将query分词
    char* keywords[100];
    int keywords_num = 0;
    split(query, " ", keywords, &keywords_num);

    // 打印一些原始的信息
    printf("===========================\n");
    printf("all keywords are as follows:\n");
    for(int i = 0; i < keywords_num; ++i)
        printf("%s\n",keywords[i]);
    printf("\n\n===========================\n");
    printf("all input sentences are as follows:\n");
    for(int i = 0; i < sentences_num; ++i)
        printf("%s\n",sentences[i]);

    // 然后针对每一个句子进行高亮处理
    printf("\n\n===========================\n");
    highlight(sentences, sentences_num, keywords, keywords_num);

    return 0;
}

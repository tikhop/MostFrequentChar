#include "mostFrequentChar.h"

#define RESULT_SIZE 127
#define THREAD_COUNT 2

struct thread_info
{
    pthread_t thread_id;
    int       resultArray[RESULT_SIZE];
    int       thread_num;
    int       startIndex;
    int       str_size;
    char      *str;
};

void _mostFrequentChar(void *arg);
int set_char(char c, int result[]);
int set_char_int(int c, int result[]);

char mostFrequentChar(char str[], int size)
{
    int result[RESULT_SIZE] = {0};
    
    char current_char;
    char frequent_char = '\0';
    
    int current_char_frequency = 0;
    int char_frequency = 0;
    
    for(int i = 0; i<size; i++)
    {
        current_char = str[i];
        current_char_frequency = set_char(current_char, result);
        
        if(current_char_frequency >= char_frequency)
        {
            char_frequency = current_char_frequency;
            frequent_char = current_char;
        }
    }
    
    return frequent_char;
}

char mostFrequentCharOpt1(char str[], int size)
{
    int result[RESULT_SIZE] = {0};
    
    char frequent_char = '\0';
    
    int current_char_frequency = 256;
    int char_frequency = 0;
    
    for(int i = 0; i<size; i++)
    {
        set_char(str[i], result);
    }
    
    for(int i = 0; i<RESULT_SIZE; i++)
    {
        current_char_frequency = result[i];
        
        if(current_char_frequency >= char_frequency)
        {
            char_frequency = current_char_frequency;
            frequent_char = i;
        }
    }
    
    return frequent_char;
}

int mostFrequentCharOpt2(char str[], int size) //Char to Int
{
    int result[RESULT_SIZE] = {0};
    
    int frequent_char = 0;
    
    int current_char_frequency = 0;
    int char_frequency = 0;
    
    for(int i = 0; i<size; i++)
    {
        set_char(str[i], result);
    }
    
    for(int i = 0; i<RESULT_SIZE; i++)
    {
        current_char_frequency = result[i];
        
        if(current_char_frequency >= char_frequency)
        {
            char_frequency = current_char_frequency;
            frequent_char = i;
        }
    }
    
    return frequent_char;
}

int mostFrequentCharOpt3(char str[], int size) //Loop optimization
{
    int result[RESULT_SIZE] = {0};
    
    int frequent_char = 0;
    
    int current_char_frequency = 0;
    int char_frequency = 0;
    
    for(int i = size; i--; )
    {
        set_char(str[i], result);
    }
    
    for(int i = RESULT_SIZE; i--; )
    {
        current_char_frequency = result[i];
        
        if(current_char_frequency >= char_frequency)
        {
            char_frequency = current_char_frequency;
            frequent_char = i;
        }
    }
    
    return frequent_char;
}

int mostFrequentCharThreadOpt(char str[], int size)
{
    int s;
    int tnum;
    int num_threads = THREAD_COUNT;
    struct thread_info *tinfo;
    
    tinfo = calloc(num_threads, sizeof(struct thread_info));
    
    if (tinfo == NULL)
        exit(EXIT_FAILURE);
    
    int minCharCountPerThread = size/num_threads;
    int startIndex = 0;
    
    for (tnum = num_threads; tnum--;)
    {
        startIndex = minCharCountPerThread*tnum;
        
        tinfo[tnum].thread_num = tnum + 1;
        tinfo[tnum].startIndex = minCharCountPerThread*tnum;
        tinfo[tnum].str_size = (size - minCharCountPerThread*tnum) >= minCharCountPerThread ? minCharCountPerThread : (size - minCharCountPerThread*(tnum-1));
        tinfo[tnum].str = str;
        
        s = pthread_create(&tinfo[tnum].thread_id, NULL,
                           (void *(*)(void *))_mostFrequentChar, &tinfo[tnum]);
        if (s != 0)
            exit(EXIT_FAILURE);
    }
    
    int frequent_char = 0;
    int char_frequency = 0;
    int current_char_frequency = 0;
    
    for (tnum = num_threads; tnum--; )
    {
        s = pthread_join(tinfo[tnum].thread_id, NULL);
    }
   
    for(int i = RESULT_SIZE; i--; )
    {
        current_char_frequency = 0;
        
        for (int z = num_threads; z--;)
        {
            current_char_frequency += tinfo[z].resultArray[i];
        }
        
        if(current_char_frequency >= char_frequency)
        {
            char_frequency = current_char_frequency;
            frequent_char = i;
        }
    }
    
    free(tinfo);
    
    return 'a';
}

int mostFrequentCharThreadOpt2(char str[], int size)
{
    int s;
    int tnum;
    int num_threads = THREAD_COUNT;
    struct thread_info *tinfo;
    
    tinfo = calloc(num_threads, sizeof(struct thread_info));
    
    if (tinfo == NULL)
        exit(EXIT_FAILURE);
    
    int minCharCountPerThread = size/num_threads;
    int startIndex = 0;
    
    for (tnum = num_threads; tnum--;)
    {
        startIndex = minCharCountPerThread*tnum;
        
        tinfo[tnum].thread_num = tnum + 1;
        tinfo[tnum].startIndex = minCharCountPerThread*tnum;
        tinfo[tnum].str_size = (size - minCharCountPerThread*tnum) >= minCharCountPerThread ? minCharCountPerThread : (size - minCharCountPerThread*(tnum-1));
        tinfo[tnum].str = str;
        
        s = pthread_create(&tinfo[tnum].thread_id, NULL,
                           (void *(*)(void *))_mostFrequentChar, &tinfo[tnum]);
        if (s != 0)
            exit(EXIT_FAILURE);
    }
    
    int frequent_char = 0;
    int char_frequency = 0;
    int current_char_frequency = 0;
    
    for (tnum = num_threads; tnum--; )
    {
        s = pthread_join(tinfo[tnum].thread_id, NULL);
    }
    
    int result[RESULT_SIZE];
    
    for (int i = num_threads; i--;)
    {
        int *resultArray = tinfo[i].resultArray;
        
        for(int z = RESULT_SIZE; z--; )
        {
            current_char_frequency = resultArray[z];
            result[z] += current_char_frequency;
        }
    }

    for(int i = RESULT_SIZE; i--; )
    {
        current_char_frequency = result[i];
        
        if(current_char_frequency >= char_frequency)
        {
            char_frequency = current_char_frequency;
            frequent_char = i;
        }
    }
    
    free(tinfo);
    
    return frequent_char;
}

void _mostFrequentChar(void *arg)
{
    struct thread_info *tinfo = arg;
    
    int current_char = 0;
    int endIdx = tinfo->str_size;
    int offset = tinfo->startIndex;
    
    for(int i = endIdx; i--; )
    {
        current_char = tinfo->str[offset + i];
        set_char(current_char, tinfo->resultArray);
    }
}


//char mostFrequentCharOpt4(char str[], int size) //Removing condition
//{
//    int result[RESULT_SIZE] = {0};
//
//    int frequent_char = 0;
//
//    int current_char_frequency = 0;
//    int char_frequency = 0;
//
//    for(size_t i = 0; i<size; i++)
//    {
//        set_char(str[i], result);
//    }
//
//    int charMap[2];
//    int charCountMap[2];
//    int index;
//
//    for(int i = 0; i<RESULT_SIZE; i++)
//    {
//        current_char_frequency = result[i];
//
//        charMap[0] = i;
//        charMap[1] = frequent_char;
//
//        charCountMap[0] = current_char_frequency;
//        charCountMap[1] = char_frequency;
//
//        index = abs((current_char_frequency - char_frequency)>>31); // if result[i] > prevMax -> 0, else 1
//        frequent_char = charMap[index];
//        char_frequency = charCountMap[index];
//    }
//
//    return (char) frequent_char;
//}
//
//char mostFrequentCharOpt5(char str[], int size) //Removing condition -> one loop
//{
//    int result[RESULT_SIZE] = {0};
//
//    char frequent_char = 0;
//    char current_char;
//
//    int current_char_frequency = 0;
//    int char_frequency = 0;
//
//    char charMap[2];
//    int charCountMap[2];
//    int index;
//
//    for(size_t i = 0; i<size; i++)
//    {
//        current_char = str[i];
//        current_char_frequency = set_char(current_char, result);
//
//        charMap[0] = current_char;
//        charMap[1] = frequent_char;
//
//        charCountMap[0] = current_char_frequency;
//        charCountMap[1] = char_frequency;
//
//        index = abs((current_char_frequency - char_frequency)>>31); // if result[i] > prevMax -> 0, else 1
//        frequent_char = charMap[index];
//        char_frequency = charCountMap[index];
//
//    }
//
//    return frequent_char;
//}


inline int test_char(char c, int result[])
{
    return result[c] != 0;
}

inline int set_char(char c, int result[])
{
    int count = result[c];
    result[c] = ++count;
    return count;
}

inline int set_char_int(int c, int result[])
{
    int count = result[c];
    result[c] = ++count;
    return count;
}

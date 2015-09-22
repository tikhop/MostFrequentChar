//
//  main.m
//  MostFrequentChar
//
//  Created by Pavel Tikhonenko on 21/09/15.
//  Copyright © 2015 Pavel Tikhonenko. All rights reserved.
//


#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <pthread.h>
#include <string.h>
#include <Foundation/Foundation.h>
#import "mostFrequentChar.h"

void generate_chars(char *arr, int n);
double get_time();

int main(int argc, char * argv[])
{
    int iterations = 500;
    
    char char_list[CHAR_LIST_LENGHT];
    generate_chars(char_list, CHAR_LIST_LENGHT);
    int n = CHAR_LIST_LENGHT;
    char frequent_char = '\0';
    
    printf("First version\n");
    double start = get_time();
    for (int i = 0; i<iterations; i++)
    {
        frequent_char = mostFrequentChar(char_list, n);
    }
    double end = get_time();
    printf("most frequent char is %c\n", frequent_char);
    printf("running time is %f\n", end - start);
    printf("\n");
    
    printf("Basic optimization\n");
    start = get_time();
    for (int i = 0; i<iterations; i++)
    {
        frequent_char = mostFrequentCharOpt1(char_list, n);
    }
    end = get_time();
    printf("most frequent char is %c\n", frequent_char);
    printf("running time is %f\n", end - start);
    printf("\n");
    
    printf("Change type char to int\n");
    start = get_time();
    int result = 0;
    for (int i = 0; i<iterations; i++)
    {
        result = mostFrequentCharOpt2(char_list, n);
    }
    end = get_time();
    printf("most frequent char is %c\n", (char) result);
    printf("running time is %f\n", end - start);
    printf("\n");
    
    printf("Decrementing loop\n");
    start = get_time();
    for (int i = 0; i<iterations; i++)
    {
        result = mostFrequentCharOpt3(char_list, n);
    }
    end = get_time();
    printf("most frequent char is %c\n", (char) result);
    printf("running time is %f\n", end - start);
    printf("\n");
    
    printf("Pthread optimization\n");
    start = get_time();
    for (int i = 0; i<iterations; i++)
    {
        result = mostFrequentCharThreadOpt(char_list, n);
    }
    end = get_time();
    printf("most frequent char is %c\n", (char) result);
    printf("running time is %f\n", end - start);
    printf("\n");
    
    return 0;
}

void generate_chars(char *arr, int n)
{
    int i = 0;
    int randomValue = 0;
    char c = 0;
    
    srand((unsigned int)time(NULL));
    while(i<n)
    {
        randomValue = 33 + (rand()/(RAND_MAX/93));
        c = (char) randomValue;
        
        if (isprint((int)c) && !isspace((int)c) )
        {
            arr[i] = c;
            i++;
        }
        
    }
}

double get_time()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec*1e-6;
}

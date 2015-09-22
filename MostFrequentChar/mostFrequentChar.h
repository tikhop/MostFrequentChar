//
//  mostFrequentChar.h
//
//  Created by Pavel Tikhonenko on 12/09/15.
//  Copyright (c) 2015 Pavel Tikhonenko. All rights reserved.
//

#ifndef __Yandex2__mostFrequentChar__
#define __Yandex2__mostFrequentChar__

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
char mostFrequentChar(char str[], int size);
char mostFrequentCharOpt1(char str[], int size);
int mostFrequentCharOpt2(char str[], int size); //Char to Int
int mostFrequentCharOpt3(char str[], int size); //Loop optimization
char mostFrequentCharOpt4(char str[], int size); //Removing condition
char mostFrequentCharOpt5(char str[], int size); //Removing condition -> one loop
int mostFrequentCharThreadOpt(char str[], int size);
int mostFrequentCharThreadOpt2(char str[], int size);


#define CHAR_LIST_LENGHT 1000000

#endif /* defined(__Yandex2__mostFrequentChar__) */

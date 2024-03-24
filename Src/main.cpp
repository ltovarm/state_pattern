/**************************************************************************
 * File Name: Main.cpp                                                    *
 * Desc: This file implements the Main state machine                      *
 * Author: LTovar                                                         *
 * History:                                                               *
 *  - 2024/02/17: ltovar - file creation                                  *
 * Copyright (c) 2024: LTovar                                             *
 *************************************************************************/

/************************************
 *          Includes                *
 ************************************/
#include <iostream>
#include "Semaphore.hpp"

int main(){
    Context *context = new Context(new Unknown);
    delete context;
    std::cout << "Bye Bye" << std::endl;
    return 0;
}
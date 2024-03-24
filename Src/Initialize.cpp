/*******************************************************************************
 * File Name: Initialize.cpp                                                   *
 * Desc: This file implements the Initialize state machine                     *
 * Author: LTovar                                                              *
 * History:                                                                    *
 *  - 2024/02/17: ltovar - file creation                                       *
 * Copyright (c) 2024: LTovar                                                  *
 ******************************************************************************/

/************************************
 *          Includes                *
 ************************************/
#include <iostream>

#include "Semaphore.hpp"

Initialize::Initialize(){
    this->SetState(OTHERS);
    GoToUnknown();
};

Initialize::~Initialize(){};

void Initialize::GoToUnknown(){
    try{
        context_->TransitionTo(new Unknown);
    } catch(std::exception& e){
        std::cerr << "[ERROR] Exception" <<  e.what() << std::endl;
    } catch(...){
       std::cerr << "[ERROR] Unknown" << std::endl; 
    }
};
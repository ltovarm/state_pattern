/*******************************************************************************
 * File Name: Opened.cpp                                                       *
 * Desc: This file implements the Opened state machine                         *
 * Author: LTovar                                                              *
 * History:                                                                    *
 *  - 2024/02/24: ltovar - file creation                                       *
 * Copyright (c) 2024: LTovar                                                  *
 ******************************************************************************/

/************************************
 *          Includes                *
 ************************************/
#include <iostream>
#include <thread>
#include <chrono>

#include "Semaphore.hpp"

Opened::~Opened(){};

void Opened::Run(){

    try{
        state = this->GetState();
        this->SetState(OPENED);
    } catch(std::exception& e){
        std::cerr << "[ERROR] Exception semaphore_ptr" << e.what() << std::endl;
        GoToTerminate();
    } catch(...){
       std::cerr << "[ERROR] Unknown Exception semaphore_ptr" << std::endl;
       GoToTerminate(); 
    }

    try{
        // This simulates the actuator
        context_->SetSemaphore(false,false,true);
    }catch(...){
        std::cout << "Error ..." << std::endl;
        GoToUnknown();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    if (true == this->context_->GetFlagTerminate()){
        SetState(OTHERS);
    }
    // Go to the next state
    // OTHERS = INITIALIZE or TERMINATE
    switch (state)
    {
        case UNKNOWN:
            GoToTransition();
            break;
        case TRANSITION:
            GoToTransition();
            break;
        default:
            GoToTerminate();
            break;
    }
};

void Opened::GoToUnknown(){
    this->context_->TransitionTo(new Unknown);
};

void Opened::GoToTransition(){
    this->context_->TransitionTo(new Transition);
};

void Opened::GoToTerminate(){
    this->context_->TransitionTo(new Terminate);
};
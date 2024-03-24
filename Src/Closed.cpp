/****************************************************************************
 * File Name: Closed.cpp                                                    *
 * Desc: This file implements the Closed state machine                      *
 * Author: LTovar                                                           *
 * History:                                                                 *
 *  - 2024/02/24: ltovar - file creation                                    *
 * Copyright (c) 2024: LTovar                                               *
 ***************************************************************************/

/************************************
 *          Includes                *
 ************************************/
#include <iostream>
#include <thread>
#include <chrono>

#include "Semaphore.hpp"

Closed::~Closed(){};

void Closed::Run(){

    try{
        state = this->GetState();
        this->SetState(CLOSED);
    } catch(std::exception& e){
        std::cerr << "[ERROR] Exception m_semaphore_ptr" << e.what() << std::endl;
        GoToTerminate();
    } catch(...){
       std::cerr << "[ERROR] Unknown Exception m_semaphore_ptr" << std::endl;
       GoToTerminate(); 
    }

    try{
        // This simulates the actuator
        context_->SetSemaphore(true,false,false);
    }catch(...){
        std::cerr << "Error ..." << std::endl;
        GoToUnknown();
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    if (true == this->context_->GetFlagTerminate()){
        this->SetState(OTHERS);
    }
    // Go to the next state
    // OTHERS = INITIALIZE or TERMINATE
    switch (state){
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

void Closed::GoToUnknown(){
    this->context_->TransitionTo(new Unknown);
};

void Closed::GoToTransition(){
    this->context_->TransitionTo(new Transition);
};

void Closed::GoToTerminate(){
    this->context_->TransitionTo(new Terminate);
};
/*******************************************************************************
 * File Name: Transition.cpp                                                   *
 * Desc: This file implements the Transition state machine                     *
 * Author: LTovar                                                              *
 * History:                                                                    *
 *  - 2024/02/24: ltovar - file creation                                       *
 * Copyright (c) 2024: LTovar                                                  *
 ******************************************************************************/

/************************************
 *          Includes                *
 ************************************/
#include <iostream>
#include <chrono>

#include "Semaphore.hpp"

Transition::~Transition(){};

void Transition::Run(){

    try{
        state = this->GetState();
        this->SetState(TRANSITION);
    } catch(std::exception& e){
        std::cerr << "[ERROR] Exception semaphore_ptr" << e.what() << std::endl;
        GoToTerminate();
    } catch(...){
       std::cerr << "[ERROR] Unknown Exception semaphore_ptr" << std::endl;
       GoToTerminate(); 
    }

    try{
        // This simulates the actuator
        context_->SetSemaphore(false,true,false);
    }catch(...){
        std::cout << "Error ..." << std::endl;
        GoToTerminate();
    }

    if (true == this->context_->GetFlagTerminate()){
        GoToTerminate();
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
        GoToTerminate();
        break;
    case OPENED:
        GoToClosed();
        break;
    case CLOSED:
        GoToOpened();
        break;
    default:
        GoToTerminate();
        break;
    }
};

void Transition::GoToOpened(){
    this->context_->TransitionTo(new Opened);
};

void Transition::GoToClosed(){
    this->context_->TransitionTo(new Closed);
};

void Transition::GoToTerminate(){
    this->context_->TransitionTo(new Terminate);
};
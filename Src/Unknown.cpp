/*****************************************************************************
 * File Name: Unknown.cpp                                                    *
 * Desc: This file implements the Unknown state machine                      *
 * Author: LTovar                                                            *
 * History:                                                                  *
 *  - 2024/02/17: ltovar - file creation                                     *
 * Copyright (c) 2024: LTovar                                                *
 ****************************************************************************/

/************************************
 *          Includes                *
 ************************************/
#include <iostream>
#include <thread>
#include <chrono>

#include "Semaphore.hpp"

Unknown::~Unknown(){};

void Unknown::Run(){

    try{
        state = this->GetState();
        this->SetState(UNKNOWN);
    } catch(std::exception& e){
        std::cerr << "[ERROR] Exception semaphore" << e.what() << std::endl;
        GoToTerminate();
    } catch(...){
       std::cerr << "[ERROR] Unknown Exception semaphore" << std::endl;
       GoToTerminate(); 
    }

    try{
        // Flashing during 5 sec (Simulation of synchronisation)
        thread_flag = true;
        std::thread flashing_thread(&Unknown::Flashing, this);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        thread_flag = false;
        flashing_thread.join();
    } catch(std::exception& e){
        std::cerr << "[ERROR] Exception in state Unknown thread" << e.what() << std::endl;
        GoToTerminate();
    } catch(...){
       std::cerr << "[ERROR] Unknown Exception in state Unknown thread" << std::endl;
       GoToTerminate();
    }
    // Go to the next state
    // OTHERS = INITIALIZE or INTERMEDIATE or TERMINATE
    switch (state)
    {
    case OTHERS:
        GoToClosed();
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

void Unknown::GoToOpened(){
    this->context_->TransitionTo(new Opened);
};

void Unknown::GoToClosed(){
    this->context_->TransitionTo(new Closed());
};

void Unknown::GoToTerminate(){
    this->context_->TransitionTo(new Terminate);
};

void Unknown::Flashing(){
    bool red = false, yellow = false, green = false;
    this->context_->SetSemaphore(red, yellow, green); 
    while (thread_flag){
        red = !red;
        yellow = !yellow;
        green = !green;
        this->context_->SetSemaphore(red, yellow, green);
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    } 
};
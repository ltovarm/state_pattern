/*******************************************************************************
 * File Name: Semaphore.cpp                                                    *
 * Desc: This file implements the Semaphore state machine                      *
 * Author: LTovar                                                              *
 * History:                                                                    *
 *  - 2024/02/17: ltovar - file creation                                       *
 * Copyright (c) 2024: LTovar                                                  *
 ******************************************************************************/

/************************************
 *          Includes                *
 ************************************/
#include <iostream>
#include <typeinfo>
#include "Semaphore.hpp"
#include <chrono>


// Wait and finish the process until Server will be implemented
void TerminateState(Context *context) {
    std::this_thread::sleep_for(std::chrono::seconds(30));
    context->EndSemaphore();
    std::cout << "salida de EndSemaphore" << std::endl;
}

/************************************
 *          Clases                  *
 ************************************/

void State::SetContext(Context* context)
{
    this->context_ = context;
};

Context::Context()
{
    this->TransitionTo(new Unknown);
}

Context::Context(State *state) : state_(nullptr)
{
    m_flag_terminate = false;
    t = new std::thread(TerminateState, this); 
    this->TransitionTo(state);
};

Context::~Context() {
    t->join();
    delete state_;
};

State_def State::GetState(){
    return m_state;
};

void State::SetState(State_def state_def){
    this->m_state = state_def;
};

void Context::SetSemaphore(bool red, bool yellow, bool green){
    std::cout << "Red: " << red << std::endl;
    std::cout << "Yellow: " << yellow << std::endl;
    std::cout << "Green: " << green << std::endl;
}

bool Context::GetFlagTerminate(){
    return m_flag_terminate;
};

void Context::TransitionTo(State *state){
    std::cerr << "Context: Transition to " << typeid(*state).name() << ".\n";
    if (nullptr != this->state_){
        state->SetState(this->state_->GetState()); // Set the new state
        delete this->state_;
    }
    this->state_ = state;
    this->state_->SetContext(this);
    this->state_->Run();
};

void Context::EndSemaphore(){
    m_flag_terminate = true;
};

/*******************************************************************************
 * File Name: Semaphore.hpp                                                    *
 * Description: This file is the header of the Semaphore state machine         *
 *              implementation.                                                *
 * Author: LTovar                                                              *
 * History:                                                                    *
 *  - 2024/02/17: ltovar - file creation                                       *
 * Copyright (c) 2024: LTovar                                                  *
 *******************************************************************************/

#ifndef SEMAPHORE_HPP
#define SEMAPHORE_HPP

#include <memory>
#include <thread>

/************************************
 *          Enums                   *
 ***********************************/

enum State_def{
    UNKNOWN,    ///< Represents the unknown state.
    OPENED,     ///< Represents the opened state.
    CLOSED,     ///< Represents the closed state.
    TRANSITION, ///< Represents the transition state.
    OTHERS      ///< Represents other undefined states.
};

/************************************
 *          Classes                 *
 ***********************************/

class Context;

/**
 * @brief Abstract base class for different states in the state machine.
 */
class State {
protected:
    Context *context_;  ///< Pointer to the context associated with the state.
    State_def m_state = OTHERS; ///< Current state of the state machine.
public:
    /**
     * @brief Virtual destructor for the State class.
     */
    virtual ~State(){};

    /**
     * @brief Pure virtual function to be implemented by derived classes.
     *        Represents the behavior of the state.
     */
    virtual void Run() = 0;

    /**
     * @brief Sets the context associated with the state.
     * @param context Pointer to the context object.
     */
    void SetContext(Context* context);

    /**
     * @brief Gets the current state of the state machine.
     * @return The current state of the state machine.
     */
    State_def GetState();

    /**
     * @brief Sets the state of the state machine.
     * @param state_def The new state to set.
     */
    void SetState(State_def state_def);
};

/**
 * @brief Class representing the context of the state machine.
 */
class Context {
private:
    State *state_;  ///< Pointer to the current state of the state machine.
    std::thread* t; ///< Pointer to the termination thread.
    bool m_flag_terminate;  ///< Flag indicating if the state machine should terminate.
public:
    /**
     * @brief Default constructor for the Context class.
     */
    Context();

    /**
     * @brief Constructor for the Context class.
     * @param state Pointer to the initial state of the state machine.
     */
    Context(State *state);

    /**
     * @brief Destructor for the Context class.
     */
    ~Context();

    /**
     * @brief Sets the semaphore state.
     * @param red Red semaphore state.
     * @param yellow Yellow semaphore state.
     * @param green Green semaphore state.
     */
    void SetSemaphore(bool red, bool yellow, bool green);

    /**
     * @brief Gets the flag indicating whether the state machine should terminate.
     * @return Flag indicating whether the state machine should terminate.
     */
    bool GetFlagTerminate();

    /**
     * @brief Transitions the state machine to a new state.
     * @param state Pointer to the new state.
     */
    void TransitionTo(State *state);

    /**
     * @brief Ends the semaphore state machine.
     */
    void EndSemaphore();
};

/**
 * @brief Class representing the initial state of the state machine.
 */
class Initialize : public State {
public:
    /**
     * @brief Default constructor for the Initialize class.
     */
    Initialize();

    /**
     * @brief Destructor for the Initialize class.
     */
    ~Initialize();

    /**
     * @brief Moves to the unknown state.
     */
    void GoToUnknown();
};

/**
 * @brief Class representing the transition state of the state machine.
 */
class Transition: public State {
private:
    bool thead_flag;
    State_def state;
public:
    /**
     * @brief Destructor for the Transition class.
     */
    ~Transition();

    /**
     * @brief Represents the behavior of the transition state.
     */
    void Run() override;

    /**
     * @brief Moves to the opened state.
     */
    void GoToOpened();

    /**
     * @brief Moves to the closed state.
     */
    void GoToClosed();

    /**
     * @brief Moves to the terminate state.
     */
    void GoToTerminate();
};

/**
 * @brief Class representing the unknown state of the state machine.
 */
class Unknown: public State {
private:
    bool thread_flag;
    State_def state;
public:
    /**
     * @brief Destructor for the Unknown class.
     */
    ~Unknown();

    /**
     * @brief Represents the behavior of the unknown state.
     */
    void Run() override;

    /**
     * @brief Moves to the opened state.
     */
    void GoToOpened();

    /**
     * @brief Moves to the closed state.
     */
    void GoToClosed();

    /**
     * @brief Moves to the terminate state.
     */
    void GoToTerminate();

    /**
     * @brief Performs flashing behavior.
     */
    void Flashing();
};

/**
 * @brief Class representing the opened state of the state machine.
 */
class Opened: public State {
private:
    bool thead_flag;
    State_def state;
public:
    /**
     * @brief Destructor for the Opened class.
     */
    ~Opened();

    /**
     * @brief Represents the behavior of the opened state.
     */
    void Run() override;

    /**
     * @brief Moves to the transition state.
     */
    void GoToTransition();

    /**
     * @brief Moves to the unknown state.
     */
    void GoToUnknown();

    /**
     * @brief Moves to the terminate state.
     */
    void GoToTerminate();
};

/**
 * @brief Class representing the closed state of the state machine.
 */
class Closed: public State {
private:
    bool thead_flag;
    State_def state;
public:
    /**
     * @brief Destructor for the Closed class.
     */
    ~Closed();

    /**
     * @brief Represents the behavior of the closed state.
     */
    void Run() override;

    /**
     * @brief Moves to the transition state.
     */
    void GoToTransition();

    /**
     * @brief Moves to the unknown state.
     */
    void GoToUnknown();

    /**
     * @brief Moves to the terminate state.
     */
    void GoToTerminate();
};

/**
 * @brief Class representing the terminate state of the state machine.
 */
class Terminate: public State {
public:
    /**
     * @brief Destructor for the Terminate class.
     */
    ~Terminate(){};

    /**
     * @brief Represents the behavior of the terminate state.
     */
    void Run() override{};
};

#endif /* SEMAPHORE_HPP */

#pragma once

enum class StateID { STATE_MENU, STATE_PLAY };

class GameState {
public:
    virtual void Input()  = 0;
    virtual void Run()    = 0;
    virtual void Render() = 0;

    StateID GetID()        { return currentState; }
    StateID GetNextState() { return nextState;    }

protected:
    StateID currentState;
    StateID nextState;
};
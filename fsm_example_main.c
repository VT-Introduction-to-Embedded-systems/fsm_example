// This is the code that is related to the example described in the below link:
// https://sites.google.com/vt.edu/introduction-to-embeddedsystem/finite-state-machines/detailed-example

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

typedef enum {SX, S2, S25, S253, S2534} passcode_state_t;

bool passcodeFSM(int guess);
int getGuessInput();
void playUnlockJingle();
void openLock();
void closeLock();

int main(void) {
    while (1) {
        // the getGuessInput() function will halt the program
        // until an input is received
        int input = getGuessInput();

        // passcodeFSM() is the function containing the FSM
        bool isUnlocked = passcodeFSM(input);

        if (isUnlocked)
            playUnlockJingle();
    }
}

int getGuessInput()
{
    // since we have not written any code that reads input from a keypad (we even don't have a keypad on this kit)
    // we use a synthetic input. In other words, we make up some input to test our fsm
    int guesses[10] = {1, 2, 5, 3, 4, 6, 2, 5, 6, 1};

    // using a static variable helps us to retain i so that we get a new input every time we return
    static int i = 0;
    int guess = guesses[i];
    i++;
    return (guess);
}

void playUnlockJingle() {

}
bool passcodeFSM(int guess) {
    static passcode_state_t currentState = SX;

    bool unlocked = false;

    switch (currentState) {
        case SX:
            if (guess == 2)
                currentState = S2;
            break;

        case S2:
            if (guess == 5)
                currentState = S25;
            else
                currentState = SX;
            break;

        case S25:
            if (guess == 3)
                currentState = S253;
            else
                currentState = SX;
            break;

        case S253:
            if (guess == 4)
            {
                currentState = S2534;
                unlocked = true;
            }
            else
                currentState = SX;
            break;

        case S2534:
            currentState = SX;
            break;
    }

    if (unlocked)
        openLock();
    else
        closeLock();

    return unlocked;
}

void openLock()
{

}
void closeLock(){

}

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>

typedef enum {SX, S1R, S2R, S3R, S4R, S1W, S2W, S3W, S4W} passcode_state_t;

#define INPUT_ARRAY_SIZE 15
#define PIN1st_DIGIT 9
#define PIN2nd_DIGIT 8
#define PIN3rd_DIGIT 7
#define PIN4th_DIGIT 6



bool passcodeFSM(int guess);
int getGuessInput();
void playUnlockJingle();
void openLock();
void closeLock();

int main(void) {
    printf ("FSM simulation of the lock with a 4-digit pin:\n");

    while (1) {
        // the getGuessInput() function will halt the program
        // until an input is received
        int input = getGuessInput();

        // passcodeFSM() is the function containing the FSM
        bool unlock = passcodeFSM(input);

        if (unlock)
            playUnlockJingle();
    }
}

int getGuessInput()
{
    // since we have not written any code that reads input from a keypad (we even don't have a keypad on this kit)
    // we use a synthetic input. In other words, we make up some input to test our fsm
    int guesses[INPUT_ARRAY_SIZE] = {9, 8, 7, 6, 0,
                                     9, 8, 7, 5, 0,
                                     1, 8, 7, 6, 0};

    // using a static variable helps us to retain i so that we get a new input every time we return
    static int i = 0;
    int guess = guesses[i%INPUT_ARRAY_SIZE];
    i++;
    return (guess);
}

void playUnlockJingle() {

}
bool passcodeFSM(int guess) {
    static passcode_state_t currentState = SX;

    bool unlock = false;

    printf ("current state is %d, input is %d", currentState, guess);

    switch (currentState) {
    case SX:
        if (guess == PIN1st_DIGIT)
            currentState = S1R;
        else
            currentState = S1W;
        break;


    case S1R:
        if (guess == PIN2nd_DIGIT)
            currentState = S2R;
        else
            currentState = S2W;
        break;

    case S2R:
        if (guess == PIN3rd_DIGIT)
            currentState = S3R;
        else
            currentState = S3W;
        break;

    case S3R:
        if (guess == PIN4th_DIGIT)
        {
            currentState = S4R;
            unlock = true;
        }
        else
            currentState = S4W;
        break;

    case S4R:
        currentState = SX;
        break;

    case S1W:
        currentState = S2W;
        break;

    case S2W:
        currentState = S3W;
        break;

    case S3W:
        currentState = S4W;
        break;

    case S4W:
        currentState = SX;
        break;

    }

    printf (", next state is %d, output is %d\n", currentState, unlock);

    if (unlock)
        openLock();
    else
        closeLock();

    return unlock;
}

void openLock()
{

}
void closeLock(){

}

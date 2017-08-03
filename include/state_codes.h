
#ifndef STATE_CODES_H
#define STATE_CODES_H

#define NUM_STATES (4)

#define STATE_MENU (0)
#define STATE_LEVEL (1)
#define STATE_PAUSE (2)
#define STATE_SCORES (3)

void init_state(int code);
void resume_state(int code);
void force_exit();

#endif

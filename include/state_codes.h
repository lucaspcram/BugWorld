
#ifndef STATE_CODES_H
#define STATE_CODES_H

#define NUM_STATES (3)
#define STATE_MENU (0)
#define STATE_LEVEL (1)
#define STATE_PAUSE (2)

void init_state(int code);
void resume_state(int code);

#endif

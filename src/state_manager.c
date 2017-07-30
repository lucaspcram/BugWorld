#include "state_manager.h"

#include <stdlib.h>

// TODO debug all this crap

void init_state_manager()
{
	states = (struct state_circbuf *) malloc(sizeof(*states));
	states->buf = (struct state **) malloc(sizeof(*(states->buf)) * M_CIRCBUF_SIZE);
	states->cur = 0;
}

void destroy_state_manager()
{
	free(states->buf);
	free(states);
}

void push_state(struct state_circbuf * buf, struct state * state)
{
	if (buf->cur == M_CIRCBUF_SIZE - 1)
		buf->cur = 0;
	else
		buf->cur++;


}

void pop_state(struct state_circbuf * buf)
{

}

struct state * peek_state(struct state_circbuf * buf)
{
	return buf->buf[buf->cur];
}

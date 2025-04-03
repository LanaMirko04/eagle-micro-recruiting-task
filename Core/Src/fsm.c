#include "fsm.h"

static fsm_state_t fsm_state;

void fsm_init(void) { fsm_state = FSM_STATE_INIT; }

fsm_state_t fsm_get_state(void) { return fsm_state; }

void fsm_update(fsm_event_t event) {
    if (FSM_EVENT_ERROR == event) {
        fsm_state = FSM_STATE_ERROR;
        return;
    }

    switch (fsm_state) {
    case FSM_STATE_INIT:
        fsm_state = FSM_STATE_WAIT_REQ;
        break;

    case FSM_STATE_WAIT_REQ:
        if (FSM_EVENT_BTN_PRESSED == event) {
            fsm_state = FSM_STATE_LISTENING;
        }
        break;

    case FSM_STATE_LISTENING:
        if (FSM_EVENT_BTN_PRESSED == event) {
            fsm_state = FSM_STATE_LISTENING;
        } else if (FSM_EVENT_WARNING == event) {
            fsm_state = FSM_STATE_WARNING;
        }
        break;

    case FSM_STATE_PAUSE:
        if (FSM_EVENT_BTN_PRESSED == event) {
            fsm_state = FSM_STATE_WAIT_REQ;
        }
        break;

    case FSM_STATE_WARNING:
        if (FSM_EVENT_BTN_PRESSED == event) {
            fsm_state = FSM_STATE_WAIT_REQ;
        }
        break;

    case FSM_STATE_ERROR:
    default:
        break;
    }
}

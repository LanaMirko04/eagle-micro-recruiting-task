#ifndef __FSM_H__
#define __FSM_H__

typedef enum {
    FSM_STATE_INIT,
    FSM_STATE_WAIT_REQ,
    FSM_STATE_LISTENING,
    FSM_STATE_PAUSE,
    FSM_STATE_WARNING,
    FSM_STATE_ERROR,
    FSM_STATE_NUM,
} fsm_state_t;

typedef enum {
    FSM_EVENT_NONE,
    FSM_EVENT_BTN_PRESSED,
    FSM_EVENT_WARNING,
    FSM_EVENT_ERROR
} fsm_event_t;

/**
 * @brief Initialize the FSM.
 */
void fsm_init(void);

/**
 * @brief Get the current state of the FSM.
 * @return The current state.
 */
fsm_state_t fsm_get_state(void);

/**
 * @brief Update the FSM current state.
 * @param event The event occured.
 */
void fsm_update(fsm_event_t event);

#endif // __FSM_H__

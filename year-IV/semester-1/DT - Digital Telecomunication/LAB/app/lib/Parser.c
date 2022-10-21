#include "Parser.h"

STATE_MACHINE_RETURN_VALUE parse_char(uint8_t current_char, uint32_t *state) {
    switch (*state) {
        case 0: { // starting state
            if (current_char == '\r') {
                *state = 1;
            }
            break;
        }
        case 1: { // <CR>
            if (current_char == '\n') {
                *state = 2;
                break;
            }
            return STATE_MACHINE_ERROR;
        }
        case 2: { // <CR><LF>
            if (current_char == 'O') {
                *state = 3;
                break;
            }
            else if (current_char == 'E') {
                *state = 4;
                break;
            }
            else if (current_char == '+') {
                *state = 10;
                break;
            }
            return STATE_MACHINE_ERROR;
        }
        case 3: { // "O"
            if (current_char == 'K') {
                *state = 8;
                break;
            }
            return STATE_MACHINE_ERROR;
        }
        case 4: { // "E"
            if (current_char == 'R') {
                *state = 5;
                break;
            }
            return STATE_MACHINE_ERROR;
        }
        case 5: { // "ER"
            if (current_char == 'R') {
                *state = 6;
                break;
            }
            return STATE_MACHINE_ERROR;
        }
        case 6: { // "ERR"
            if (current_char == 'O') {
                *state = 7;
                break;
            }
            return STATE_MACHINE_ERROR;
        }
        case 7: { // "ERRO"
            if (current_char == 'R') {
                *state = 8;
                break;
            }
            return STATE_MACHINE_ERROR;
        }
        case 8: { // "OK" or "ERROR"
           if (current_char == '\r') {
                *state = 9;
                break;
            } 
            return STATE_MACHINE_ERROR;            
        }
        case 9: { // <CR>
            if (current_char == '\n') {
                return STATE_MACHINE_READY;
            }
            return STATE_MACHINE_ERROR;
        }
        case 10: { // "+"
            if (' ' <= current_char && current_char <= '~') {
                *state = 11;
                break;
            }
            return STATE_MACHINE_ERROR;
        }
        case 11: { // "+"
            if (' ' <= current_char && current_char <= '~') {
                *state = 11;
                break;
            }
            else if (current_char == '\r') {
                *state = 12;
                break;
            }
            return STATE_MACHINE_ERROR;
        }
        case 12: {
            if (current_char == '\n') {
                *state = 13;
                break;
            }
            return STATE_MACHINE_ERROR;
        }
        case 13: {
            if (current_char == '+') {
                *state = 10;
                break;
            }
            else if (current_char == '\r') {
                *state = 14;
                break;
            }
            return STATE_MACHINE_ERROR;
        }
        case 14: {
            if (current_char == '\n') {
                *state = 15;
                break;
            }
            return STATE_MACHINE_ERROR;
        }
        case 15: {
            if (current_char == 'O') {
                *state = 3;
                break;
            }
            else if (current_char == 'E') {
                *state = 4;
                break;
            }
            return STATE_MACHINE_ERROR;
        }
    }
    return STATE_MACHINE_NOT_READY;
}

#include QMK_KEYBOARD_H

#define DEFAULT_LAYER 0
#define LAYER_1       1
#define LAYER_2       2


// Make sure when adding more variables that you add status messages for them.
// Whether vim edit mode binds are enabled or not.
bool vim_normal_mode = true;
// Whether the windows key is enabled or not.
bool windows_key_disabled = false;

// Run compile script without resetting keyboard.
void compile(void) {
	SEND_STRING("qmkcompilebsplit");
	tap_code16(KC_ENT);
}
// Run compile script and reset keyboard ready to be flashed.
void compileflash(void) {
	SEND_STRING("qmkcompilebsplit");
	tap_code16(KC_ENT);
	reset_keyboard();
}

/* Start handling macro keycodes. */
/* Announce existence of the keycode. */
enum custom_keycodes {
	LARR = SAFE_RANGE,
	RARR,
	NEQT,
	BCC,
	MODU,
	BXOR,
	BAND,
	MULT,
	ESUB,
	EADD,
	GTOE,
	LTOE,
	LLUN,
	DELB,
	LSUP,
	RSUP
};

/* Handle keycodes. */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case LARR:
			if (record->event.pressed) {
				// When keycode is pressed.
				SEND_STRING("<-");
			} else {
				// When keycode is released.
			}
			break;
		case RARR:
			if(record->event.pressed) {
				// When keycode is pressed.
				SEND_STRING("->");
			} else {
				// When keycode is released.
			}
			break;
		case NEQT:
			if(record->event.pressed) {
				// When keycode is pressed.
				SEND_STRING("!=");
			} else {
				// When keycode is released.
			}
			break;
		case BCC:
			if(record->event.pressed) {
				// When keycode is pressed.
				SEND_STRING("#+");
			} else {
				// When keycode is released.
			}
			break;
		case MODU:
			if(record->event.pressed) {
				// When keycode is pressed.
				SEND_STRING("%=");
			} else {
				// When keycode is released.
			}
			break;
		case BXOR:
			if(record->event.pressed) {
				// When keycode is pressed.
				SEND_STRING("^=");
			} else {
				// When keycode is released.
			}
			break;
		case BAND:
			if(record->event.pressed) {
				// When keycode is released.
				SEND_STRING("&=");
			} else {
				// When keycode is released.
			}
			break;
		case MULT:
			if(record->event.pressed) {
				// When keycode is pressed.
				SEND_STRING("*=");
			} else {
				// When keycode is released.
			}
			break;
		case ESUB:
			if(record->event.pressed) {
				// When keycode is pressed.
				SEND_STRING("-=");
			} else {
				// When keycode is released.
			}
			break;
		case EADD:
			if(record->event.pressed) {
				// When keycode is pressed.
				SEND_STRING("+=");
			} else {
				// When keycode is released.
			}
			break;
		case GTOE:
			if(record->event.pressed) {
				// When keycode is pressed.
				SEND_STRING(">=");
			} else {
				// When keycode is released.
			}
			break;
		case LTOE:
			if(record->event.pressed) {
				// When keycode is pressed.
				SEND_STRING("<=");
			} else {
				// When keycode is released.
			}
			break;
		case LLUN:
			if(record->event.pressed) {
				// When keycode is pressed.
				SEND_STRING("NULL");
			} else {
				// When keycode is released.
			}
			break;
		case DELB:
			if(record->event.pressed) {
				// When keycode is pressed.
				if(vim_normal_mode == true) {
					SEND_STRING("c");
					tap_code16(KC_BSPC);
					tap_code16(KC_DEL);
					tap_code16(C(KC_R));
					tap_code16(KC_DQUO);
					tap_code16(KC_ESC);
				} else {
					tap_code16(C(KC_X));
					tap_code16(KC_BSPC);
					tap_code16(KC_DEL);
					tap_code16(C(KC_V));
				}
			} else {
				// When keycode is released.
			}
			break;
		case LSUP:
			if(windows_key_disabled == false) {
				if(record->event.pressed) {
					// When keycode is pressed.
					register_code16(KC_LGUI);
				} else {
					// When keycode is released.
					unregister_code16(KC_LGUI);
				}
			}
			break;
		case RSUP:
			if(windows_key_disabled == false) {
				if(record->event.pressed) {
					// When keycode is pressed.
					register_code16(KC_RGUI);
				} else {
					// When keycode is released.
					unregister_code16(KC_RGUI);
				}
			}
			break;
	}
	return true;
};
/* End handling macro keycodes. */


/* Start handling tap dance keycodes. */
enum {
    TD_FLAB,
	TD_FRAB,
	TD_PPRN,
	TD_APRN,
	TD_PCBR,
	TD_ACBR,
	TD_PBRC,
	TD_ABRC,
	TD_PABK,
	TD_AABK,
	TD_QUOT,
	TD_DQUO,
	TD_COMM,
	TD_LCOM,
	TD_RCOM
};


typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;


enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP, // Send two single taps
    TRIPLE_TAP,
    TRIPLE_HOLD
};


// Create an instance of 'tap' for the 'x' tap dance.
static tap xtap_state = {
    .is_press_action = true,
    .state = 0
};


// This is to handle multiple taps and holds as opposed to just taps.
// Call this at the start of a TD function and pass the return value to xtap_state.state.
uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        // DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    } else return 8; // Magic number. At some point this method will expand to work for more presses
}


// Less than or equal to.
// <=
// Left arrow.
// <-
void dance_flab_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == SINGLE_TAP) {
		// One tap.
		SEND_STRING("<");
    } else {
		// Double tap.
		SEND_STRING("<");
    }
}
void dance_flab_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == SINGLE_TAP) {
		// One tap.
		SEND_STRING("-");
    } else {
		// Double tap.
		SEND_STRING("=");
    }
}


// Greater than or equal to.
// >=
// Right arrow. (member pointed to arrow operator)
// ->
void dance_frab_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == SINGLE_TAP) {
		// One tap.
		SEND_STRING("-");
    } else {
		// Double tap.
		SEND_STRING(">");
    }
}
void dance_frab_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == SINGLE_TAP) {
		// One tap.
		SEND_STRING(">");
    } else {
		// Double tap.
		SEND_STRING("=");
    }
}

// Put characters to the left and right of a chunk of text.
// Used for all of the functions immediately below to add brackets to things.
void surround(uint16_t left, uint16_t right) {
	if(vim_normal_mode == true) {
		// Change (cut) highlighted text.
		SEND_STRING("c");
		// Add the new character to the left.
		tap_code16(left);
		// Paste removed text.
		tap_code16(C(KC_R));
		// Register is cut text.
		tap_code16(KC_DQUO);
		// Add the new character to the right.
		tap_code16(right);
		// Move the cursor.
		tap_code16(KC_LEFT);
		// Escape back to normal mode.
		tap_code16(KC_ESC);
	} else {
		// Cut the highlighted text.
		tap_code16(C(KC_X));
		// Add the new character to the left.
		tap_code16(left);
		// Paste the text back.
		tap_code16(C(KC_V));
		// Add the new character to the right.
		tap_code16(right);
	}
}


// This is the code that all of the bracket keys below use.
// Handle left bracket keys.
void bracketTap_left(int l_bracket, int r_bracket, qk_tap_dance_state_t *state, void *user_data) {
	xtap_state.state = cur_dance(state);
	switch(xtap_state.state) {
		case SINGLE_TAP:
			// One tap.
			register_code16(l_bracket);
			break;
		case DOUBLE_TAP:
			// Double tap.
			tap_code16(l_bracket);
			tap_code16(l_bracket);
			break;
		case SINGLE_HOLD:
			// Hold key.
			tap_code16(l_bracket);
			tap_code16(r_bracket);
			tap_code16(KC_LEFT);
			break;
    }
}

// Handle right bracket keys.
void bracketTap_right(int l_bracket, int r_bracket, qk_tap_dance_state_t *state, void *user_data) {
	xtap_state.state = cur_dance(state);
	switch(xtap_state.state) {
		case SINGLE_TAP:
			// One tap.
			register_code16(r_bracket);
			break;
		case DOUBLE_TAP:
			// Double tap.
			tap_code16(r_bracket);
			tap_code16(r_bracket);
			break;
		case SINGLE_HOLD:
			// Hold key.
			surround(l_bracket, r_bracket);
			break;
	}
}


// Parenthesis ()
// Left
void dance_pprn_finished(qk_tap_dance_state_t *state, void *user_data) {
	bracketTap_left(KC_LPRN, KC_RPRN, state, user_data);
}
void dance_pprn_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == SINGLE_TAP) {
		// One tap.
		unregister_code16(KC_LPRN);
    } else {
		// Double tap.
    }
}
// Right
void dance_aprn_finished(qk_tap_dance_state_t *state, void *user_data) {
	bracketTap_right(KC_LPRN, KC_RPRN, state, user_data);
}
void dance_aprn_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == SINGLE_TAP) {
		// One tap.
		unregister_code16(KC_RPRN);
    } else {
		// Double tap.
    }
}

// Curled braces {}
// Left
void dance_pcbr_finished(qk_tap_dance_state_t *state, void *user_data) {
	bracketTap_left(KC_LCBR, KC_RCBR, state, user_data);
}
void dance_pcbr_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == SINGLE_TAP) {
		// One tap.
		unregister_code16(KC_LCBR);
    } else {
		// Double tap.
    }
}
// Right
void dance_acbr_finished(qk_tap_dance_state_t *state, void *user_data) {
	bracketTap_right(KC_LCBR, KC_RCBR, state, user_data);
}
void dance_acbr_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == SINGLE_TAP) {
		// One tap.
		unregister_code16(KC_RCBR);
    } else {
		// Double tap.
    }
}

// Braces []
// Left
void dance_pbrc_finished(qk_tap_dance_state_t *state, void *user_data) {
	bracketTap_left(KC_LBRC, KC_RBRC, state, user_data);
}
void dance_pbrc_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == SINGLE_TAP) {
		// One tap.
		unregister_code16(KC_LBRC);
    } else {
		// Double tap.
    }
}
// Right
void dance_abrc_finished(qk_tap_dance_state_t *state, void *user_data) {
	bracketTap_right(KC_LBRC, KC_RBRC, state, user_data);
}
void dance_abrc_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == SINGLE_TAP) {
		// One tap.
		unregister_code16(KC_RBRC);
    } else {
		// Double tap.
    }
}

// Angle brackets <>
// Left
void dance_pabk_finished(qk_tap_dance_state_t *state, void *user_data) {
	bracketTap_left(KC_LABK, KC_RABK, state, user_data);
}
void dance_pabk_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == SINGLE_TAP) {
		// One tap.
		unregister_code16(KC_LABK);
    } else {
		// Double tap.
    }
}
// Right
void dance_aabk_finished(qk_tap_dance_state_t *state, void *user_data) {
	bracketTap_right(KC_LABK, KC_RABK, state, user_data);
}
void dance_aabk_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == SINGLE_TAP) {
		// One tap.
		unregister_code16(KC_RABK);
    } else {
		// Double tap.
    }
}


// Quotes ''
void dance_quot_finished(qk_tap_dance_state_t *state, void *user_data) {
	xtap_state.state = cur_dance(state);
	switch(xtap_state.state) {
		case SINGLE_TAP:
			// One tap.
			tap_code16(KC_QUOT);
			tap_code16(KC_QUOT);
			tap_code16(KC_LEFT);
			break;
		case SINGLE_HOLD:
			// Hold key.
			surround(KC_QUOT, KC_QUOT);
			break;
	}
}
void dance_quot_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == SINGLE_TAP) {
		// One tap.
    } else {
		// Double tap.
    }
}
// Quotes ""
void dance_dquo_finished(qk_tap_dance_state_t *state, void *user_data) {
	xtap_state.state = cur_dance(state);
	switch(xtap_state.state) {
		case SINGLE_TAP:
			// One tap.
			tap_code16(KC_DQUO);
			tap_code16(KC_DQUO);
			tap_code16(KC_LEFT);
			break;
		case SINGLE_HOLD:
			// Hold key.
			surround(KC_DQUO, KC_DQUO);
			break;
	}
}
void dance_dquo_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == SINGLE_TAP) {
		// One tap.
    } else {
		// Double tap.
    }
}


// c/c++ style comments.
// Comment line.
// Remove comment.
void dance_comm_finished(qk_tap_dance_state_t *state, void *user_data) {
	// Check if we're in vim edit mode or not,
	//+then move to the start of the line in the appropriate manner.
	if (vim_normal_mode == true) {
		SEND_STRING("I");
	} else {
		tap_code16(KC_HOME);
	}
	// Comment the line.
	if (state->count == SINGLE_TAP) {
		// One tap.
		SEND_STRING("//");
	} else {
		// Double tap.
		tap_code16(KC_DEL);
		tap_code16(KC_DEL);
	}
}
void dance_comm_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == SINGLE_TAP) {
		// One tap.
	} else {
		// Double tap.
    }
	// Only hit escape if using vim in order to return to normal mode.
	if (vim_normal_mode == true) {
		tap_code16(KC_ESC);
	}
}
// Pipe is cursor.
// /*
// /* |*/
void dance_lcom_finished(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == SINGLE_TAP) {
		// One tap.
		tap_code16(KC_SLSH);
		tap_code16(KC_ASTR);
	} else {
		// Double tap.
		SEND_STRING("/* */");
	}
}
void dance_lcom_reset(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == SINGLE_TAP) {
		// One tap.
	} else {
		// Double tap.
		tap_code16(KC_LEFT);
		tap_code16(KC_LEFT);
	}
}
// */
//  *+
//  /* Text */
void dance_rcom_finished(qk_tap_dance_state_t *state, void *user_data) {
	xtap_state.state = cur_dance(state);
	switch(xtap_state.state) {
		case SINGLE_TAP:
			tap_code16(KC_ASTR);
			tap_code16(KC_SLSH);
			break;
		case SINGLE_HOLD:
			/*
			 *+My surround function can't handle multiple characters because
			 *+SEND_STRING is a precompiler macro so this is almost a copy of
			 *+that function.
			 */
			if(vim_normal_mode == true) {
				// Change (cut) highlighted text.
				SEND_STRING("c");
				// Add the new character to the left.
				SEND_STRING("/*");
				// Paste removed text.
				tap_code16(C(KC_R));
				// Register is cut text.
				tap_code16(KC_DQUO);
				// Add the new character to the right.
				SEND_STRING("*/");
				// Move the cursor.
				tap_code16(KC_LEFT);
				// Escape back to normal mode.
				tap_code16(KC_ESC);
			} else {
				// Cut the highlighted text.
				tap_code16(C(KC_X));
				// Add the new character to the left.
				SEND_STRING("/*");
				// Paste the text back.
				tap_code16(C(KC_V));
				// Add the new characters to the right.
				SEND_STRING("*/");
			}
			break;
		case DOUBLE_TAP:
			SEND_STRING("*+");
			break;
	}
}
void dance_rcom_reset(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == SINGLE_TAP) {
		// One tap.
	} else {
		// Double tap.
	}
}


qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_FLAB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_flab_finished, dance_flab_reset),
    [TD_FRAB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_frab_finished, dance_frab_reset),
	[TD_PPRN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_pprn_finished, dance_pprn_reset),
	[TD_APRN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_aprn_finished, dance_aprn_reset),
	[TD_PCBR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_pcbr_finished, dance_pcbr_reset),
	[TD_ACBR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_acbr_finished, dance_acbr_reset),
	[TD_PBRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_pbrc_finished, dance_pbrc_reset),
	[TD_ABRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_abrc_finished, dance_abrc_reset),
	[TD_PABK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_pabk_finished, dance_pabk_reset),
	[TD_AABK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_aabk_finished, dance_aabk_reset),
	[TD_QUOT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_quot_finished, dance_quot_reset),
	[TD_DQUO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_dquo_finished, dance_dquo_reset),
	[TD_COMM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_comm_finished, dance_comm_reset),
	[TD_LCOM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_lcom_finished, dance_lcom_reset),
	[TD_RCOM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_rcom_finished, dance_rcom_reset)
};
/* End handling tap dance keycodes. */




/* Start handling leader key sequences. */
LEADER_EXTERNS();

void matrix_scan_user(void) {
	LEADER_DICTIONARY() {
		leading = false;
		// Put lead sequences in here.


		


		// Owner
		SEQ_FOUR_KEYS(KC_R, KC_O, KC_O, KC_T) {
			SEND_STRING("root == Matthew James Hulme");
		}

		// e-mail address
		SEQ_ONE_KEY(KC_2) {
			SEND_STRING("jager.mh@gmail.com");
		}

		// Run compile script.
		SEQ_FOUR_KEYS(KC_C, KC_O, KC_M, KC_P) {
			compile();
		}
		// Run compile script and flash.
		SEQ_FIVE_KEYS(KC_F, KC_L, KC_A, KC_S, KC_H) {
			compileflash();
		}

		// c main function
		SEQ_FOUR_KEYS(KC_M, KC_A, KC_I, KC_N) {
			SEND_STRING("int main(int argc, char *argv[]) {");
			tap_code16(KC_ENT);
			tap_code16(KC_RCBR);
		}

		// Print status message.
		SEQ_THREE_KEYS(KC_R, KC_E, KC_G) {
			size_t backspace_count = 0;
			tap_code16(KC_HOME);
			if(vim_normal_mode) {
				SEND_STRING("IVim mode: ON");
				backspace_count += 12;
			} else {
				SEND_STRING("Vim mode: OFF");
				backspace_count += 13;
			}
			SEND_STRING(", Super key: ");
			backspace_count += 13;
			if(windows_key_disabled) {
				SEND_STRING("Disabled");
				backspace_count += 8;
			} else {
				SEND_STRING("Enabled");
				backspace_count += 7;
			}
			//tap_code16(KC_ENT);
			_delay_ms(2500);

			// Remove the status text from the screen.
			for(size_t i = 0; i < backspace_count; i++) {
				tap_code16(KC_BSPC);
			}
		}

		// Turn the vim mode setting on or off.
		SEQ_THREE_KEYS(KC_V, KC_I, KC_M) {
			vim_normal_mode = true;
			// Display updated status.
			SEND_STRING("IVim mode: ON");
			_delay_ms(2000);
			// Remove the status text from the screen.
			for(size_t i = 0; i < 12; i++) {
				tap_code16(KC_BSPC);
			}
			tap_code16(KC_ESC);
		}
		SEQ_FIVE_KEYS(KC_N, KC_O, KC_V, KC_I, KC_M) {
			vim_normal_mode = false;
			// Display updated status.
			tap_code16(KC_HOME);
			SEND_STRING("Vim mode: OFF");
			_delay_ms(2000);
			// Remove the status text from the screen.
			for(size_t i = 0; i < 13; i++) {
				tap_code16(KC_BSPC);
			}
		}

		// Turn the windows key on or off.
		SEQ_THREE_KEYS(KC_W, KC_I, KC_N) {
			windows_key_disabled = false;
		}
		SEQ_FIVE_KEYS(KC_N, KC_O, KC_W, KC_I, KC_N) {
			windows_key_disabled = true;
		}


		// Open the calculator.
		SEQ_FOUR_KEYS(KC_C, KC_A, KC_L, KC_C) {
			tap_code16(KC_CALC);
		}

		// Type the head of an HTML5 file.
		SEQ_FOUR_KEYS(KC_H, KC_T, KC_M, KC_L) {
			// Line number:
			// 1
			SEND_STRING("<!DOCTYPE html>"); tap_code16(KC_ENT);
			// 2
			SEND_STRING("<html>"); tap_code16(KC_ENT);
			// 3
			SEND_STRING("<head>"); tap_code16(KC_ENT);
			// 4
			SEND_STRING("<meta charset=");
			tap_code16(KC_DQUO);
			SEND_STRING("utf-8");
			tap_code16(KC_DQUO);
			SEND_STRING("/>");
			tap_code16(KC_ENT);
			// 5
			SEND_STRING("<meta name=");
			tap_code16(KC_DQUO);
			SEND_STRING("description");
			tap_code16(KC_DQUO);
			SEND_STRING(" content=");
			tap_code16(KC_DQUO);
			tap_code16(KC_DQUO);
			SEND_STRING("/>");
			tap_code16(KC_ENT);
			// 6
			SEND_STRING("<meta name=");
			tap_code16(KC_DQUO);
			SEND_STRING("keywords");
			tap_code16(KC_DQUO);
			SEND_STRING(" content=");
			tap_code16(KC_DQUO);
			SEND_STRING("HTML, something, else");
			tap_code16(KC_DQUO);
			SEND_STRING("/>");
			tap_code16(KC_ENT);
			// 7
			SEND_STRING("<meta name=");
			tap_code16(KC_DQUO);
			SEND_STRING("author");
			tap_code16(KC_DQUO);
			SEND_STRING(" content=");
			tap_code16(KC_DQUO);
			SEND_STRING("Matthew Hulme");
			tap_code16(KC_DQUO);
			SEND_STRING("/>");
			tap_code16(KC_ENT);
			// 8
			SEND_STRING("<title>Title</title>"); tap_code16(KC_ENT);
			// 9
			SEND_STRING("</head>"); tap_code16(KC_ENT);
			// 10
			SEND_STRING("<body>"); tap_code16(KC_ENT);
			// 11
			SEND_STRING("</body>"); tap_code16(KC_ENT);
			// 12
			SEND_STRING("</html>"); tap_code16(KC_ENT);
			// Escape
			//tap_code16(KC_ESC);
		}

		// Obscure keys
		// SysReq / Attention
		SEQ_FIVE_KEYS(KC_S, KC_Y, KC_S, KC_R, KC_Q) {
			tap_code16(KC_SYSREQ);
		}

		// Print Screen key
		SEQ_FIVE_KEYS(KC_P, KC_R, KC_I, KC_N, KC_T) {
			tap_code16(KC_PSCR);
		}

		// Pause / Break key
		SEQ_FIVE_KEYS(KC_P, KC_A, KC_U, KC_S, KC_E) {
			tap_code16(KC_PAUS);
		}

		// Insert key
		SEQ_THREE_KEYS(KC_I, KC_N, KC_S) {
			tap_code16(KC_INS);
		}

		/*
		// HTML Paragraph tag <p> / </p>
		SEQ_ONE_KEY(KC_P) {
			SEND_STRING("<p>");
		}
		SEQ_TWO_KEYS(KC_SLSH, KC_P) {
			SEND_STRING("</p>");
		}
		*/

		// Print LaTeX when latex is typed.
		SEQ_FIVE_KEYS(KC_L, KC_A, KC_T, KC_E, KC_X) {
			SEND_STRING("LaTeX");
		}

		// Print help message for these commands.
		SEQ_FOUR_KEYS(KC_H, KC_E, KC_L, KC_P) {
			SEND_STRING("root (owner), 2 (email), comp (compile), flash, ");
			SEND_STRING("main (c main function), reg (settings), vim, novim, ");
			SEND_STRING("win, nowin, calc (calculator), sysrq (SysRq), ");
			SEND_STRING("print (print screen), pause (pause/break), ");
			SEND_STRING("ins (insert)");
		}

		// Make escape kill the sequence.
		SEQ_ONE_KEY(KC_GESC) {leader_end();}
		SEQ_ONE_KEY(KC_ESC) {leader_end();}


		// If none of these match the sequence then end the sequence.
		leader_end();
	}
}
/* End handling leader key sequences. */




/*
PERSONAL KEYMAPPING JAGERMAP

-------------------------------------------------------------------------------------------
| K00 | K01 | K02 | K03 | K04 | K05 | K06 | K07 | K08 | K09 | K0A | K0B | K0C | K0D | K2D |
-------------------------------------------------------------------------------------------
|  K10   | K11 | K12 | K13 | K14 | K15 | K16 | K17 | K18 | K19 | K1A | K1B | K1C |  K1D   |
-------------------------------------------------------------------------------------------
|   K20   | K21 | K22 | K23 | K24 | K25 | K26 | K27 | K28 | K29 | K2A | K2B |     K2C     |
-------------------------------------------------------------------------------------------
|  K30  |XK31X| K32 | K33 | K34 | K35 | K36 | K37 | K38 | K39 | K3A | K3B |   K3C   | K3D |
-------------------------------------------------------------------------------------------
|  K40  |  K41  |  K42  |     K44     |  K45  |     K46     | K48 | K49 |XK4AX| K4B | K4C |
-------------------------------------------------------------------------------------------


Empty layer:

[LAYER_?] = KEYMAP_JAGERMAP( \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS  \
  ),

*/


/* Start key mapping. */
/* DEFAULT_LAYER */
/* CapsLock function key layer. */
/* Middle space function key layer. */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [DEFAULT_LAYER] = LAYOUT_jagermap(
    KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS,   KC_GRV, \
    KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,  TD(TD_LCOM),  TD(TD_RCOM), KC_BSPC, \
    MO(LAYER_1),   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,   KC_QUOT,  KC_ENT, \
    KC_LSFT,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,  KC_DOT,  KC_SLSH,  KC_RSFT, KC_LCAP, \
    KC_LCTL,  LSUP,  KC_LALT,		KC_ENT,		MO(LAYER_2),	KC_SPC,		KC_RALT, RSUP, KC_NO, KC_APP, KC_RCTL \
  ),

  [LAYER_1] = LAYOUT_jagermap(
    LCA(KC_DEL), KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_UP, KC_PGDN, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END, KC_TRNS, KC_LEAD, \
    KC_TRNS, KC_TRNS, S(KC_X), S(KC_C), S(KC_V), KC_TRNS, KC_END, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_UNDS,          KC_TRNS, KC_TRNS, KC_NO, KC_TRNS, KC_PSCR  \
  ),

  [LAYER_2] = LAYOUT_jagermap(
    KC_TRNS, NEQT, S(KC_2), BCC, S(KC_4), MODU, BXOR, BAND, MULT, S(KC_9), S(KC_0), ESUB, EADD, KC_TRNS, KC_TRNS, \
    KC_TRNS, TD(TD_DQUO), KC_TRNS, KC_EQL, KC_TRNS, KC_GRV, KC_TRNS, KC_TRNS, S(KC_PIPE), KC_TRNS, KC_PLUS, KC_TRNS, KC_TRNS, DELB, \
    KC_TRNS, TD(TD_PABK), TD(TD_PBRC), TD(TD_PCBR), TD(TD_PPRN), KC_BSLS, KC_SLSH, TD(TD_APRN), TD(TD_ACBR), TD(TD_ABRC), TD(TD_AABK), TD(TD_QUOT), KC_TRNS, \
    KC_TRNS, KC_TRNS, KC_TRNS, TD(TD_COMM), KC_TRNS, KC_TRNS, LLUN, KC_MINS, TD(TD_FLAB), TD(TD_FRAB), KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_SPC,          KC_TRNS, KC_TRNS, KC_NO, KC_TRNS, KC_LOCK  \
  )
};
/* End key mapping. */


/* Start combo handling. */

/*
// Remember to change COMBO_COUNT in config.h accordingly.
enum combo_events {
  CNR_REC,
  CNR_RST
};

// Declarations of combos.
// Copy paste examples.
//const uint16_t PROGMEM copy_combo[] = {KC_Z, KC_C, COMBO_END};
//const uint16_t PROGMEM paste_combo[] = {KC_X, KC_V, COMBO_END};

// Run flashing script and reset keyboard ready for flashing.
const uint16_t PROGMEM compile_combo[] = {KC_LCTL, KC_RCTL, KC_LALT, KC_RALT, COMBO_END};
const uint16_t PROGMEM reset_combo[] = {KC_LCTL, KC_RCTL, KC_TAB, KC_BSPC, COMBO_END};

// Link combo to action.
combo_t key_combos[COMBO_COUNT] = {
  [CNR_REC] = COMBO_ACTION(compile_combo),
  [CNR_RST] = COMBO_ACTION(reset_combo)
};

// Combo action.
void process_combo_event(uint8_t combo_index, bool pressed) {
  switch(combo_index) {
	case CNR_REC:
	  if(pressed) {
		  compile();
	  }
	  break;
    case CNR_RST:
      if(pressed) {
		  compileflash();
	  }
      break;
  }
}
*/
/* End combo handling. */




/*

Keycode Index



#	Long Name 	Short Name 	Description
#	KC_1
#	KC_2
#	KC_3
#	KC_4
#	KC_5
#	KC_6
#	KC_7
#	KC_8
#	KC_9
#	KC_0
#	KC_F1
#	KC_F2
#	KC_F3
#	KC_F4
#	KC_F5
#	KC_F6
#	KC_F7
#	KC_F8
#	KC_F9
#	KC_F10
#	KC_F11
#	KC_F12
#	KC_F13
#	KC_F14
#	KC_F15
#	KC_F16
#	KC_F17
#	KC_F18
#	KC_F19
#	KC_F20
#	KC_F21
#	KC_F22
#	KC_F23
#	KC_F24
#	KC_A
#	KC_B
#	KC_C
#	KC_D
#	KC_E
#	KC_F
#	KC_G
#	KC_H
#	KC_I
#	KC_J
#	KC_K
#	KC_L
#	KC_M
#	KC_N
#	KC_O
#	KC_P
#	KC_Q
#	KC_R
#	KC_S
#	KC_T
#	KC_U
#	KC_V
#	KC_W
#	KC_X
#	KC_Y
#	KC_Z
#	KC_ENTER 	KC_ENT 	Return (ENTER)
#	KC_ESCAPE 	KC_ESC 	ESCAPE
#	KC_BSPACE 	KC_BSPC 	DELETE (Backspace)
#	KC_TAB 		Tab
#	KC_SPACE 	KC_SPC 	Spacebar
#	KC_MINUS 	KC_MINS 	- and _
#	KC_EQUAL 	KC_EQL 	= and +
#	KC_LBRACKET 	KC_LBRC 	[ and {
#	KC_RBRACKET 	KC_RBRC 	] and }
#	KC_BSLASH 	KC_BSLS 	\ and |
#	KC_NONUS_HASH 	KC_NUHS 	Non-US # and ~
#	KC_NONUS_BSLASH 	KC_NUBS 	Non-US \ and |
#	KC_INT1 	KC_RO 	JIS \ and |
#	KC_INT2 	KC_KANA 	International216
#	KC_INT3 	KC_JYEN 	Yen Symbol (¥)
#	KC_SCOLON 	KC_SCLN 	; and :
#	KC_QUOTE 	KC_QUOT 	‘ and “
#	KC_GRAVE 	KC_GRV 	Grave Accent and Tilde
#	KC_COMMA 	KC_COMM 	, and <
#	KC_DOT 		. and >
#	KC_SLASH 	KC_SLSH 	/ and ?
#	KC_CAPSLOCK 	KC_CAPS 	Caps Lock
#	KC_LCTRL 	KC_LCTL 	LeftControl
#	KC_LSHIFT 	KC_LSFT 	LeftShift
#	KC_LALT 		LeftAlt
#	KC_LGUI 		Left GUI(Windows/Apple/Meta key)
#	KC_RCTRL 	KC_RCTL 	RightControl
#	KC_RSHIFT 	KC_RSFT 	RightShift
#	KC_RALT 		RightAlt
#	KC_RGUI 		Right GUI(Windows/Apple/Meta key)
#	KC_LOCKING_CAPS 	KC_LCAP 	Locking Caps Lock
#	KC_LOCKING_NUM 	KC_LNUM 	Locking Num Lock
#	KC_LOCKING_SCROLL 	KC_LSCR 	Locking Scroll Lock
#	KC_INT4 	KC_HENK 	JIS Henken
#	KC_INT5 	KC_MHEN 	JIS Muhenken
#	KC_PSCREEN 	KC_PSCR 	PrintScreen
#	KC_SCROLLLOCK 	KC_SLCK 	Scroll Lock
#	KC_PAUSE 	KC_PAUS 	Pause
#	KC_INSERT 	KC_INS 	Insert
#	KC_HOME 		Home
#	KC_PGUP 		PageUp
#	KC_DELETE 	KC_DEL 	Delete Forward
#	KC_END 		End
#	KC_PGDOWN 	KC_PGDN 	PageDown
#	KC_RIGHT 	KC_RGHT 	RightArrow
#	KC_LEFT 		LeftArrow
#	KC_DOWN 		DownArrow
#	KC_UP 		UpArrow
#	KC_APPLICATION 	KC_APP 	Application
#	KC_POWER 		Power
#	KC_EXECUTE 		Execute
#	KC_HELP 		Help
#	KC_MENU 		Menu
#	KC_SELECT 		Select
#	KC_AGAIN 		Again
#	KC_UNDO 		Undo
#	KC_CUT 		Cut
#	KC_COPY 		Copy
#	KC_PASTE 		Paste
#	KC_FIND 		Find
#	KC_ALT_ERASE 		Alternate Erase
#	KC_SYSREQ 		SysReq/Attention
#	KC_CANCEL 		Cancel
#	KC_CLEAR 		Clear
#	KC_PRIOR 		Prior
#	KC_RETURN 		Return
#	KC_SEPARATOR 		Separator
#	KC_OUT 		Out
#	KC_OPER 		Oper
#	KC_CLEAR_AGAIN 		Clear/Again
#	KC_CRSEL 		CrSel/Props
#	KC_EXSEL 		ExSel
#	KC_SYSTEM_POWER 	KC_PWR 	System Power Down
#	KC_SYSTEM_SLEEP 	KC_SLEP 	System Sleep
#	KC_SYSTEM_WAKE 	KC_WAKE 	System Wake
#	KC_MAIL 	KC_MAIL
#	KC_CALCULATOR 	KC_CALC
#	KC_MY_COMPUTER 	KC_MYCM
#	KC_WWW_SEARCH 	KC_WSCH
#	KC_WWW_HOME 	KC_WHOM
#	KC_WWW_BACK 	KC_WBAK
#	KC_WWW_FORWARD 	KC_WFWD
#	KC_WWW_STOP 	KC_WSTP
#	KC_WWW_REFRESH 	KC_WREF
#	KC_WWW_FAVORITES 	KC_WFAV
#	KC_STOP 		Stop
#	KC__MUTE 		Mute (macOS)
#	KC__VOLUP 		Volume Up (macOS)
#	KC__VOLDOWN 		Volume Down (macOS)
#	KC_AUDIO_MUTE 	KC_MUTE 	Mute (Windows/macOS/Linux)
#	KC_AUDIO_VOL_UP 	KC_VOLU 	Volume Up (Windows/macOS/Linux)
#	KC_AUDIO_VOL_DOWN 	KC_VOLD 	Volume Down (Windows/macOS/Linux)
#	KC_MEDIA_NEXT_TRACK 	KC_MNXT 	Next Track (Windows)
#	KC_MEDIA_PREV_TRACK 	KC_MPRV 	Previous Track (Windows)
#	KC_MEDIA_FAST_FORWARD 	KC_MFFD 	Next Track (macOS)
#	KC_MEDIA_REWIND 	KC_MRWD 	Previous Track (macOS)
#	KC_MEDIA_STOP 	KC_MSTP
#	KC_MEDIA_PLAY_PAUSE 	KC_MPLY
#	KC_MEDIA_SELECT 	KC_MSEL
#	KC_NUMLOCK 	KC_NLCK 	Keypad Num Lock and Clear
#	KC_KP_SLASH 	KC_PSLS 	Keypad /
#	KC_KP_ASTERISK 	KC_PAST 	Keypad *
#	KC_KP_MINUS 	KC_PMNS 	Keypad -
#	KC_KP_PLUS 	KC_PPLS 	Keypad +
#	KC_KP_ENTER 	KC_PENT 	Keypad ENTER`
#	KC_KP_1 	KC_P1 	Keypad 1 and End
#	KC_KP_2 	KC_P2 	Keypad 2 and Down Arrow
#	KC_KP_3 	KC_P3 	Keypad 3 and PageDn
#	KC_KP_4 	KC_P4 	Keypad 4 and Left Arrow
#	KC_KP_5 	KC_P5 	Keypad 5
#	KC_KP_6 	KC_P6 	Keypad 6 and Right Arrow
#	KC_KP_7 	KC_P7 	Keypad 7 and Home
#	KC_KP_8 	KC_P8 	Keypad 8 and Up Arrow
#	KC_KP_9 	KC_P9 	Keypad 9 and PageUp
#	KC_KP_0 	KC_P0 	Keypad 0 and Insert
#	KC_KP_DOT 	KC_PDOT 	Keypad . and Delete
#	KC_KP_EQUAL 	KC_PEQL 	Keypad =
#	KC_KP_COMMA 	KC_PCMM 	Keypad Comma
#	KC_KP_EQUAL_AS400 		Keypad Equal Sign
#	KC_NO 		Ignore this key. (NOOP)
#	KC_TRNS 		Make this key transparent to find the key on a lower layer.
#	KC_MS_UP 	KC_MS_U 	Mouse Cursor Up
#	KC_MS_DOWN 	KC_MS_D 	Mouse Cursor Down
#	KC_MS_LEFT 	KC_MS_L 	Mouse Cursor Left
#	KC_MS_RIGHT 	KC_MS_R 	Mouse Cursor Right
#	KC_MS_BTN1 	KC_BTN1 	Mouse Button 1
#	KC_MS_BTN2 	KC_BTN2 	Mouse Button 2
#	KC_MS_BTN3 	KC_BTN3 	Mouse Button 3
#	KC_MS_BTN4 	KC_BTN4 	Mouse Button 4
#	KC_MS_BTN5 	KC_BTN5 	Mouse Button 5
#	KC_MS_WH_UP 	KC_WH_U 	Mouse Wheel Up
#	KC_MS_WH_DOWN 	KC_WH_D 	Mouse Wheel Down
#	KC_MS_WH_LEFT 	KC_WH_L 	Mouse Wheel Left
#	KC_MS_WH_RIGHT 	KC_WH_R 	Mouse Wheel Right
#	KC_MS_ACCEL0 	KC_ACL0 	Mouse Acceleration 0
#	KC_MS_ACCEL1 	KC_ACL1 	Mouse Acceleration 1
#	KC_MS_ACCEL2 	KC_ACL2 	Mouse Acceleration 2
#	RESET 		Put the keyboard into DFU mode for flashing
#	DEBUG 		Toggles debug mode
#	KC_GESC 	GRAVE_ESC 	Acts as escape when pressed normally but when pressed with Shift or GUI will send a ~
#	KC_LSPO 		Left shift when held, open paranthesis when tapped
#	KC_RSPC 		Right shift when held, close paranthesis when tapped
#	KC_LEAD 		The leader key
#	FUNC(n) 	F(n) 	Call fn_action(n)
#	M(n) 		to call macro n
#	MACROTAP(n) 		to macro-tap n idk FIXME`
#	MAGIC_SWAP_CONTROL_CAPSLOCK 		Swap Capslock and Left Control
#	MAGIC_CAPSLOCK_TO_CONTROL 		Treat Capslock like a Control Key
#	MAGIC_SWAP_LALT_LGUI 		Swap the left Alt and GUI keys
#	MAGIC_SWAP_RALT_RGUI 		Swap the right Alt and GUI keys
#	MAGIC_NO_GUI 		Disable the GUI key
#	MAGIC_SWAP_GRAVE_ESC 		Swap the Grave and Esc key.
#	MAGIC_SWAP_BACKSLASH_BACKSPACE 		Swap backslack and backspace
#	MAGIC_HOST_NKRO 		Force NKRO on
#	MAGIC_SWAP_ALT_GUI/AG_SWAP 		Swap Alt and Gui on both sides
#	MAGIC_UNSWAP_CONTROL_CAPSLOCK 		Disable the Control/Capslock swap
#	MAGIC_UNCAPSLOCK_TO_CONTROL 		Disable treating Capslock like Control
#	MAGIC_UNSWAP_LALT_LGUI 		Disable Left Alt and GUI switching
#	MAGIC_UNSWAP_RALT_RGUI 		Disable Right Alt and GUI switching
#	MAGIC_UNNO_GUI 		Enable the GUI key
#	MAGIC_UNSWAP_GRAVE_ESC 		Disable the Grave/Esc swap
#	MAGIC_UNSWAP_BACKSLASH_BACKSPACE 		Disable the backslash/backspace swap
#	MAGIC_UNHOST_NKRO 		Force NKRO off
#	MAGIC_UNSWAP_ALT_GUI/AG_NORM 		Disable the Alt/GUI switching
#	MAGIC_TOGGLE_NKRO 		Turn NKRO on or off
#	BL_x 		Set a specific backlight level between 0-9
#	BL_ON 		An alias for BL_9
#	BL_OFF 		An alias for BL_0
#	BL_DEC 		Turn the backlight level down by 1
#	BL_INC 		Turn the backlight level up by 1
#	BL_TOGG 		Toggle the backlight on or off
#	BL_STEP 		Step through backlight levels, wrapping around to 0 when you reach the top.
#	RGB_TOG 		toggle on/off
#	RGB_MOD 		cycle through modes
#	RGB_HUI 		hue increase
#	RGB_HUD 		hue decrease
#	RGB_SAI 		saturation increase
#	RGB_SAD 		saturation decrease
#	RGB_VAI 		value increase
#	RGB_VAD 		value decrease
#	PRINT_ON 		Start printing everything the user types
#	PRINT_OFF 		Stop printing everything the user types
#	OUT_AUTO 		auto mode
#	OUT_USB 		usb only
#	OUT_BT 		bluetooth (when BLUETOOTH_ENABLE)
#	KC_HYPR 		Hold down LCTL + LSFT + LALT + LGUI`
#	KC_MEH 		Hold down LCTL + LSFT + LALT`
#	LCTL(kc) 		LCTL + kc
#	LSFT(kc) 	S(kc) 	LSFT + kc
#	LALT(kc) 		LALT + kc
#	LGUI(kc) 		LGUI + kc
#	RCTL(kc) 		RCTL + kc
#	RSFT(kc) 		RSFT + kc
#	RALT(kc) 		RALT + kc
#	RGUI(kc) 		RGUI + kc
#	HYPR(kc) 		LCTL + LSFT + LALT + LGUI + kc
#	MEH(kc) 		LCTL + LSFT + LALT + kc
#	LCAG(kc) 		LCTL + LALT + LGUI + kc
#	ALTG(kc) 		RCTL + RALT + kc
#	SCMD(kc) 	SWIN(kc) 	LGUI + LSFT + kc
#	LCA(kc) 		LCTL + LALT + kc
#	CTL_T(kc) 	LCTL_T(kc) 	LCTL when held, kc when tapped
#	RCTL_T(kc) 		[RCTL when held, kc when tapped
#	SFT_T(kc) 	LSFT_T(kc) 	LSFT when held, kc when tapped
#	RSFT_T(kc) 		[RSFT when held, kc when tapped
#	ALT_T(kc) 	LALT_T(kc) 	LALT when held, kc when tapped
#	RALT_T(kc) 	ALGR_T(kc) 	RALT when held, kc when tapped
#	GUI_T(kc) 	LGUI_T(kc) 	LGUI when held, kc when tapped
#	RGUI_T(kc) 		RGUI when held, kc when tapped
#	C_S_T(kc) 		LCTL + LSFT when held, kc when tapped
#	MEH_T(kc) 		LCTL + LSFT + LALT when held, kc when tapped
#	LCAG_T(kc) 		LCTL + LALT + LGUI when held, kc when tapped
#	RCAG_T(kc) 		RCTL + RALT + RGUI when held, kc when tapped
#	ALL_T(kc) 		LCTL + LSFT + LALT + LGUI when held, kc when tapped more info
#	SCMD_T(kc) 	SWIN_T(kc) 	LGUI + LSFT when held, kc when tapped
#	LCA_T(kc) 		LCTL + LALT when held, kc when tapped
#	KC_TILD 	KC_TILDE 	tilde ~
#	KC_EXLM 	KC_EXCLAIM 	exclamation mark !
#	KC_AT 		at sign @
#	KC_HASH 		hash sign #
#	KC_DLR 	KC_DOLLAR 	dollar sign $
#	KC_PERC 	KC_PERCENT 	percent sign %
#	KC_CIRC 	KC_CIRCUMFLEX 	circumflex ^
#	KC_AMPR 	KC_AMPERSAND 	ampersand &
#	KC_ASTR 	KC_ASTERISK 	asterisk *
#	KC_LPRN 	KC_LEFT_PAREN 	left parenthesis (
#	KC_RPRN 	KC_RIGHT_PAREN 	right parenthesis )
#	KC_UNDS 	KC_UNDERSCORE 	underscore _
#	KC_PLUS 		plus sign +
#	KC_LCBR 	KC_LEFT_CURLY_BRACE 	left curly brace {
#	KC_RCBR 	KC_RIGHT_CURLY_BRACE 	right curly brace }
#	KC_LT/KC_LABK 	KC_LEFT_ANGLE_BRACKET 	left angle bracket <
#	KC_GT/KC_RABK 	KC_RIGHT_ANGLE_BRACKET 	right angle bracket >
#	KC_COLN 	KC_COLON 	colon :
#	KC_PIPE 		pipe `\ 	`
#	KC_QUES 	KC_QUESTION 	question mark ?
#	KC_DQT/KC_DQUO 	KC_DOUBLE_QUOTE 	double quote "
#	LT(layer, kc) 		turn on layer (0-15) when held, kc (basic keycodes) when tapped
#	TO(layer) 		turn on layer when depressed
#	MO(layer) 		momentarily turn on layer when depressed (requires KC_TRNS on destination layer)
#	DF(layer) 		sets the base (default) layer
#	TG(layer) 		toggle layer on/off
#	TT(layer) 		tap toggle? idk FIXME`
#	OSM(mod) 		hold mod for one keypress
#	OSL(layer) 		switch to layer for one keypress
#	UNICODE(n) 	UC(n) 	if UNICODE_ENABLE, this will send characters up to 0x7FFF
#	X(n) 		if UNICODEMAP_ENABLE, also sends unicode via a different method


*/

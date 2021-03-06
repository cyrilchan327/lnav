/**
 * Copyright (c) 2007-2012, Timothy Stack
 *
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * * Neither the name of Timothy Stack nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "view_curses.hh"

class test_colors : public view_curses {

public:
	test_colors() 
		: tc_window(NULL) {

	}

	void do_update(void) {
		int lpc;

		for (lpc = 0; lpc < 16; lpc++) {
            view_colors::role_t role;
			char label[64];
			attr_line_t al;
			line_range lr;

            role = view_colors::singleton().next_highlight();
			snprintf(label, sizeof(label), "This is line: %d", lpc);
			al = label;
			lr.lr_start = 0;
			lr.lr_end = 40;
			this->mvwattrline(this->tc_window,
                              lpc,
                              0,
                              al,
                              lr,
                              role);
		}
	};

	WINDOW *tc_window;
};

int main(int argc, char *argv[])
{
	int c, retval = EXIT_SUCCESS;
	bool wait_for_input = false;
	WINDOW *win;
	test_colors tc;

	win = initscr();
	noecho();

	while ((c = getopt(argc, argv, "w")) != -1) {
		switch (c) {
			case 'w':
			wait_for_input = true;
			break;
		}
	}

	view_colors::singleton().init();
	tc.tc_window = win;
	tc.do_update();
	refresh();
	if (wait_for_input) {
		getch();
	}
	endwin();

	return retval;
}

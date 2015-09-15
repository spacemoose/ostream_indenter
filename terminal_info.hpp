/// @file
///
/// Provides a wrapper to system specific tools to get terminal information.
#pragma once

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>


namespace terminal_info {

static winsize terminal_size;

int cols()
{
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminal_size);
	return terminal_size.ws_col;
}

int lines()
{
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminal_size);
	return terminal_size.ws_row;
}


}// namespace

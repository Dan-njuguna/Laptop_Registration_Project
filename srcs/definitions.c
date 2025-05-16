#include "../includes/header_files.h"

/**
 * flush_input_buff - Flushes the input buffer for the given window
 * @child: pointer to the window
 *
 * Return: Nothing
 */
void flush_input_buff(WINDOW *child)
{
	char ch;

	while ((ch = wgetch(child)) != '\n' && ch != EOF)
		;
}

/**
 * add_terminator - Adds a null terminator to the string if needed and
 * flushes input buffer if necessary
 * @string: pointer to the string character
 * @size: size of the string
 * @length: length of the string
 * @child: pointer to the window
 *
 * Return: Nothing
 */
void add_terminator(char *string, int size, int length, WINDOW *child)
{
	/* TODO: check for instance of newline and replace it with null */
	if (strchr(string, '\n'))
	{
		string[strcspn(string, "\n")] = '\0';
		return;
	}

	/* Check if the string is too long */
	if (size - 1 == length)
	{
		string[length] = '\0';
		flush_input_buff(child);
	}
}

/**
 * clear_console - Clears the console after a delay
 * @time: the time to be waited before clearing the console
 * @child: pointer to the window
 *
 * Return: Nothing
 */
void clear_console(int time, WINDOW *child)
{
	int i;
	const int MOVE_UP = 2;

	sleep(time);

	/* TODO: Removes the error message and the typed */
	/*	characters from the console */
	for (i = 0; i < MOVE_UP; ++i)
	{
		wprintw(child, "\033[A\033[2K");
		wrefresh(child);
		mvwdelch(child, -2, 1);
	}
}

/**
 * isEmpty - Checks if the input is empty and prints a message if so
 * @newline: the character to check
 * @member: the name of the member to check
 * @child: pointer to the window
 *
 * Return: 1 if empty, 0 otherwise
 */
int isEmpty(char newline, char *member, WINDOW *child)
{
	if (newline == '\n')
	{
		wprintw(child, "\t\t%s should not be empty\n", member);
		wrefresh(child);
		clear_console(1, child);
		return (1);
	}
	return (0);
}

/**
 * init_current_date - Initializes the current date in the entry structure
 * @entry: pointer to the entry structure
 * @child: pointer to the window
 *
 * Return: Nothing
 */
void init_current_date(Entry *entry, WINDOW *child)
{
	time_t now;
	struct tm *current_d;

	/* Buffer to hold the formatted date string (dd-mm-yyyy + null terminator) */
	char date_str[DATE_LEN];

	time(&now);
	current_d = localtime(&now);

	if (current_d != NULL)
	{
		if (!(strftime(date_str, sizeof(date_str),
						"%d-%m-%Y", current_d)))
		{
			wprintw(child, "\t\tError formatting the current date.\n");
			wrefresh(child);
			strcpy(entry->t_stamp.t_registration, "NULL");
		}
		else
		{
			strcpy(entry->t_stamp.t_registration, date_str);
		}
	}
	else
	{
		wprintw(child, "\t\tError retrieving the current date.\n");
		wrefresh(child);
	}
}

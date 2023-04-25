#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - A custom implementation of printf
 * @format: The format string
 *
 * Return: The number of characters printed
 */
int _printf(const char *format, ...)
{
	int i, printed_chars = 0, flags, width, precision, size, buff_ind = 0, printed = 0;
	char buffer[BUFF_SIZE];
	va_list args;

	if (format == NULL)
		return (-1);

	va_start(args, format);

	for (i = 0; format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];

			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);

			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);

			flags = get_flags(format, &i);
			width = get_width(format, &i, args);
			precision = get_precision(format, &i, args);
			size = get_size(format, &i);
			i++;

			printed = handle_print(format, &i, args, buffer, flags, width, precision, size);

			if (printed == -1)
				return (-1);

			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(args);

	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it is not empty
 * @buffer: The buffer to print from
 * @buff_ind: The index of the buffer
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
	{
		write(1, &buffer[0], *buff_ind);
	}

	*buff_ind = 0;
}


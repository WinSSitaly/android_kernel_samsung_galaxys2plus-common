#ifndef _PERF_UI_UTIL_H_
#define _PERF_UI_UTIL_H_ 1

<<<<<<< HEAD
#include <stdarg.h>

int ui__getch(int delay_secs);
int ui__popup_menu(int argc, char * const argv[]);
int ui__help_window(const char *text);
int ui__dialog_yesno(const char *msg);
int ui__question_window(const char *title, const char *text,
			const char *exit_msg, int delay_secs);
int __ui__warning(const char *title, const char *format, va_list args);
=======
#include <stdbool.h>

int ui__popup_menu(int argc, char * const argv[]);
int ui__help_window(const char *text);
bool ui__dialog_yesno(const char *msg);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

#endif /* _PERF_UI_UTIL_H_ */

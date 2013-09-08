#ifndef _PERF_UI_HELPLINE_H_
#define _PERF_UI_HELPLINE_H_ 1

<<<<<<< HEAD
#include <stdio.h>
#include <stdarg.h>

=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
void ui_helpline__init(void);
void ui_helpline__pop(void);
void ui_helpline__push(const char *msg);
void ui_helpline__vpush(const char *fmt, va_list ap);
void ui_helpline__fpush(const char *fmt, ...);
void ui_helpline__puts(const char *msg);

<<<<<<< HEAD
extern char ui_helpline__current[];

=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#endif /* _PERF_UI_HELPLINE_H_ */

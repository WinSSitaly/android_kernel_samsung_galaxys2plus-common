#define ARRAY_AND_SIZE(x)	(x), ARRAY_SIZE(x)

struct sys_timer;

extern void timer_init(int irq);

extern void __init icu_init_irq(void);
extern void __init mmp_map_io(void);
<<<<<<< HEAD
extern void mmp_restart(char, const char *);
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

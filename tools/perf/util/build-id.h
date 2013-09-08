#ifndef PERF_BUILD_ID_H_
#define PERF_BUILD_ID_H_ 1

#include "session.h"

<<<<<<< HEAD
extern struct perf_tool build_id__mark_dso_hit_ops;
=======
extern struct perf_event_ops build_id__mark_dso_hit_ops;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

char *dso__build_id_filename(struct dso *self, char *bf, size_t size);

#endif

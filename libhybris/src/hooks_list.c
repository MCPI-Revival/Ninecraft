#include "hooks_list.h"
#include <hybris/hook.h>

extern struct _hook main_hooks[];
extern struct _hook dirent_hooks[];
extern struct _hook io_hooks[];
extern struct _hook net_hooks[];
extern struct _hook pthread_hooks[];
#ifdef __APPLE__
extern struct _hook net_darwin_hooks[];
#endif

void hybris_register_default_hooks() {
    hybris_register_hooks(main_hooks);
    hybris_register_hooks(dirent_hooks);
    hybris_register_hooks(io_hooks);
    hybris_register_hooks(net_hooks);
    hybris_register_hooks(pthread_hooks);

#ifdef __APPLE__
    hybris_register_hooks(net_darwin_hooks);
#endif
}
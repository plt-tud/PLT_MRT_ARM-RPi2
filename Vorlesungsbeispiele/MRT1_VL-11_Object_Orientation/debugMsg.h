#ifndef HAVE_DEBUGMSG_H
#define HAVE_DEBUGMSG_H

#define DEBUG_ENABLE

#ifdef DEBUG_ENABLE
    #include <stdio.h>
    #define DEBUG(_p_msg) { printf("%s\n", _p_msg); }
#else
    #define DEBUG(_p_msg) {}
#endif

#endif /* HAVE_DEBUGMSG_H */

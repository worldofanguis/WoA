/*
 * ___            ___       __
 * \  \          /  /      /  \
 *  \  \        /  /      /    \
 *   \  \  /\  /  /___   /  /\  \
 *    \  \/  \/  /|   | /  ____  \
 *     \___/\___/ |___|/__/    \__\
 *                    World Of Anguis
 *
 *	Common header files
 */
 

#if COMPILER == COMPILER_MICROSOFT
#   pragma warning(disable:4996)                            // 'function': was declared deprecated
#ifndef __SHOW_STUPID_WARNINGS__
#   pragma warning(disable:4005)                            // 'identifier' : macro redefinition
#   pragma warning(disable:4018)                            // 'expression' : signed/unsigned mismatch
#   pragma warning(disable:4244)                            // 'argument' : conversion from 'type1' to 'type2', possible loss of data
#   pragma warning(disable:4267)                            // 'var' : conversion from 'size_t' to 'type', possible loss of data
#   pragma warning(disable:4305)                            // 'identifier' : truncation from 'type1' to 'type2'
#   pragma warning(disable:4311)                            // 'variable' : pointer truncation from 'type' to 'type'
#   pragma warning(disable:4355)                            // 'this' : used in base member initializer list
#   pragma warning(disable:4800)                            // 'type' : forcing value to bool 'true' or 'false' (performance warning)
#endif                                                      // __SHOW_STUPID_WARNINGS__
#endif
 
#include <windows.h>
#include <queue>
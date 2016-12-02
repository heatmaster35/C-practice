/*
##########################
# Name: Leo Gomez        #
# CruzID: legomez        #
# Class: CMPS-12M        #
# Date: Nov 7, 2014      #
# filename: minunit.h    #
# Details: code for unit #
#   testing in queue.c   #
##########################
*/
/* file: minunit.h */
/* C unit testing in 7 lines of preprocessor code. */
#define STR(x) #x
#define STRINGIFY(x) STR(x)
#define FILE_LINE __FILE__ ":" STRINGIFY(__LINE__) " --- "
#define mu_assert(message, test) do { if (!(test)) return FILE_LINE message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                               if (message) return message; } while (0)
extern int tests_run;

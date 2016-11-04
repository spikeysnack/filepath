/* options.h */
#include <unistd.h>

extern char* delim;

inline int options( int argc, char** argv);
void usage(FILE* f);
void version(FILE* f);



/* check options  (unistd.h)*/
inline int options( int argc, char** argv)
{
  int flags = 0;
  int opt = 0; 

  while ((opt = getopt(argc, argv, "cdD:hwWv")) != -1) {
    switch (opt) 
      {

      case 'c':
	flags += CONT;
	break;
      
      case 'd':
	delim = NEWLINE;
	break;

      case 'D':
	delim = optarg;	
	break;

      case 'h':
	usage(stdout); 
	exit(0); 
	break;

      case 'w':
	flags += WARN;
	break;

      case 'W':
	flags += WARNALL;
	break;

      case 'v':
	version(stdout);
	exit(0);
	break;

      default: /* '?' */
	break;
      }
  }

  errno = 0;
  return flags;  
}/* options */
 

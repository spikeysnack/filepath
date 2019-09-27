/* filepath.c */


/* AUTHOR:  Chris Reid <spikeysnack@gmail.com> */
/* LICENSE: Free for all purposes              */
/* COPYRIGHT: 2016- Chris Reid                 */


/* get the full path of a file  */

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <error.h>
#include <locale.h>


/* version information */
const char* filepath_version       = "1.3";
const char* filepath_revision_date = "04 Nov 2016";
const char* filepath_author        = "Chris Reid <spikeysnack@gmail.com>";
const char* filepath_license       = "@2016 freeware, unrestricted, no warranty";
const char* thisfile;
char *delim;  

/* Linux vs BSD  */

#ifdef MAXPATHLEN
#define MAX_PATH_LEN  MAXPATHLEN
#endif

#ifndef MAX_PATH_LEN
#ifdef PATH_MAX
#define MAX_PATH_LEN PATH_MAX   /* max bytes in pathname */
#else
#define MAX_PATH_LEN 4096
#endif
#endif

/* linux, BSD, Apple  */ 
#define NEWLINE "\n"    

/*  mac  < OS9   */
/* #define NEWLINE "\r"        */

/* windows */
/* #define NEWLINE "\r\n"  */


/* option masks */
#define QUIET   0x00
#define WARN    0x01
#define WARNALL 0x02
#define CONT    0x04


#include "options.h"

/* function prototypes */
int main( int argc, char** argv , char** env );

inline int options( int argc, char** argv);
static inline int checkerr(const int err, int flags );

void usage(FILE* f);
void version(FILE* f);


/* print version info */
void version(FILE* f)
{
  fprintf(f , "%s:\tversion\t%s\t%s\n", thisfile, filepath_version, filepath_revision_date );
  fprintf(f , "author:  \t%s\n",  filepath_author );
  fprintf(f , "license: \t%s\n", filepath_license );
}


/* simple usage message */
void usage(FILE* f)
{
  fprintf(f , "usage:\n" );
  
  fprintf( f , "\t\t%s <file(s)>\n", thisfile );

  fprintf( f , "\t\t%s -c           \t continue through errors (default:no) \n", thisfile );

  fprintf( f , "\t\t%s -d           \t delimit output with \\n  (default:space)\n", thisfile );

  fprintf( f , "\t\t%s -D<string>   \t delimit output with string or char \n", thisfile );

  fprintf( f , "\t\t%s -h           \t show this message\n", thisfile );

  fprintf( f , "\t\t%s -w <filename>\t return numeric error code \n", thisfile );

  fprintf( f , "\t\t%s -W <filename>\t return textual error \n" , thisfile );
}



/* main driver */
int main( int argc, char** argv , char** env )
{
  
  char actualpath [MAX_PATH_LEN+1] = {0};
  char *symlinkpath = NULL;
  char *ptr         = NULL; 
  char *argv_0      = NULL; /* thisfile */
  int cont = 0;
  int warn = 0;
  int warnall = 0;
  int flags = 0;
  int patherr = 0;
  int err = 0;
  int i = 0;
  
  delim = " "; /* default: space */

  /* skip all the '/' in argv[0] */
  thisfile = ( argv_0 = strchr(argv[0], '/') ) ? (argv_0 + 1) : argv[0];

  setlocale(LC_ALL, "");

  errno = 0;

  if ( argc < 2 ) 
    {
      usage(stderr);
      exit(0);
    }


  flags = options(argc, argv);  /* get flags */
  errno = 0;

  /* set options */
  cont =    ( flags & CONT );
  warn =    ( flags & WARN );
  warnall = ( flags & WARNALL );

  errno = 0;

  /* loop through args */
  for (i=optind; i< argc; i++) 
    {
      symlinkpath = argv[i];

      ptr = realpath(symlinkpath, actualpath);
      patherr = errno; errno = 0;

      if ( ptr ) fprintf(stdout, "%s%s", ptr, delim);
      err = errno; errno = 0;

      ptr = NULL; /* don't free ptr, it points to actualpath */
      
      if ( checkerr( patherr, flags ) )
	{
	  if ( warn )   
	    fprintf( stdout, "%d %s", patherr, delim );
	  
	  if ( warnall ) 
	    fprintf( stdout, "%s %s", strerror( patherr ), delim );

	  if ( cont ) continue;
	  else goto done;

	  if ( err ) goto err;
	    
	} /* if checkerr*/

    }/* for i */

  return 0;
  
 err:
  fprintf( stderr , "%s \n", strerror(err) );
  
 done:
  return err; 
} /* main */



/* mask errors to be ignored */
inline int checkerr(const int err, int flags)
{ 
  flags = flags % CONT; /* mask CONT */

  if ( (err) && (flags) )
    {
      /* return all errors */
      if ( flags == WARNALL) return 1;
  
      /* return errors but not file not found or null path*/
      if ( flags == WARN )
	if ( (err != EINVAL) && (err != ENOENT )) return 1; 
    }      

  return 0;
   
}/* checkerr */







/**
   ERRORS
   EACCES Read or search permission was denied for a component of the path prefix.

   EINVAL path is NULL.  (In glibc versions before 2.3, this error is also returned if resolved_path is NULL.)

   EIO    An I/O error occurred while reading from the filesystem.

   ELOOP  Too many symbolic links were encountered in translating the pathname.

   ENAMETOOLONG
   A component of a pathname exceeded NAME_MAX characters, or an entire pathname exceeded PATH_MAX characters.

   ENOENT The named file does not exist.

   ENOTDIR
   A component of the path prefix is not a directory.
**/


/*END*/


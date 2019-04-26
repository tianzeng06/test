#ifndef __errors_h  
#define __errors_h  
  
#include <unistd.h>  
#include <errno.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
  
#ifdef DEBUG  
#define DPRINTF(arg) printf arg  
#eles  
#define DPRINTF(arg)  
#endif  
// 用do_while语句结束，把{}里的当作语句块  
#define err_abort(code, text) do {\
  fprintf( stderr, "%s at \"%s\":%d: %s\n",\
       text, __FILE__, __LINE__, strerror(code));\
  abort(); \
  } while (0)  
  
#define errno_abort(text) do{ \
  fprintf( stderr, "%s at \"%s\":%d: %s\n",       \
       text, __FILE__, __LINE__, strerror(errno)); \
  abort(); \
  } while (0)  
  
#endif 

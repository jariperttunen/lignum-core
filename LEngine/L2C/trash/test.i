# 1 "test.cpp"
# 1 "/usr/include/assert.h" 1 3
 

















 



# 32 "/usr/include/assert.h" 3



# 1 "/usr/include/features.h" 1 3
 




















 


























































 



















 





 



 







 
# 137 "/usr/include/features.h" 3


 









 





 



























# 195 "/usr/include/features.h" 3


































 



 








 




 

# 1 "/usr/include/sys/cdefs.h" 1 3
 




















 




 





 








 




# 71 "/usr/include/sys/cdefs.h" 3


 







 



# 103 "/usr/include/sys/cdefs.h" 3



 








 















 








 








 









 







# 249 "/usr/include/features.h" 2 3


 








 





 

 








# 1 "/usr/include/gnu/stubs.h" 1 3
 




































# 277 "/usr/include/features.h" 2 3




# 35 "/usr/include/assert.h" 2 3


 




# 56 "/usr/include/assert.h" 3


extern "C" { 

 
extern void __assert_fail  (__const char *__assertion,
				__const char *__file,
				unsigned int __line,
				__const char *__function)  throw ()  
     __attribute__ ((__noreturn__));

 
extern void __assert_perror_fail  (int __errnum,
				       __const char *__file,
				       unsigned int __line,
				       __const char *__function)  throw ()  
     __attribute__ ((__noreturn__));

} 













 











# 1 "test.cpp" 2

# 1 "/usr/include/stdio.h" 1 3
 

















 









extern "C" { 



# 1 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h" 1 3






 


# 19 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h" 3



 


 





 


# 61 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h" 3


 





 


















 





 

 

# 131 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h" 3


 

 


































typedef unsigned int size_t;






















 




 

# 271 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h" 3


# 283 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h" 3


 

 

# 317 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h" 3




 





















# 33 "/usr/include/stdio.h" 2 3





# 1 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stdarg.h" 1 3
 





























































 






typedef void *__gnuc_va_list;



 

# 116 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stdarg.h" 3



















# 202 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stdarg.h" 3




# 38 "/usr/include/stdio.h" 2 3


# 1 "/usr/include/bits/types.h" 1 3
 

















 









# 1 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h" 1 3






 


# 19 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h" 3



 


 





 


# 61 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h" 3


 





 


















 





 

 

# 131 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h" 3


 

 


# 188 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h" 3





 




 

# 271 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h" 3


# 283 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h" 3


 

 

# 317 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h" 3




 





















# 29 "/usr/include/bits/types.h" 2 3


 
typedef unsigned char __u_char;
typedef unsigned short __u_short;
typedef unsigned int __u_int;
typedef unsigned long __u_long;

__extension__ typedef unsigned long long int __u_quad_t;
__extension__ typedef long long int __quad_t;
# 48 "/usr/include/bits/types.h" 3

typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

__extension__ typedef signed long long int __int64_t;
__extension__ typedef unsigned long long int __uint64_t;

typedef __quad_t *__qaddr_t;

typedef __u_quad_t __dev_t;		 
typedef __u_int __uid_t;		 
typedef __u_int __gid_t;		 
typedef __u_long __ino_t;		 
typedef __u_int __mode_t;		 
typedef __u_int __nlink_t; 		 
typedef long int __off_t;		 
typedef __quad_t __loff_t;		 
typedef int __pid_t;			 
typedef int __ssize_t;			 
typedef long int __rlim_t;		 
typedef __quad_t __rlim64_t;		 
typedef __u_int __id_t;			 

typedef struct
  {
    int __val[2];
  } __fsid_t;				 

 
typedef int __daddr_t;			 
typedef char *__caddr_t;
typedef long int __time_t;
typedef long int __swblk_t;		 

typedef long int __clock_t;

 
typedef unsigned long int __fd_mask;

 


 




 
typedef struct
  {
     





    __fd_mask __fds_bits[1024  / (8 * sizeof (__fd_mask)) ];


  } __fd_set;


typedef int __key_t;

 
typedef unsigned short int __ipc_pid_t;


 

 
typedef __u_long __blkcnt_t;
typedef __u_quad_t __blkcnt64_t;

 
typedef long int __fsblkcnt_t;
typedef __quad_t __fsblkcnt64_t;

 
typedef __u_long __fsfilcnt_t;
typedef __u_quad_t __fsfilcnt64_t;

 
typedef __u_long __ino64_t;

 
typedef __loff_t __off64_t;

 
typedef int __t_scalar_t;
typedef unsigned int __t_uscalar_t;

 
typedef int __intptr_t;


 





# 40 "/usr/include/stdio.h" 2 3







 
typedef struct _IO_FILE FILE;








# 1 "/usr/include/libio.h" 1 3
 




























# 1 "/usr/include/_G_config.h" 1 3
 





 






# 1 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h" 1 3






 


# 19 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h" 3



 


 





 


# 61 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h" 3


 





 


















 





 

 

# 131 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h" 3


 

 


# 188 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h" 3





 




 





























 



















































typedef unsigned int  wint_t;




 

 

# 317 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h" 3




 





















# 14 "/usr/include/_G_config.h" 2 3





















typedef int _G_int16_t __attribute__ ((__mode__ (__HI__)));
typedef int _G_int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int _G_uint16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int _G_uint32_t __attribute__ ((__mode__ (__SI__)));




 


















 




 














# 30 "/usr/include/libio.h" 2 3
















 

# 1 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stdarg.h" 1 3
 





























































 










 

# 116 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stdarg.h" 3



















# 202 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stdarg.h" 3




# 48 "/usr/include/libio.h" 2 3







# 67 "/usr/include/libio.h" 3


 

















# 98 "/usr/include/libio.h" 3











 
























 



















struct _IO_jump_t;  struct _IO_FILE;

 







typedef void _IO_lock_t;



 

struct _IO_marker {
  struct _IO_marker *_next;
  struct _IO_FILE *_sbuf;
   

   
  int _pos;
# 186 "/usr/include/libio.h" 3

};

struct _IO_FILE {
  int _flags;		 


   
   
  char* _IO_read_ptr;	 
  char* _IO_read_end;	 
  char* _IO_read_base;	 
  char* _IO_write_base;	 
  char* _IO_write_ptr;	 
  char* _IO_write_end;	 
  char* _IO_buf_base;	 
  char* _IO_buf_end;	 
   
  char *_IO_save_base;  
  char *_IO_backup_base;   
  char *_IO_save_end;  

  struct _IO_marker *_markers;

  struct _IO_FILE *_chain;

  int _fileno;
  int _blksize;
  __off_t   _old_offset;  


   
  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];

   

  _IO_lock_t *_lock;








  __off64_t   _offset;
   
  int _unused2[16];

};





struct _IO_FILE_plus;
extern struct _IO_FILE_plus _IO_2_1_stdin_;
extern struct _IO_FILE_plus _IO_2_1_stdout_;
extern struct _IO_FILE_plus _IO_2_1_stderr_;











# 276 "/usr/include/libio.h" 3




extern "C" {


extern int __underflow  (_IO_FILE *)  throw ()  ;
extern int __uflow  (_IO_FILE *)  throw ()  ;
extern int __overflow  (_IO_FILE *, int)  throw ()  ;
















extern int _IO_getc  (_IO_FILE *__fp)  throw ()  ;
extern int _IO_putc  (int __c, _IO_FILE *__fp)  throw ()  ;
extern int _IO_feof  (_IO_FILE *__fp)  throw ()  ;
extern int _IO_ferror  (_IO_FILE *__fp)  throw ()  ;

extern int _IO_peekc_locked  (_IO_FILE *__fp)  throw ()  ;

 



extern void _IO_flockfile  (_IO_FILE *)  throw ()  ;
extern void _IO_funlockfile  (_IO_FILE *)  throw ()  ;
extern int _IO_ftrylockfile  (_IO_FILE *)  throw ()  ;












extern int _IO_vfscanf  (_IO_FILE *  , const char *  ,
			     __gnuc_va_list , int *  )  throw ()  ;
extern int _IO_vfprintf  (_IO_FILE *  , const char *  ,
			      __gnuc_va_list )  throw ()  ;
extern __ssize_t   _IO_padn  (_IO_FILE *, int, __ssize_t  )  throw ()  ;
extern size_t   _IO_sgetn  (_IO_FILE *, void *, size_t  )  throw ()  ;

extern __off64_t   _IO_seekoff  (_IO_FILE *, __off64_t  , int, int)  throw ()  ;
extern __off64_t   _IO_seekpos  (_IO_FILE *, __off64_t  , int)  throw ()  ;

extern void _IO_free_backup_area  (_IO_FILE *)  throw ()  ;


}



# 57 "/usr/include/stdio.h" 2 3


 

typedef __off_t  fpos_t;







 





 





 






 







 




 








# 1 "/usr/include/bits/stdio_lim.h" 1 3
 




































# 110 "/usr/include/stdio.h" 2 3



 
extern FILE *stdin;		 
extern FILE *stdout;		 
extern FILE *stderr;		 


 
extern int remove  (__const char *__filename)  throw ()  ;
 
extern int rename  (__const char *__old, __const char *__new)  throw ()  ;


 

extern FILE *tmpfile  (void)  throw ()  ;










 
extern char *tmpnam  (char *__s)  throw ()  ;


 

extern char *tmpnam_r  (char *__s)  throw ()  ;




 






extern char *tempnam  (__const char *__dir, __const char *__pfx)  throw ()  ;



 
extern int fclose  (FILE *__stream)  throw ()  ;
 
extern int fflush  (FILE *__stream)  throw ()  ;


 
extern int fflush_unlocked  (FILE *__stream)  throw ()  ;









 
extern FILE *fopen  (__const char *   __filename,
			 __const char *   __modes)  throw ()  ;
 
extern FILE *freopen  (__const char *   __filename,
			   __const char *   __modes,
			   FILE *   __stream)  throw ()  ;
# 197 "/usr/include/stdio.h" 3










 
extern FILE *fdopen  (int __fd, __const char *__modes)  throw ()  ;


# 223 "/usr/include/stdio.h" 3



 

extern void setbuf  (FILE *   __stream, char *   __buf)  throw ()  ;
 


extern int setvbuf  (FILE *   __stream, char *   __buf,
			 int __modes, size_t __n)  throw ()  ;


 

extern void setbuffer  (FILE *   __stream, char *   __buf,
			    size_t __size)  throw ()  ;

 
extern void setlinebuf  (FILE *__stream)  throw ()  ;



 
extern int fprintf  (FILE *   __stream,
			 __const char *   __format, ...)  throw ()  ;
 
extern int printf  (__const char *   __format, ...)  throw ()  ;
 
extern int sprintf  (char *   __s,
			 __const char *   __format, ...)  throw ()  ;

 
extern int vfprintf  (FILE *   __s,
			  __const char *   __format,
			  __gnuc_va_list  __arg)  throw ()  ;
 
extern int vprintf  (__const char *   __format,
			 __gnuc_va_list  __arg)  throw ()  ;
 
extern int vsprintf  (char *   __s,
			  __const char *   __format,
			  __gnuc_va_list  __arg)  throw ()  ;


 
extern int snprintf  (char *   __s, size_t __maxlen,
			  __const char *   __format, ...)  throw ()  
     __attribute__ ((__format__ (__printf__, 3, 4)));

extern int __vsnprintf  (char *   __s, size_t __maxlen,
			     __const char *   __format,
			     __gnuc_va_list  __arg)  throw ()  
     __attribute__ ((__format__ (__printf__, 3, 0)));
extern int vsnprintf  (char *   __s, size_t __maxlen,
			   __const char *   __format,
			   __gnuc_va_list  __arg)  throw ()  
     __attribute__ ((__format__ (__printf__, 3, 0)));


# 302 "/usr/include/stdio.h" 3



 
extern int fscanf  (FILE *   __stream,
			__const char *   __format, ...)  throw ()  ;
 
extern int scanf  (__const char *   __format, ...)  throw ()  ;
 
extern int sscanf  (__const char *   __s,
			__const char *   __format, ...)  throw ()  ;

# 330 "/usr/include/stdio.h" 3



 
extern int fgetc  (FILE *__stream)  throw ()  ;
extern int getc  (FILE *__stream)  throw ()  ;

 
extern int getchar  (void)  throw ()  ;

 




 
extern int getc_unlocked  (FILE *__stream)  throw ()  ;
extern int getchar_unlocked  (void)  throw ()  ;



 
extern int fgetc_unlocked  (FILE *__stream)  throw ()  ;



 
extern int fputc  (int __c, FILE *__stream)  throw ()  ;
extern int putc  (int __c, FILE *__stream)  throw ()  ;

 
extern int putchar  (int __c)  throw ()  ;

 




 
extern int fputc_unlocked  (int __c, FILE *__stream)  throw ()  ;



 
extern int putc_unlocked  (int __c, FILE *__stream)  throw ()  ;
extern int putchar_unlocked  (int __c)  throw ()  ;




 
extern int getw  (FILE *__stream)  throw ()  ;

 
extern int putw  (int __w, FILE *__stream)  throw ()  ;



 
extern char *fgets  (char *   __s, int __n,
			 FILE *   __stream)  throw ()  ;







 

extern char *gets  (char *__s)  throw ()  ;


# 420 "/usr/include/stdio.h" 3



 
extern int fputs  (__const char *   __s,
		       FILE *   __stream)  throw ()  ;







 
extern int puts  (__const char *__s)  throw ()  ;


 
extern int ungetc  (int __c, FILE *__stream)  throw ()  ;


 
extern size_t fread  (void *   __ptr, size_t __size,
			  size_t __n, FILE *   __stream)  throw ()  ;
 
extern size_t fwrite  (__const void *   __ptr, size_t __size,
			   size_t __n, FILE *   __s)  throw ()  ;


 
extern size_t fread_unlocked  (void *   __ptr, size_t __size,
				   size_t __n, FILE *   __stream)  throw ()  ;
extern size_t fwrite_unlocked  (__const void *   __ptr,
				    size_t __size, size_t __n,
				    FILE *   __stream)  throw ()  ;



 
extern int fseek  (FILE *__stream, long int __off, int __whence)  throw ()  ;
 
extern long int ftell  (FILE *__stream)  throw ()  ;
 
extern void rewind  (FILE *__stream)  throw ()  ;

 




 


typedef __off_t off_t;




















 
extern int fgetpos  (FILE *   __stream,
			 fpos_t *   __pos)  throw ()  ;
 
extern int fsetpos  (FILE *__stream, __const fpos_t *__pos)  throw ()  ;
# 519 "/usr/include/stdio.h" 3


# 529 "/usr/include/stdio.h" 3


 
extern void clearerr  (FILE *__stream)  throw ()  ;
 
extern int feof  (FILE *__stream)  throw ()  ;
 
extern int ferror  (FILE *__stream)  throw ()  ;


 
extern void clearerr_unlocked  (FILE *__stream)  throw ()  ;
extern int feof_unlocked  (FILE *__stream)  throw ()  ;
extern int ferror_unlocked  (FILE *__stream)  throw ()  ;



 
extern void perror  (__const char *__s)  throw ()  ;

 


extern int sys_nerr;
extern __const char *__const sys_errlist[];








 
extern int fileno  (FILE *__stream)  throw ()  ;



 
extern int fileno_unlocked  (FILE *__stream)  throw ()  ;





 
extern FILE *popen  (__const char *__command, __const char *__modes)  throw ()  ;

 
extern int pclose  (FILE *__stream)  throw ()  ;




 
extern char *ctermid  (char *__s)  throw ()  ;









# 603 "/usr/include/stdio.h" 3




 

 
extern void flockfile  (FILE *__stream)  throw ()  ;

 

extern int ftrylockfile  (FILE *__stream)  throw ()  ;

 
extern void funlockfile  (FILE *__stream)  throw ()  ;










 





} 




# 2 "test.cpp" 2

# 1 "/usr/include/math.h" 1 3
 


















 








extern "C" { 

 

# 1 "/usr/include/bits/huge_val.h" 1 3
 

























 













 

# 68 "/usr/include/bits/huge_val.h" 3

# 33 "/usr/include/math.h" 2 3


 



 
# 1 "/usr/include/bits/mathdef.h" 1 3
 





















# 45 "/usr/include/bits/mathdef.h" 3

# 40 "/usr/include/math.h" 2 3



 



















# 1 "/usr/include/bits/mathcalls.h" 1 3
 


















 






























 

 
extern   double          acos          (double  __x)    ; extern   double         __acos          (double  __x)      ;
 
extern   double          asin          (double  __x)    ; extern   double         __asin          (double  __x)      ;
 
extern   double          atan          (double  __x)    ; extern   double         __atan          (double  __x)      ;
 
extern   double          atan2          (double  __y, double  __x)    ; extern   double         __atan2          (double  __y, double  __x)      ;

 
extern   double          cos          (double  __x)    ; extern   double         __cos          (double  __x)      ;
 
extern   double          sin          (double  __x)    ; extern   double         __sin          (double  __x)      ;
 
extern   double          tan          (double  __x)    ; extern   double         __tan          (double  __x)      ;







 

 
extern   double          cosh          (double  __x)    ; extern   double         __cosh          (double  __x)      ;
 
extern   double          sinh          (double  __x)    ; extern   double         __sinh          (double  __x)      ;
 
extern   double          tanh          (double  __x)    ; extern   double         __tanh          (double  __x)      ;


 
extern   double          acosh          (double  __x)    ; extern   double         __acosh          (double  __x)      ;
 
extern   double          asinh          (double  __x)    ; extern   double         __asinh          (double  __x)      ;
 
extern   double          atanh          (double  __x)    ; extern   double         __atanh          (double  __x)      ;


 

 
extern   double          exp          (double  __x)    ; extern   double         __exp          (double  __x)      ;








 
extern   double          frexp          (double  __x, int *__exponent)    ; extern   double         __frexp          (double  __x, int *__exponent)      ;

 
extern   double          ldexp          (double  __x, int __exponent)    ; extern   double         __ldexp          (double  __x, int __exponent)      ;

 
extern   double          log          (double  __x)    ; extern   double         __log          (double  __x)      ;

 
extern   double          log10          (double  __x)    ; extern   double         __log10          (double  __x)      ;

 
extern   double          modf          (double  __x, double  *__iptr)    ; extern   double         __modf          (double  __x, double  *__iptr)      ;


 
extern   double          expm1          (double  __x)    ; extern   double         __expm1          (double  __x)      ;

 
extern   double          log1p          (double  __x)    ; extern   double         __log1p          (double  __x)      ;

 
extern   double          logb          (double  __x)    ; extern   double         __logb          (double  __x)      ;











 

 
extern   double          pow          (double  __x, double  __y)    ; extern   double         __pow          (double  __x, double  __y)      ;

 
extern   double          sqrt          (double  __x)    ; extern   double         __sqrt          (double  __x)      ;


 
extern   double          hypot          (double  __x, double  __y)    ; extern   double         __hypot          (double  __x, double  __y)      ;



 
extern   double          cbrt          (double  __x)    ; extern   double         __cbrt          (double  __x)      ;



 

 
extern   double          ceil          (double  __x)    ; extern   double         __ceil          (double  __x)      ;

 
extern   double          fabs          (double  __x)     __attribute__ (    (__const__)  ); extern   double         __fabs          (double  __x)     __attribute__ (    (__const__)  )  ;

 
extern   double          floor          (double  __x)    ; extern   double         __floor          (double  __x)      ;

 
extern   double          fmod          (double  __x, double  __y)    ; extern   double         __fmod          (double  __x, double  __y)      ;


 

extern  int     __isinf      (double  __value)   __attribute__ ((__const__));


 

extern  int     isinf      (double  __value)   __attribute__ ((__const__));

 
extern   int        finite        (double  __value)    __attribute__ (  (__const__) ); extern   int        __finite        (double  __value)    __attribute__ (  (__const__) ) ;

 





extern   double          infnan          (int __error)     __attribute__ (    (__const__)  ); extern   double         __infnan          (int __error)     __attribute__ (    (__const__)  )  ;

 
extern   double          drem          (double  __x, double  __y)    ; extern   double         __drem          (double  __x, double  __y)      ;


 
extern   double          significand          (double  __x)    ; extern   double         __significand          (double  __x)      ;



 
extern   double          copysign          (double  __x, double  __y)     __attribute__ (    (__const__)  ); extern   double         __copysign          (double  __x, double  __y)     __attribute__ (    (__const__)  )  ;









 
extern   int        isnan        (double  __value)    __attribute__ (  (__const__) ); extern   int        __isnan        (double  __value)    __attribute__ (  (__const__) ) ;

 
extern   double          j0          (double )    ; extern   double         __j0          (double )      ;
extern   double          j1          (double )    ; extern   double         __j1          (double )      ;
extern   double          jn          (int, double )    ; extern   double         __jn          (int, double )      ;
extern   double          y0          (double )    ; extern   double         __y0          (double )      ;
extern   double          y1          (double )    ; extern   double         __y1          (double )      ;
extern   double          yn          (int, double )    ; extern   double         __yn          (int, double )      ;




 
extern   double          erf          (double )    ; extern   double         __erf          (double )      ;
extern   double          erfc          (double )    ; extern   double         __erfc          (double )      ;
extern   double          lgamma          (double )    ; extern   double         __lgamma          (double )      ;
extern   double          tgamma          (double )    ; extern   double         __tgamma          (double )      ;



 
extern   double          gamma          (double )    ; extern   double         __gamma          (double )      ;



 


extern   double          lgamma_r              (double , int *__signgamp)    ; extern   double         __lgamma_r              (double , int *__signgamp)      ;




 

extern   double          rint          (double  __x)    ; extern   double         __rint          (double  __x)      ;

 
extern   double          nextafter          (double  __x, double  __y)     __attribute__ (    (__const__)  ); extern   double         __nextafter          (double  __x, double  __y)     __attribute__ (    (__const__)  )  ;




 
extern   double          remainder          (double  __x, double  __y)    ; extern   double         __remainder          (double  __x, double  __y)      ;


 
extern   double          scalb          (double  __x, double  __n)    ; extern   double         __scalb          (double  __x, double  __n)      ;


 
extern   double          scalbn          (double  __x, int __n)    ; extern   double         __scalbn          (double  __x, int __n)      ;

 
extern   int        ilogb        (double  __x)   ; extern   int        __ilogb        (double  __x)    ;


# 330 "/usr/include/bits/mathcalls.h" 3

# 63 "/usr/include/math.h" 2 3







 











# 1 "/usr/include/bits/mathcalls.h" 1 3
 


















 






























 

 
extern   float          acosf         (float   __x)    ; extern   float         __acosf         (float   __x)      ;
 
extern   float          asinf         (float   __x)    ; extern   float         __asinf         (float   __x)      ;
 
extern   float          atanf         (float   __x)    ; extern   float         __atanf         (float   __x)      ;
 
extern   float          atan2f         (float   __y, float   __x)    ; extern   float         __atan2f         (float   __y, float   __x)      ;

 
extern   float          cosf         (float   __x)    ; extern   float         __cosf         (float   __x)      ;
 
extern   float          sinf         (float   __x)    ; extern   float         __sinf         (float   __x)      ;
 
extern   float          tanf         (float   __x)    ; extern   float         __tanf         (float   __x)      ;







 

 
extern   float          coshf         (float   __x)    ; extern   float         __coshf         (float   __x)      ;
 
extern   float          sinhf         (float   __x)    ; extern   float         __sinhf         (float   __x)      ;
 
extern   float          tanhf         (float   __x)    ; extern   float         __tanhf         (float   __x)      ;


 
extern   float          acoshf         (float   __x)    ; extern   float         __acoshf         (float   __x)      ;
 
extern   float          asinhf         (float   __x)    ; extern   float         __asinhf         (float   __x)      ;
 
extern   float          atanhf         (float   __x)    ; extern   float         __atanhf         (float   __x)      ;


 

 
extern   float          expf         (float   __x)    ; extern   float         __expf         (float   __x)      ;








 
extern   float          frexpf         (float   __x, int *__exponent)    ; extern   float         __frexpf         (float   __x, int *__exponent)      ;

 
extern   float          ldexpf         (float   __x, int __exponent)    ; extern   float         __ldexpf         (float   __x, int __exponent)      ;

 
extern   float          logf         (float   __x)    ; extern   float         __logf         (float   __x)      ;

 
extern   float          log10f         (float   __x)    ; extern   float         __log10f         (float   __x)      ;

 
extern   float          modff         (float   __x, float   *__iptr)    ; extern   float         __modff         (float   __x, float   *__iptr)      ;


 
extern   float          expm1f         (float   __x)    ; extern   float         __expm1f         (float   __x)      ;

 
extern   float          log1pf         (float   __x)    ; extern   float         __log1pf         (float   __x)      ;

 
extern   float          logbf         (float   __x)    ; extern   float         __logbf         (float   __x)      ;











 

 
extern   float          powf         (float   __x, float   __y)    ; extern   float         __powf         (float   __x, float   __y)      ;

 
extern   float          sqrtf         (float   __x)    ; extern   float         __sqrtf         (float   __x)      ;


 
extern   float          hypotf         (float   __x, float   __y)    ; extern   float         __hypotf         (float   __x, float   __y)      ;



 
extern   float          cbrtf         (float   __x)    ; extern   float         __cbrtf         (float   __x)      ;



 

 
extern   float          ceilf         (float   __x)    ; extern   float         __ceilf         (float   __x)      ;

 
extern   float          fabsf         (float   __x)     __attribute__ (    (__const__)  ); extern   float         __fabsf         (float   __x)     __attribute__ (    (__const__)  )  ;

 
extern   float          floorf         (float   __x)    ; extern   float         __floorf         (float   __x)      ;

 
extern   float          fmodf         (float   __x, float   __y)    ; extern   float         __fmodf         (float   __x, float   __y)      ;


 

extern  int    __isinff     (float   __value)   __attribute__ ((__const__));


 

extern  int    isinff     (float   __value)   __attribute__ ((__const__));

 
extern   int       finitef       (float   __value)    __attribute__ (  (__const__) ); extern   int       __finitef       (float   __value)    __attribute__ (  (__const__) ) ;

 





extern   float          infnanf         (int __error)     __attribute__ (    (__const__)  ); extern   float         __infnanf         (int __error)     __attribute__ (    (__const__)  )  ;

 
extern   float          dremf         (float   __x, float   __y)    ; extern   float         __dremf         (float   __x, float   __y)      ;


 
extern   float          significandf         (float   __x)    ; extern   float         __significandf         (float   __x)      ;



 
extern   float          copysignf         (float   __x, float   __y)     __attribute__ (    (__const__)  ); extern   float         __copysignf         (float   __x, float   __y)     __attribute__ (    (__const__)  )  ;









 
extern   int       isnanf       (float   __value)    __attribute__ (  (__const__) ); extern   int       __isnanf       (float   __value)    __attribute__ (  (__const__) ) ;

 
extern   float          j0f         (float  )    ; extern   float         __j0f         (float  )      ;
extern   float          j1f         (float  )    ; extern   float         __j1f         (float  )      ;
extern   float          jnf         (int, float  )    ; extern   float         __jnf         (int, float  )      ;
extern   float          y0f         (float  )    ; extern   float         __y0f         (float  )      ;
extern   float          y1f         (float  )    ; extern   float         __y1f         (float  )      ;
extern   float          ynf         (int, float  )    ; extern   float         __ynf         (int, float  )      ;




 
extern   float          erff         (float  )    ; extern   float         __erff         (float  )      ;
extern   float          erfcf         (float  )    ; extern   float         __erfcf         (float  )      ;
extern   float          lgammaf         (float  )    ; extern   float         __lgammaf         (float  )      ;
extern   float          tgammaf         (float  )    ; extern   float         __tgammaf         (float  )      ;



 
extern   float          gammaf         (float  )    ; extern   float         __gammaf         (float  )      ;



 


extern   float          lgammaf_r            (float  , int *__signgamp)    ; extern   float         __lgammaf_r            (float  , int *__signgamp)      ;




 

extern   float          rintf         (float   __x)    ; extern   float         __rintf         (float   __x)      ;

 
extern   float          nextafterf         (float   __x, float   __y)     __attribute__ (    (__const__)  ); extern   float         __nextafterf         (float   __x, float   __y)     __attribute__ (    (__const__)  )  ;




 
extern   float          remainderf         (float   __x, float   __y)    ; extern   float         __remainderf         (float   __x, float   __y)      ;


 
extern   float          scalbf         (float   __x, float   __n)    ; extern   float         __scalbf         (float   __x, float   __n)      ;


 
extern   float          scalbnf         (float   __x, int __n)    ; extern   float         __scalbnf         (float   __x, int __n)      ;

 
extern   int       ilogbf       (float   __x)   ; extern   int       __ilogbf       (float   __x)    ;


# 330 "/usr/include/bits/mathcalls.h" 3

# 82 "/usr/include/math.h" 2 3





 











# 1 "/usr/include/bits/mathcalls.h" 1 3
 


















 






























 

 
extern   long double          acosl         (long double   __x)    ; extern   long double         __acosl         (long double   __x)      ;
 
extern   long double          asinl         (long double   __x)    ; extern   long double         __asinl         (long double   __x)      ;
 
extern   long double          atanl         (long double   __x)    ; extern   long double         __atanl         (long double   __x)      ;
 
extern   long double          atan2l         (long double   __y, long double   __x)    ; extern   long double         __atan2l         (long double   __y, long double   __x)      ;

 
extern   long double          cosl         (long double   __x)    ; extern   long double         __cosl         (long double   __x)      ;
 
extern   long double          sinl         (long double   __x)    ; extern   long double         __sinl         (long double   __x)      ;
 
extern   long double          tanl         (long double   __x)    ; extern   long double         __tanl         (long double   __x)      ;







 

 
extern   long double          coshl         (long double   __x)    ; extern   long double         __coshl         (long double   __x)      ;
 
extern   long double          sinhl         (long double   __x)    ; extern   long double         __sinhl         (long double   __x)      ;
 
extern   long double          tanhl         (long double   __x)    ; extern   long double         __tanhl         (long double   __x)      ;


 
extern   long double          acoshl         (long double   __x)    ; extern   long double         __acoshl         (long double   __x)      ;
 
extern   long double          asinhl         (long double   __x)    ; extern   long double         __asinhl         (long double   __x)      ;
 
extern   long double          atanhl         (long double   __x)    ; extern   long double         __atanhl         (long double   __x)      ;


 

 
extern   long double          expl         (long double   __x)    ; extern   long double         __expl         (long double   __x)      ;








 
extern   long double          frexpl         (long double   __x, int *__exponent)    ; extern   long double         __frexpl         (long double   __x, int *__exponent)      ;

 
extern   long double          ldexpl         (long double   __x, int __exponent)    ; extern   long double         __ldexpl         (long double   __x, int __exponent)      ;

 
extern   long double          logl         (long double   __x)    ; extern   long double         __logl         (long double   __x)      ;

 
extern   long double          log10l         (long double   __x)    ; extern   long double         __log10l         (long double   __x)      ;

 
extern   long double          modfl         (long double   __x, long double   *__iptr)    ; extern   long double         __modfl         (long double   __x, long double   *__iptr)      ;


 
extern   long double          expm1l         (long double   __x)    ; extern   long double         __expm1l         (long double   __x)      ;

 
extern   long double          log1pl         (long double   __x)    ; extern   long double         __log1pl         (long double   __x)      ;

 
extern   long double          logbl         (long double   __x)    ; extern   long double         __logbl         (long double   __x)      ;











 

 
extern   long double          powl         (long double   __x, long double   __y)    ; extern   long double         __powl         (long double   __x, long double   __y)      ;

 
extern   long double          sqrtl         (long double   __x)    ; extern   long double         __sqrtl         (long double   __x)      ;


 
extern   long double          hypotl         (long double   __x, long double   __y)    ; extern   long double         __hypotl         (long double   __x, long double   __y)      ;



 
extern   long double          cbrtl         (long double   __x)    ; extern   long double         __cbrtl         (long double   __x)      ;



 

 
extern   long double          ceill         (long double   __x)    ; extern   long double         __ceill         (long double   __x)      ;

 
extern   long double          fabsl         (long double   __x)     __attribute__ (    (__const__)  ); extern   long double         __fabsl         (long double   __x)     __attribute__ (    (__const__)  )  ;

 
extern   long double          floorl         (long double   __x)    ; extern   long double         __floorl         (long double   __x)      ;

 
extern   long double          fmodl         (long double   __x, long double   __y)    ; extern   long double         __fmodl         (long double   __x, long double   __y)      ;


 

extern  int    __isinfl     (long double   __value)   __attribute__ ((__const__));


 

extern  int    isinfl     (long double   __value)   __attribute__ ((__const__));

 
extern   int       finitel       (long double   __value)    __attribute__ (  (__const__) ); extern   int       __finitel       (long double   __value)    __attribute__ (  (__const__) ) ;

 





extern   long double          infnanl         (int __error)     __attribute__ (    (__const__)  ); extern   long double         __infnanl         (int __error)     __attribute__ (    (__const__)  )  ;

 
extern   long double          dreml         (long double   __x, long double   __y)    ; extern   long double         __dreml         (long double   __x, long double   __y)      ;


 
extern   long double          significandl         (long double   __x)    ; extern   long double         __significandl         (long double   __x)      ;



 
extern   long double          copysignl         (long double   __x, long double   __y)     __attribute__ (    (__const__)  ); extern   long double         __copysignl         (long double   __x, long double   __y)     __attribute__ (    (__const__)  )  ;









 
extern   int       isnanl       (long double   __value)    __attribute__ (  (__const__) ); extern   int       __isnanl       (long double   __value)    __attribute__ (  (__const__) ) ;

 
extern   long double          j0l         (long double  )    ; extern   long double         __j0l         (long double  )      ;
extern   long double          j1l         (long double  )    ; extern   long double         __j1l         (long double  )      ;
extern   long double          jnl         (int, long double  )    ; extern   long double         __jnl         (int, long double  )      ;
extern   long double          y0l         (long double  )    ; extern   long double         __y0l         (long double  )      ;
extern   long double          y1l         (long double  )    ; extern   long double         __y1l         (long double  )      ;
extern   long double          ynl         (int, long double  )    ; extern   long double         __ynl         (int, long double  )      ;




 
extern   long double          erfl         (long double  )    ; extern   long double         __erfl         (long double  )      ;
extern   long double          erfcl         (long double  )    ; extern   long double         __erfcl         (long double  )      ;
extern   long double          lgammal         (long double  )    ; extern   long double         __lgammal         (long double  )      ;
extern   long double          tgammal         (long double  )    ; extern   long double         __tgammal         (long double  )      ;



 
extern   long double          gammal         (long double  )    ; extern   long double         __gammal         (long double  )      ;



 


extern   long double          lgammal_r            (long double  , int *__signgamp)    ; extern   long double         __lgammal_r            (long double  , int *__signgamp)      ;




 

extern   long double          rintl         (long double   __x)    ; extern   long double         __rintl         (long double   __x)      ;

 
extern   long double          nextafterl         (long double   __x, long double   __y)     __attribute__ (    (__const__)  ); extern   long double         __nextafterl         (long double   __x, long double   __y)     __attribute__ (    (__const__)  )  ;




 
extern   long double          remainderl         (long double   __x, long double   __y)    ; extern   long double         __remainderl         (long double   __x, long double   __y)      ;


 
extern   long double          scalbl         (long double   __x, long double   __n)    ; extern   long double         __scalbl         (long double   __x, long double   __n)      ;


 
extern   long double          scalbnl         (long double   __x, int __n)    ; extern   long double         __scalbnl         (long double   __x, int __n)      ;

 
extern   int       ilogbl       (long double   __x)   ; extern   int       __ilogbl       (long double   __x)    ;


# 330 "/usr/include/bits/mathcalls.h" 3

# 99 "/usr/include/math.h" 2 3













 
extern int signgam;



 
# 232 "/usr/include/math.h" 3



 
typedef enum
{
  _IEEE_ = -1,	 
  _SVID_,	 
  _XOPEN_,	 
  _POSIX_,
  _ISOC_	 
} _LIB_VERSION_TYPE;

 


extern _LIB_VERSION_TYPE _LIB_VERSION;




 





struct __exception



  {
    int type;
    char *name;
    double arg1;
    double arg2;
    double retval;
  };


extern int matherr  (struct __exception *__exc)  throw ()  ;






 







 

# 1 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/float.h" 1 3
 



 

    


    


    


    


    


    


    


    


    


    


    



    


    


    


    


    


    


    


    


    



    


    


    



union __convert_long_double {
  unsigned __convert_long_double_i[4];
  long double __convert_long_double_d;
};


    


    


    


    


    


    




# 289 "/usr/include/math.h" 2 3


# 299 "/usr/include/math.h" 3



 
















 


# 336 "/usr/include/math.h" 3



 






 





# 407 "/usr/include/math.h" 3


} 



# 3 "test.cpp" 2

# 1 "/usr/include/string.h" 1 3
 

















 








extern "C" { 

 


# 1 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h" 1 3






 


# 19 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h" 3



 


 





 


# 61 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h" 3


 





 


















 





 

 

# 131 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h" 3


 

 


# 188 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h" 3





 




 

# 271 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h" 3


# 283 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h" 3


 

 

# 317 "/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h" 3




 





















# 33 "/usr/include/string.h" 2 3



 
extern void *  memcpy  (void *    __dest,
			    __const void *    __src, size_t __n)  throw ()  ;
 

extern void *  memmove  (void *  __dest, __const void *  __src,
			     size_t __n)  throw ()  ;

 



extern void *  memccpy  (void *  __dest, __const void *  __src,
			     int __c, size_t __n)  throw ()  ;



 
extern void *  memset  (void *  __s, int __c, size_t __n)  throw ()  ;

 
extern int memcmp  (__const void *  __s1, __const void *  __s2,
			size_t __n)  throw ()  ;

 
extern void *  memchr  (__const void *  __s, int __c, size_t __n)  throw ()  ;








 
extern char *strcpy  (char *   __dest,
			  __const char *   __src)  throw ()  ;
 
extern char *strncpy  (char *   __dest,
			   __const char *   __src, size_t __n)  throw ()  ;

 
extern char *strcat  (char *   __dest,
			  __const char *   __src)  throw ()  ;
 
extern char *strncat  (char *   __dest,
			   __const char *   __src, size_t __n)  throw ()  ;

 
extern int strcmp  (__const char *__s1, __const char *__s2)  throw ()  ;
 
extern int strncmp  (__const char *__s1, __const char *__s2, size_t __n)  throw ()  ;

 
extern int strcoll  (__const char *__s1, __const char *__s2)  throw ()  ;
 
extern size_t strxfrm  (char *   __dest,
			    __const char *   __src, size_t __n)  throw ()  ;

# 107 "/usr/include/string.h" 3



 
extern char *__strdup  (__const char *__s)  throw ()  ;
extern char *strdup  (__const char *__s)  throw ()  ;


 






# 143 "/usr/include/string.h" 3


 
extern char *strchr  (__const char *__s, int __c)  throw ()  ;
 
extern char *strrchr  (__const char *__s, int __c)  throw ()  ;

 

extern size_t strcspn  (__const char *__s, __const char *__reject)  throw ()  ;
 

extern size_t strspn  (__const char *__s, __const char *__accept)  throw ()  ;
 
extern char *strpbrk  (__const char *__s, __const char *__accept)  throw ()  ;
 
extern char *strstr  (__const char *__haystack, __const char *__needle)  throw ()  ;









 
extern char *strtok  (char *   __s,
			  __const char *   __delim)  throw ()  ;

 

extern char *__strtok_r  (char *   __s,
			      __const char *   __delim,
			      char **   __save_ptr)  throw ()  ;

extern char *strtok_r  (char *   __s,
			    __const char *   __delim,
			    char **   __save_ptr)  throw ()  ;


# 197 "/usr/include/string.h" 3



 
extern size_t strlen  (__const char *__s)  throw ()  ;








 
extern char *strerror  (int __errnum)  throw ()  ;

 

extern char *__strerror_r  (int __errnum, char *__buf, size_t __buflen)  throw ()  ;
extern char *strerror_r  (int __errnum, char *__buf, size_t __buflen)  throw ()  ;


 

extern void __bzero  (void *  __s, size_t __n)  throw ()  ;


 
extern void bcopy  (__const void *  __src, void *  __dest, size_t __n)  throw ()  ;

 
extern void bzero  (void *  __s, size_t __n)  throw ()  ;

 
extern int bcmp  (__const void *  __s1, __const void *  __s2, size_t __n)  throw ()  ;

 
extern char *index  (__const char *__s, int __c)  throw ()  ;

 
extern char *rindex  (__const char *__s, int __c)  throw ()  ;

 

extern int __ffs  (int __i)  throw ()   __attribute__ ((const));
extern int ffs  (int __i)  throw ()   __attribute__ ((const));

 









 
extern int __strcasecmp  (__const char *__s1, __const char *__s2)  throw ()  ;
extern int strcasecmp  (__const char *__s1, __const char *__s2)  throw ()  ;

 
extern int strncasecmp  (__const char *__s1, __const char *__s2,
			     size_t __n)  throw ()  ;


# 271 "/usr/include/string.h" 3



 

extern char *strsep  (char **   __stringp,
			  __const char *   __delim)  throw ()  ;


# 313 "/usr/include/string.h" 3




# 341 "/usr/include/string.h" 3



} 


# 4 "test.cpp" 2



# 1 "stdmods.h" 1




module F(float);
module f(float);
module G(float);
module g(float);
module SetPos(float, float, float);
module TL(float);
module TR(float);
module PD(float);
module PU(float);
module RL(float);
module RR(float);
module TA();
module LBRCT();
module RBRCT();



# 7 "test.cpp" 2







module A();
module B(int,float);
module C();
module D(int,int);
module E();
module F();
module G();
module H();
module I(int);
module J();
module K();
module L();


FILE* fp;


Start:
{
  fp = fopen("input.txt", "r");
  fputc('A', fp);
  int n=0;
  for (n=0; n<1010; n++)
	printf("%d --> \n", n);
}

End:
{
  fclose(fp);
}


derivation length: 51 - strlen("module and produce");

void Func(Struct* pS)
{
  for (int i=0; i<123; i++)
    pS->arr[i] = 1.0/i;
}

A() >  LBRCT() B(a,b)  RBRCT() :
{
  produce B(a,b) A();
}

A() >   LBRCT() B(a,b) LBRCT() C() RBRCT() RBRCT() :
{
  produce A(n, s) LBRCT() B(a,b)  C() RBRCT();
}

A() > LBRCT() B(a,b) LBRCT() C() RBRCT() F() RBRCT() :
{
  produce A() LBRCT() C() RBRCT() B(a,b) F();
}

A() > LBRCT() RBRCT()  LBRCT() H() I(c) RBRCT()  :
{
  produce  A() I(c) H();
}

A() > LBRCT() B(a,b) RBRCT() LBRCT() H() RBRCT() K():
{
  produce A() LBRCT()B(a,b)RBRCT() LBRCT()H()RBRCT() K() L();
}

A()K() < L():
{
  produce L()I(1);
}

A() LBRCT() B(a,b) LBRCT() C()   < D(c,d):
{
  produce D(c,d) I(1);
}



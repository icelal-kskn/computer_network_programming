/*
#####  #####   ######  ######   ####   ######  #####   #    #  ######  #####
  #    #    #  #       #       #       #       #    #  #    #  #       #    #
  #    #    #  #####   #####    ####   #####   #    #  #    #  #####   #    #  
  #    #####   #       #            #  #       #####   #    #  #       #####
  #    #   #   #       #       #    #  #       #   #    #  #   #       #   #
  #    #    #  ######  ######   ####   ######  #    #    ##    ######  #    #
*/
#include "local.h"
#include "tree.h"
 
static int cur = 0,                             /* Index into output array   */
       been_allocated = 0,                      /* Has array been allocated? */
       depth = 0;                               /* Indenting level           */
 
dir_result     *
do_dir_1_svc( char **f, struct svc_req * rqstp) {
  static dir_result result;                     /* Either array or void      */
  struct stat       statbuff;                   /* For status check of entry */
  DIR               *dp;                        /* Directory entry           */
  struct dirent     *dentry;                    /* Pointer to current entry  */
  char              *current;                   /* Position in output array  */
  int               length;                     /* Length of current entry   */
  static char       buffer[DIR_1];              /* Temp storage location     */
 
  if (!been_allocated)                          /* If not done then allocate */
    if ((result.dir_result_u.line_ptr=(line *)malloc(sizeof(line))) == NULL)
      return (&result);
    else{
      been_allocated = 1;                       /* Record allocation         */
  } else if ( depth == 0 )      {               /* Clear 'old' contents.     */ 
    memset(result.dir_result_u.line_ptr, 0, sizeof(line));
    cur = 0;                                    /* Reset indent level        */
  }
  if ((dp = opendir(*f)) != NULL) {             /* If successfully opened    */
    chdir(*f);                                  /* Change to the directory   */
    dentry = readdir(dp);                       /* Read first entry          */
    while (dentry != NULL) {
      if (stat(dentry->d_name, &statbuff) != -1)        /* If accessible */
        if ((statbuff.st_mode & S_IFMT) == S_IFDIR &&   /* & a directory */
            dentry->d_name[0] != '.') {                 /* & not . or .. */
          depth += INDENT;                              /* adjust indent */
           /*
            * Store the entry in buffer - then copy buffer into larger array.
           */
          sprintf(buffer, "%*s %-10s\n", depth, " ", dentry->d_name);
          length = strlen(buffer);
          memcpy((char *)result.dir_result_u.line_ptr + cur, buffer, length);
          cur += length;                       /* update ptr to ref next loc */
          current = dentry->d_name;            /* the new directory          */
          (dir_result *)do_dir_1_svc(&current, rqstp);  /* call self         */
          chdir("..");                         /* back to previous level     */
          depth -= INDENT;                     /* adjust the indent level    */
        }
      dentry = readdir(dp);                    /* Read the next entry        */
    }
    closedir(dp);                              /* Done with this one         */
  }
  return (&result);                            /* Pass back the result       */
}

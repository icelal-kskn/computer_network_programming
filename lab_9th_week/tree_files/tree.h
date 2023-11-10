/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _TREE_H_RPCGEN
#define _TREE_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif

#define MAXP 4096
#define DELIM "\n"
#define INDENT 5
#define DIR_1 128

typedef char line[MAXP];

typedef line *line_ptr;

struct dir_result {
	int errno;
	union {
		line *line_ptr;
	} dir_result_u;
};
typedef struct dir_result dir_result;

#define TREE 0x2000001
#define one 1

#if defined(__STDC__) || defined(__cplusplus)
#define do_dir 1
extern  dir_result * do_dir_1(char **, CLIENT *);
extern  dir_result * do_dir_1_svc(char **, struct svc_req *);
extern int tree_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define do_dir 1
extern  dir_result * do_dir_1();
extern  dir_result * do_dir_1_svc();
extern int tree_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_line (XDR *, line);
extern  bool_t xdr_line_ptr (XDR *, line_ptr*);
extern  bool_t xdr_dir_result (XDR *, dir_result*);

#else /* K&R C */
extern bool_t xdr_line ();
extern bool_t xdr_line_ptr ();
extern bool_t xdr_dir_result ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_TREE_H_RPCGEN */

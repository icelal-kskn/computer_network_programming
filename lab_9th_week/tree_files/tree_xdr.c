/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "tree.h"

bool_t
xdr_line (XDR *xdrs, line objp)
{
	register int32_t *buf;

	 if (!xdr_vector (xdrs, (char *)objp, MAXP,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_line_ptr (XDR *xdrs, line_ptr *objp)
{
	register int32_t *buf;

	 if (!xdr_pointer (xdrs, (char **)objp, sizeof (line), (xdrproc_t) xdr_line))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_dir_result (XDR *xdrs, dir_result *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->errno))
		 return FALSE;
	switch (objp->errno) {
	case 0:
		 if (!xdr_pointer (xdrs, (char **)&objp->dir_result_u.line_ptr, sizeof (line), (xdrproc_t) xdr_line))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}
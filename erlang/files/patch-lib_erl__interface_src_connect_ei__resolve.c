
$FreeBSD: ports/lang/erlang/files/patch-lib_erl__interface_src_connect_ei__resolve.c,v 1.1 2006/11/25 16:47:07 olgeni Exp $

--- lib/erl_interface/src/connect/ei_resolve.c.orig
+++ lib/erl_interface/src/connect/ei_resolve.c
@@ -621,7 +621,8 @@
 
   return result;
 #else
-  return gethostbyname_r(name,hostp,buffer,buflen,h_errnop);
+  struct hostent *dummy;
+  return gethostbyname_r(name,hostp,buffer,buflen,&dummy,h_errnop);
 #endif
 #endif
 #endif

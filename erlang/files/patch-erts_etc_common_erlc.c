
$FreeBSD: ports/lang/erlang/files/patch-erts_etc_common_erlc.c,v 1.1 2010/04/07 22:04:49 olgeni Exp $

--- erts/etc/common/erlc.c.orig
+++ erts/etc/common/erlc.c
@@ -186,6 +186,7 @@
      */
 
     PUSH("-noinput");
+    PUSH2("-smp", "disable");
     PUSH2("-mode", "minimal");
     PUSH2("-boot", "start_clean");
     PUSH3("-s", "erl_compile", "compile_cmdline");

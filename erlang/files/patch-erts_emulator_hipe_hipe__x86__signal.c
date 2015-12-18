--- erts/emulator/hipe/hipe_x86_signal.c
+++ erts/emulator/hipe/hipe_x86_signal.c
@@ -234,7 +234,29 @@ static void do_init(void)
 #define INIT()	do { if (!init_done()) do_init(); } while (0)
 #endif /* __sun__ */
 
-#if !(defined(__GLIBC__) || defined(__DARWIN__) || defined(__NetBSD__) || defined(__sun__))
+#if defined(__FreeBSD__)
+/*
+ * This is a copy of Darwin code for FreeBSD.
+ * CAVEAT: detailed semantics are not verified yet.
+ */
+#include <dlfcn.h>
+static int (*__next_sigaction)(int, const struct sigaction*, struct sigaction*);
+#define init_done()	(__next_sigaction != 0)
+extern int _sigaction(int, const struct sigaction*, struct sigaction*);
+#define __SIGACTION _sigaction
+static void do_init(void)
+{
+    __next_sigaction = dlsym(RTLD_NEXT, "sigaction");
+    if (__next_sigaction != 0)
+	return;
+    perror("dlsym_freebsd");
+    abort();
+}
+#define _NSIG NSIG
+#define INIT()	do { if (!init_done()) do_init(); } while (0)
+#endif /* __FreeBSD__ */
+
+#if !(defined(__GLIBC__) || defined(__DARWIN__) || defined(__NetBSD__) || defined(__FreeBSD__) || defined(__sun__))
 /*
  * Unknown libc -- assume musl.  Note: musl deliberately does not provide a musl-specific
  * feature test macro, so we cannot check for it.
@@ -259,7 +281,7 @@ static void do_init(void)
 #define _NSIG NSIG
 #endif
 #define INIT()	do { if (!init_done()) do_init(); } while (0)
-#endif	/* !(__GLIBC__ || __DARWIN__ || __NetBSD__ || __sun__) */
+#endif	/* !(__GLIBC__ || __DARWIN__ || __NetBSD__ || __FreeBSD__ || __sun__) */
 
 #if !defined(__NetBSD__)
 /*
@@ -299,7 +321,7 @@ int __SIGACTION(int signum, const struct sigaction *act, struct sigaction *oldac
 /*
  * This catches the application's own sigaction() calls.
  */
-#if !defined(__DARWIN__) && !defined(__NetBSD__)
+#if !defined(__DARWIN__) && !defined(__NetBSD__) && !defined(__FreeBSD__)
 int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)
 {
     return my_sigaction(signum, act, oldact);

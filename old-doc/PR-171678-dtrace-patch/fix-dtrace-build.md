# Fix dtrace build issue

## Notice

This patch is no longer needed for the FreeBSD 9-STABLE r251857 and later; the PR 171678 code has been merged.

## Symptom

On FreeBSD 9.1-STABLE r245019, 
When the dtrace build option is enabled,
building this port will cause this error and stop:

        checking for sys/sdt.h... yes
        dtrace: failed to compile script emulator/beam/erlang_dtrace.d: "/usr/lib/dtrace/regs_x86.d", line 2: type redeclared: struct devinfo
        configure: error: Could not precompile erlang_dtrace.d: dtrace -h failed
        configure: error: /bin/sh '/home/kenji/src/erlang-freebsd-port/erlang/work/otp_src_R15B03/erts/configure' failed for erts
        ===>  Script "configure" failed unexpectedly.

## Workaround

A workaround is posted in FreeBSD PR bin/171678 at <http://www.freebsd.org/cgi/query-pr.cgi?pr=171678>.

## How to apply the patch

	cd /usr/src
	patch -p1 < $DIRECTORY_OF_PATCH/171678-dtrace_depends_on_sysctl.patch
	cd /usr/src/cddl
	make obj && make && make install


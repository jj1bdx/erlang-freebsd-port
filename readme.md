# (Unofficial) FreeBSD Port for Erlang/OTP

This is an unofficial FreeBSD Port file for Erlang/OTP.
The contents are based on the `lang/erlang` Port
available in the FreeBSD Port tree.

This Port is highly experimental.

Current version is for R15B01, tested on 9.0-RELEASE/amd64 and 8.2-RELEASE/i386.

In this Port parallel make is enabled. (aka `MAKE_JOBS_SAFE = true`)

## DTrace support

<http://wiki.freebsd.org/DTrace> is a must read for testing DTrace.
At least you've got to do the following things:

* Rebuild the kernel with all the necessary options.
* Add necessary definitions in `make.conf`; Erlang BEAM works on the userland.
* Compile the Port with the `root` privilege; otherwise `dtrace -h` won't work.
* Invoke `dtrace` command with the `root` privilege when profiling; using `sudo` may help. (You don't have to run the target Erlang BEAM privileged BTW.)

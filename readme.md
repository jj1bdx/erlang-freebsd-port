# (Unofficial) FreeBSD Port for Erlang/OTP

This is an unofficial FreeBSD Port file for Erlang/OTP.
The contents are based on the `lang/erlang` Port
available in the FreeBSD Port tree.

This Port is highly experimental, so use with care.

Current version is for R15B03-1, tested on 9.1-STABLE/amd64 and 8.3-STABLE/i386.

This port is based on FreeBSD Ports svn r310183.

## Notes

Consider applying the patch in FreeBSD PR `bin/171678` to compile the dtrace version. The patch is included under the directory `PR-171678-dtrace-patch`. See `PR-171678-dtrace-patch/fix-dtrace-build.md` for the further details.

The `make config` flag `GCC46` must be enabled when building the DTrace-enabled version on amd64. Symptom: when building `erts/emulator/beam/erl_nif.c` with the stock cc (4.2.1) on 9.1-PRERELEASE/amd64, the compiler takes too much CPU time and does not proceed. This problem will be solved by using gcc 4.6 in the Ports library `lang/gcc46`. Related info: <http://www.freebsd.org/cgi/query-pr.cgi?pr=147451>. (Thanks Jimmy Olgeni for helping chasing this bug)

Merged the main line files for R15B03-1

In this Port parallel make is *disabled* as default. Use the `make config` option `PARALLELMAKE`.

For reducing memory consumption on building, try `env ERL_PORTS_MAX=4096 make`.

`USE_OPENSSL` for enabling `bsd.openssl.mk` does not seem to work, 
so it is not explicitly set in the `Makefile`. 
The library search path decides what to link,
and it seems `/usr/local/lib` takes precedence over `/usr/lib`.
You can verify which one is linked by
`objdump -x /usr/local/lib/erlang/lib/crypto-MODULE_VERSION/priv/lib/crypto.so`
and check out the version numbers for `libssl.so.*`.

Native Libraries compilation flag is now supported as `NATIVELIBS` in `make config`.
On amd64, however, it does not work on the libraries yet.

## DTrace support

<http://wiki.freebsd.org/DTrace> is a must read for testing DTrace.
At least you've got to do the following things:

* Rebuild the kernel with all the necessary options.
* Add necessary definitions in `make.conf`; Erlang BEAM works on the userland.
* Compile the Port with the `root` privilege; otherwise `dtrace -h` won't work.
* Invoke `dtrace` command with the `root` privilege when profiling; using `sudo` may help. (You don't have to run the target Erlang BEAM privileged BTW.)

## Acknowledgment

* Jimmy Olgeni, for maintaining the original Erlang Port of FreeBSD.

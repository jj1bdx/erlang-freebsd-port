# (Unofficial) FreeBSD Port for Erlang/OTP

This is an unofficial FreeBSD Port file for Erlang/OTP.
The contents are based on the `lang/erlang` Port
available in the FreeBSD Port tree.

This Port is highly experimental, so use with care.

Current version is for R15B01, tested on 9.1-PRERELEASE/amd64 and 8.3-RELEASE/i386.

## Notes

Merged the main line files for R15B01 as described in <http://www.freebsd.org/cgi/query-pr.cgi?pr=163711>.

Merged OptionsNG patch at <http://www.freebsd.org/cgi/query-pr.cgi?pr=169355>.

In this Port parallel make is *disabled* as default. Use the `make config` option `PARALLELMAKE`.

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

# A private FreeBSD Erlang Port

The official port status in Freshports is <https://www.freshports.org/lang/erlang/>.

## Tentative revival: for 18.2

18-DEC-2015: This is an unofficial experimental FreeBSD Erlang Port enabling
HiPE for 18.2 on 10.2-STABLE, built based on Jimmy Olgeni's Ports `lang/erlang`
and `lang/erlang-runtime18`.

See https://github.com/erlang/otp/pull/926 for the patch details for HiPE.

## Please check FreeBSD official Ports first.

I will no longer maintain this archive regularly. 

Jimmy Olgeni has been actively maintaining the original Erlang and other
related ports.

## DTrace support

<http://wiki.freebsd.org/DTrace> is a must read for testing DTrace.

At least you've got to do the following things:

* Rebuild the kernel with all the necessary options.
* Add necessary definitions in `make.conf`; Erlang BEAM works on the userland.
* Compile the Port with the `root` privilege; otherwise `dtrace -h` won't work.
* Invoke `dtrace` command with the `root` privilege when profiling; using `sudo` may help. (You don't have to run the target Erlang BEAM privileged BTW.)

## Acknowledgment

* Jimmy Olgeni, for maintaining the original Erlang-related Ports of FreeBSD.
* Stefan Grundmann, for native libs patch based on the erlang-questions mailing list article <http://erlang.org/pipermail/erlang-questions/2014-April/078460.html>

Updating an Erlang/OTP Port (files under the Ports tree)
for FreeBSD is not a complicated task,
with the latest pieces of the Port files.
You can find out the latest pieces at
[the FreeBSD CVSweb page for Erlang Port](http://www.freebsd.org/cgi/cvsweb.cgi/ports/lang/erlang/).

You need to do the following things:

* [Updating the source file names](#filenames)
* [Preparing the library list](#lib)
* [Preparing the man file list](#man)
* [Removing/editing/adding patches](#patches)
* [Updating the checksum file](#makesum)
* [Preparing the package list](#plist)
* [Test building](#build)
* [References](#ref)

## <a name="filenames"/>Updating the source file names

The following parts of the main `Makefile` must be modified
to specify the related source file names
(in a unified diff-like format):

        -PORTVERSION=   r14b04
        +PORTVERSION=   r14b

        -DISTNAME=      otp_src_R14B04
        +DISTNAME=      otp_src_R15B

        -ERLANG_MAN=    otp_doc_man_R14B04.tar.gz
        +ERLANG_MAN=    otp_doc_man_R15B.tar.gz

        -ERLANG_DOCS=   otp_doc_html_R14B04.tar.gz
        +ERLANG_DOCS=   otp_doc_html_R15B.tar.gz

## <a name="lib"/>Preparing the library list

`Makefile.lib` must be supplied to provide
all the version numbers of the OTP library modules.

To extract the version number, use the following shell command:

        (ls work/otp_src_*/lib/*/vsn.mk | while read _file; do
           echo -e "\\t\\t$(basename $(dirname ${_file}))-$(grep "VSN" ${_file} | grep -v "APP_VSN" | awk -F= '{ print $2 }' | sed -e "s/ *//") \\"
        done;

        echo work/otp_src_*/erts/vsn.mk | while read _file; do
           echo -e "\\t\\t$(basename $(dirname ${_file}))-$(grep "^VSN" ${_file} | awk -F= '{ print $2 }' | sed -e "s/ *//") \\"
        done) | sort > OTP-vsnlist.txt

The content of `OTP-vsnlist.txt` will be something like this:

        appmon-2.1.14.1 \
        asn1-1.7 \
        common_test-1.6.1 \
        compiler-4.8.1 \
        cosEvent-2.1.12 \
        cosEventDomain-1.1.12 \
        cosFileTransfer-1.1.13 \
        [...]
        wx-0.99.2 \
        xmerl-1.3.1 \

You have to manually edit the `Makefile.lib`
with the content of `OTP-vsnlist.txt`.
The format of `Makefile.lib` is
(beware that the last line has no backslash):

        ERTS_VSN=       5.9.1
        TOOLS_VSN=      2.6.7
        OTP_LIBS=       appmon-2.1.14.1 \
                        asn1-1.7 \
                        common_test-1.6.1 \
                        compiler-4.8.1 \
                        cosEvent-2.1.12 \
                        cosEventDomain-1.1.12 \
                        cosFileTransfer-1.1.13 \
                        [...]
                        wx-0.99.2 \
                        xmerl-1.3

The contents of `Makefile.lib` is a set of `Makefile` variables,
so all the module names must be listed with the backslash character.
(Note: `ERTS_VSN` is no longer needed, but I will include it
here just FYI.)

## <a name="man"/>Preparing the man file list

`Makefile.man` must be supplied to provide
all the version numbers of the OTP library modules.

To extract the man filenames, use the following shell command:

        tar ztf /usr/ports/distfiles/erlang/otp_doc_man_VERSION.tar.gz | \
	    sort | awk '{FS="/"; print $3;}' > OTP-manlist.txt

You have to manually edit the `Makefile.man`
with the content of `OTP-manlist.txt`.
For OTP R15B, `Makefile.man` only needs man sections 1, 3, 4, and 6,
so man section 7 must not be included.

The content of `OTP-manlist.txt` will be something like this:

	COPYRIGHT
	PR.template
	README

	man1/
	man1/ct_run.1
	man1/diameter_compile.1
	man1/epmd.1
	man1/erl.1
	man1/erl_call.1
	man1/erlc.1
	[...]
	man7/SNMP-VIEW-BASED-ACM-MIB.7
	man7/SNMPv2-MIB.7
	man7/SNMPv2-TM.7
	man7/STANDARD-MIB.7
	man7/TRANSPORT-ADDRESS-MIB.7

You have to manually edit the `Makefile.man`
with the content of `OTP-manlist.txt`.
The format of `Makefile.man` is:
(beware that the last line of each section has no backslash):

        MAN1=   ct_run.1 \
                diameter_compile.1 \
                epmd.1 \
                erl.1 \
                erl_call.1 \
                erlc.1 \
                erlsrv.1 \
                escript.1 \
                run_erl.1 \
                snmpc.1 \
                [...]
                start_webtool.1 \
                werl.1

        MAN3=   CosEventChannelAdmin.3 \
                CosEventChannelAdmin_ConsumerAdmin.3 \
                [...]
                zlib.3 \
                zlib_stub.3

        MAN4=   app.4 \
                appup.4 \
                [...]
                relup.4 \
                script.4

        MAN6=   common_test.6 \
                crypto.6 \
                [...]
                stdlib.6 \
                test_server.6

The contents of `Makefile.man` is a set of `Makefile` variables,
so all the module names must be listed with the backslash character.

## <a name="patches">Removing/editing/adding patches

FreeBSD-specific patch files are provided under the Port directory
`files`. You need to remove the obsolete patches first, by `make patches`.
You should edit the existing ones and add the new ones as well.

The naming convention of the patch file is:

        patch-lib_et_src_et__gs__contents__viewer.erl

for

        lib/et/src/et_gs_contents_viewer.erl

(Conversion of `/ -> _` and `_ -> __` is needed.)

## <a name="makesum"/>Updating the checksum file

`make makesum` is the convenient way to update the `distinfo` checksum data.

## <a name="plist"/>Preparing the package list

New binary files are occasionally added in the OTP distributions.
`pkg-plist` file must be updated as well.

## <a name="build">Test building

The building process will be like this
(note the `umask 022`):

        # I use zsh, but use whatever you want
        # as root
	# (for DTrace building with root privilege is mandatory)
        sudo zsh
        umask 022
        make fetch
        make
        make deinstall && make reinstall
        exit

## <a name="ref"/>References

* [Erlang/OTP repository at GitHub](https://github.com/erlang/otp/)
* [FreeBSD Porter's Handbook](http://www.freebsd.org/doc/en/books/porters-handbook/)

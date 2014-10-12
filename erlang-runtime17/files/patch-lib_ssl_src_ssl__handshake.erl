
$FreeBSD: head/lang/erlang-runtime17/files/patch-lib_ssl_src_ssl__handshake.erl 370520 2014-10-09 12:48:31Z olgeni $

--- lib/ssl/src/ssl_handshake.erl.orig
+++ lib/ssl/src/ssl_handshake.erl
@@ -1732,6 +1732,9 @@
 							#ec_point_formats{ec_point_format_list =
 									      ECPointFormats}});
 
+dec_hello_extensions(<<?UINT16(?SNI_EXT), ?UINT16(Len), Rest/binary>>, Acc) when Len == 0 ->
+    dec_hello_extensions(Rest, Acc#hello_extensions{sni = ""}); %% Server may send an empy SNI
+
 dec_hello_extensions(<<?UINT16(?SNI_EXT), ?UINT16(Len),
                 ExtData:Len/binary, Rest/binary>>, Acc) ->
     <<?UINT16(_), NameList/binary>> = ExtData,

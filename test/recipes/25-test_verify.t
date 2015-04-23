#! /usr/bin/perl

use strict;
use warnings;

use File::Spec::Functions qw/canonpath/;
use Test::More;
use OpenSSL::Test qw/:DEFAULT top_dir top_file/;

$ENV{OPENSSL_CONF} = File::Spec->devnull();

setup("test_verify");

plan tests => 1;

note("Expect some failures and expired certificate");
ok(run(app(["openssl", "verify", "-CApath", top_dir("certs", "demo"),
	    glob(top_file("certs", "demo", "*.pem"))])), "verying demo certs");

#! /usr/bin/perl

use strict;
use warnings;

use File::Spec;
use Test::More;
use lib 'testlib';
use OpenSSL::Test qw/setup run app test/;

$ENV{OPENSSL_CONF} = File::Spec->devnull();

setup("test_dsa");

plan tests => 6;

require_ok('recipes/tconversion.pl');

ok(run(test(["dsatest"])), "running dsatest");
ok(run(test(["dsatest", "-app2_1"])), "running dsatest -app2_1");

 SKIP: {
     skip "Skipping dsa conversion test", 3
	 if run(app(["openssl","no-dsa"], stdout => undef));

     subtest 'dsa conversions -- private key' => sub {
	 tconversion("dsa", "testdsa.pem");
     };
     subtest 'dsa conversions -- private key PKCS#8' => sub {
	 tconversion("dsa", "testdsa.pem", "pkey");
     };
     subtest 'dsa conversions -- public key' => sub {
	 tconversion("dsa", "testdsapub.pem", "dsa", "-pubin", "-pubout");
     };
}

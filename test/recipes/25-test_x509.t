#! /usr/bin/perl

use strict;
use warnings;

use File::Spec;
use Test::More;
use OpenSSL::Test qw/:DEFAULT top_file/;

$ENV{OPENSSL_CONF} = File::Spec->devnull();

setup("test_rsa");

plan tests => 4;

require_ok(top_file('test','recipes','tconversion.pl'));

subtest 'x509 -- x.509 v1 certificate' => sub {
    tconversion("x509", top_file("test","testx509.pem"));
};
subtest 'x509 -- first x.509 v3 certificate' => sub {
    tconversion("x509", top_file("test","v3-cert1.pem"));
};
subtest 'x509 -- second x.509 v3 certificate' => sub {
    tconversion("x509", top_file("test","v3-cert2.pem"));
};

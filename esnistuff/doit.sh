#!/bin/bash

#set -x

# to pick up correct .so's - maybe note 
#export LD_LIBRARY_PATH=$HOME/code/openssl

# this is one I downloaded manually via dig +short TXT _esni.encryptedsni.com
# ESNI="/wHHBBOoACQAHQAg4YSfjSyJPNr1z3F8KqzBNBnMejim0mJZaPmria3XsicAAhMBAQQAAAAAW9pQEAAAAABb4jkQAAA="
# COVER="cloudflare.net"
# HIDDEN="encryptedsni.com"


# this is one I downloaded manually via dig +short TXT _esni.www.cloudflare.com on 20181121
#ESNI="/wEU528gACQAHQAguwSAYz57kzOUzDXCAZ7aBJLWPrQwvSuNsRZbi7JzqkYAAhMBAQQAAAAAW/E4IAAAAABb+SEgAAA="
ESNI=`dig +short txt _esni.www.cloudflare.com | sed -e 's/"//g'`
HIDDEN="www.cloudflare.com"
COVER="www.cloudflare.com"


VG="yes"

# should really add getopt but this is likely short-term (famous last
# words those:-)

if [[ "$1" == "fresh" ]]
then
	echo "Checking for fresh ESNI value from $HIDDEN"
	ESNI=`dig +short TXT _esni.$HIDDEN | sed -e 's/"//g'`	
	echo "Fresh ESNI value: $ESNI"
fi	

echo "gdb cheat: r $HIDDEN $COVER $ESNI"
if [[ "$VG" == "no" ]]
then
	./esni $HIDDEN $COVER $ESNI
else
	valgrind --leak-check=full ./esni $HIDDEN $COVER $ESNI
fi

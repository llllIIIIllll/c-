#!/bin/bash


docker run -d --name ftpd_server -p 21:21 -p 30000-30009:30000-30009 \
	-e "PUBLICHOST=localhost" -e "ADDED_FLAGS=-d -d" \
	stilliard/pure-ftpd:hardened



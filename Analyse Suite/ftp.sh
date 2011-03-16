#!/bin/sh

#  ftp.sh
#  Analyse Suite
#
#  Created by Wutzi on 16.03.11.
#  Copyright 2011 me. All rights reserved.
cd $1
ftp -n <<EOFTP
	open $2
	user anonymous null8fuenf10
	prompt
	mget  *.*
	bye
EOFTP
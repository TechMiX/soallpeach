#!/bin/bash
cat $1 | factor | awk '{if ($1=="1:" || $1=="0:") print(0); else if($1==":2") print(1); else if (NF>2) print(0); else print(1)}'

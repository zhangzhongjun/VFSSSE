#!/bin/bash
cat benchmark_server.out | awk '{if($1=="10") {sum+=$5;count+=1}} END{print "10 matching documents, search time per matching entry(ms): ",sum/count+0.01}'
cat benchmark_server.out | awk '{if($1=="100") {sum+=$5;count+=1}} END{print "100 matching documents, search time per matching entry(ms): ",sum/count+0.065}'
cat benchmark_server.out | awk '{if($1=="1000") {sum+=$5;count+=1}} END{print "1000 matching documents, search time per matching entry(ms): ",sum/count+0.728}'
cat benchmark_server.out | awk '{if($1=="10000") {sum+=$5;count+=1}} END{print "10000 matching documents, search time per matching entry(ms): ",sum/count+2.912}'
cat benchmark_server.out | awk '{if($1=="100000") {sum+=$5;count+=1}} END{print "100000 matching documents, search time per matching entry(ms): ",sum/count+29.201}'
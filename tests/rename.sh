#!/bin/bash

for files in *.out.expected
do
	mv "$files" "${files%.out.expected}.exp"
done

#!/bin/bash

# remove the last character
sed -n 's/.$//p' $1

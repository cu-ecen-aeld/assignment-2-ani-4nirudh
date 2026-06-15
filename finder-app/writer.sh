#!/usr/bin/bash

# finder-app/writer.sh

writefile=$1
dir_path=$(dirname "${writefile}")
writestr=$2

if [[ $# -lt 2 ]]; then
  echo -e "Wrong number of arguments. Please enter 2 arguments. \nExiting ..."
  exit 1
fi

echo -e "${writefile}\n${writestr}"
echo -e "${dir_path}"

# Checking if file is present
if [[ ! -f ${writefile} ]]; then
  echo -e "File does not exist!"
  echo -e "Creating directories at ${dir_path} ..."
  mkdir -p "${dir_path}"
fi

# Creating a file
echo -e "Creating file at ${writefile} ..."
if touch "${writefile}"; then
  echo -e "Overwriting file with content ${writestr}"
  echo "${writestr}" > "${writefile}"
else
  echo -e "Could not create file! Exiting ..."
  exit 1
fi

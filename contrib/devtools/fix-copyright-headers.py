#!/usr/bin/env python
'''
<<<<<<< HEAD
Run this script to update all the copyright headers of files
that were changed this year.

For example:

// Copyright (c) 2009-2012 The Bitcoin Core developers

it will change it to

// Copyright (c) 2009-2015 The Bitcoin Core developers
'''
import os
import time
import re

year = time.gmtime()[0]
CMD_GIT_DATE = 'git log --format=@%%at -1 %s | date +"%%Y" -u -f -'
CMD_REGEX= "perl -pi -e 's/(20\d\d)(?:-20\d\d)? The Bitcoin/$1-%s The Bitcoin/' %s"
REGEX_CURRENT= re.compile("%s The Bitcoin" % year)
CMD_LIST_FILES= "find %s | grep %s"

FOLDERS = ["./qa", "./src"]
EXTENSIONS = [".cpp",".h", ".py"]

def get_git_date(file_path):
  r = os.popen(CMD_GIT_DATE % file_path)
  for l in r:
    # Result is one line, so just return
    return l.replace("\n","")
  return ""

n=1
for folder in FOLDERS:
  for extension in EXTENSIONS:
    for file_path in os.popen(CMD_LIST_FILES % (folder, extension)):
      file_path = os.getcwd() + file_path[1:-1]
      if file_path.endswith(extension):
        git_date = get_git_date(file_path)
        if str(year) == git_date:
          # Only update if current year is not found
          if REGEX_CURRENT.search(open(file_path, "r").read()) is None:
            print n,"Last git edit", git_date, "-", file_path
            os.popen(CMD_REGEX % (year,file_path))
            n = n + 1
=======
Run this script inside of src/ and it will look for all the files
that were changed this year that still have the last year in the
copyright headers, and it will fix the headers on that file using
a perl regex one liner.

For example: if it finds something like this and we're in 2014

// Copyright (c) 2009-2013 The Bitcoin developers

it will change it to

// Copyright (c) 2009-2014 The Bitcoin developers

It will do this for all the files in the folder and its children.

Author: @gubatron
'''
import os
import time

year = time.gmtime()[0]
last_year = year - 1
command = "perl -pi -e 's/%s The Bitcoin/%s The Bitcoin/' %s"
listFilesCommand = "find . | grep %s"

extensions = [".cpp",".h"]

def getLastGitModifiedDate(filePath):
  gitGetLastCommitDateCommand = "git log " + filePath +" | grep Date | head -n 1"
  p = os.popen(gitGetLastCommitDateCommand)
  result = ""
  for l in p:
    result = l
    break
  result = result.replace("\n","")
  return result

n=1
for extension in extensions:
  foundFiles = os.popen(listFilesCommand % extension)
  for filePath in foundFiles:
    filePath = filePath[1:-1]
    if filePath.endswith(extension):
      filePath = os.getcwd() + filePath
      modifiedTime = getLastGitModifiedDate(filePath)
      if len(modifiedTime) > 0 and str(year) in modifiedTime:
        print n,"Last Git Modified: ", modifiedTime, " - ", filePath
        os.popen(command % (last_year,year,filePath))
        n = n + 1


>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3

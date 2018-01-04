@echo off

set /p msg=Input Message:

git pull

git checkout test

git add .

git commit -m "%msg%"

git push -u origin test

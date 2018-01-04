@echo off

set /p message= 输入提交注释:

git pull

git checkout test

git add .

git commit -m %message%

git push -u origin test


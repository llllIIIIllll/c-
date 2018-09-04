@echo off

<<<<<<< HEAD
set /p message= 输入提交注释:
=======
set /p msg=Input Message:
>>>>>>> origin/test

git pull

git checkout test

git add .

<<<<<<< HEAD
git commit -m "%message%"

git push -u origin test

=======
git commit -m "%msg%"

git push -u origin test
>>>>>>> origin/test

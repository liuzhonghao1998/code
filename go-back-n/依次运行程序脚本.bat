@echo off
echo wscript.sleep 1800000 >run.vbs
:: ����1800000����
::����str���򣬺����ǲ���
:name
cls
echo.���������������(ͬһ�ļ�����)
set /p str=
if exist %str% goto menu
::if exist %str%.exe goto menu
goto name
:menu
echo au ������...
start %str% au -log 1a.txt
start %str% bu -log 1b.txt
run.vbs
::�ر� str����
taskkill /f /im %str%
echo a ������...
start %str% a -log 2a.txt
start %str% b -log 2b.txt
run.vbs
::�ر� str����
taskkill /f /im %str%
echo afu ������...
start %str% afu -log 3a.txt
start %str% bfu -log 3b.txt
run.vbs
::�ر� str����
taskkill /f /im %str%
echo af ������...
start %str% af -log 4a.txt
start %str% bf -log 4b.txt
run.vbs
::�ر� str����
taskkill /f /im %str%
echo af -ber 1e-4 ������...
start %str% af -ber 1e-4 -log 5a.txt
start %str% bf -ber 1e-4 -log 5b.txt
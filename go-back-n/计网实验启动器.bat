@echo off
title ����ʵ��������
mode con cols=47 lines=20
color f5
set dbg=""
set port1=23333
set port2=23334
set port3=23335
set port4=23336
set port5=23337
:name
cls
echo.���������������(ͬһ�ļ�����)
set /p str=
if exist %str% goto menu
if exist %str%.exe goto menu
goto name
:menu
cls
echo.                ����ʵ��������
echo.**********************************************
echo 1  ������������
echo.
echo 2  ����ȫ��������
echo.
echo 3  �޸ļ���������  ^<��ǰΪ%str%^>
echo.
echo 4  debugѡ��
echo.
echo 5  �޸Ķ˿�
echo.
echo 6  �˳�
echo                                  by:Lanvent
echo.**********************************************
echo.������ѡ����Ŀ�����:
set /p  ID=
if "%id%"=="1" goto cmd1
if "%id%"=="2" goto cmd2
if "%id%"=="3" goto cmd3
if "%id%"=="4" goto cmd4
if "%id%"=="5" goto cmd5
if "%id%"=="6" exit
echo ��������
PAUSE
goto menu
:cmd1
cls
echo 1  a:IDLE b:Flood 0e0
echo.
echo 2  a:IDLE b:Flood 1e-5
echo.
echo 3  a:Flood b:Flood 0e0
echo.
echo 4  a:Flood b:Flood 1e-5
echo.
echo 5  a:Flood b:Flood 1e-4
echo.
echo.6  �������˵�
echo.*********************
echo.���������:
set /p  ID=
if "%id%"=="1"  start %str% au%dbg% -port %port1% -log 1a.txt&start %str% bu%dbg% -port %port1% -log 1b.txt
if "%id%"=="2" 	start %str% a%dbg% -port %port2% -log 2a.txt&start %str% b%dbg% -port %port2% -log 2b.txt
if "%id%"=="3"  start %str% afu%dbg% -port %port3% -log 3a.txt&start %str% bfu%dbg% -port %port3% -log 3b.txt
if "%id%"=="4"  start %str% af%dbg% -port %port4% -log 4a.txt&start %str% bf%dbg% -port %port4% -log 4b.txt
if "%id%"=="5"  start %str% af%dbg% -ber 1e-4 -port %port5% -log 5a.txt&start %str% bf%dbg% -ber 1e-4 -port %port5% -log 5b.txt
if "%id%"=="6"  goto menu
echo ��������
goto cmd1
:cmd2
start %str% au%dbg% -port %port1% -log 1a.txt
start %str% bu%dbg% -port %port1% -log 1b.txt
start %str% a%dbg% -port %port2% -log 2a.txt
start %str% b%dbg% -port %port2% -log 2b.txt
start %str% afu%dbg% -port %port3% -log 3a.txt
start %str% bfu%dbg% -port %port3% -log 3b.txt
start %str% af%dbg% -port %port4% -log 4a.txt
start %str% bf%dbg% -port %port4% -log 4b.txt
start %str% af%dbg% -ber 1e-4 -port %port5% -log 5a.txt
start %str% bf%dbg% -ber 1e-4 -port %port5% -log 5b.txt
goto menu
:cmd3
goto name

:cmd4
cls
set /a tmp=%dbg%+1
echo ��ǰ����Ϊ [%tmp%]
echo 1  �ر�debug
echo.
echo 2  ֻ����dbg_event
echo.
echo 3  ֻ����dbg_frame
echo.
echo 4  debug��Ϣȫ������
echo.
echo 5  �������˵�
echo.
echo.*********************
echo.���������:
set /p  ID=
if "%id%"=="1"  set dbg=""
if "%id%"=="2" 	set dbg=1
if "%id%"=="3"  set dbg=2
if "%id%"=="4"  set dbg=3
if "%id%"=="5"  goto menu
goto cmd4
:cmd5
cls
echo 1  �޸Ķ˿�1 ^<��ǰ:%port1%^>
echo 2  �޸Ķ˿�2 ^<��ǰ:%port2%^>
echo 3  �޸Ķ˿�3 ^<��ǰ:%port3%^>
echo 4  �޸Ķ˿�4 ^<��ǰ:%port4%^>
echo 5  �޸Ķ˿�5 ^<��ǰ:%port5%^>
echo 6  �������˵�
echo.��������ţ�
set /p  ID=
if "%id%"=="1"  set /p port1=������˿ں�(������65535):
if "%id%"=="2" 	set /p port2=������˿ں�(������65535):
if "%id%"=="3"  set /p port3=������˿ں�(������65535):
if "%id%"=="4"  set /p port4=������˿ں�(������65535):
if "%id%"=="5"  set /p port5=������˿ں�(������65535):
if "%id%"=="6"  goto menu
goto cmd5
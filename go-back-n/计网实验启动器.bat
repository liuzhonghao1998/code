@echo off
title 计网实验启动器
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
echo.请输入计网程序名(同一文件夹内)
set /p str=
if exist %str% goto menu
if exist %str%.exe goto menu
goto name
:menu
cls
echo.                计网实验启动器
echo.**********************************************
echo 1  单个命令启动
echo.
echo 2  验收全命令启动
echo.
echo 3  修改计网程序名  ^<当前为%str%^>
echo.
echo 4  debug选项
echo.
echo 5  修改端口
echo.
echo 6  退出
echo                                  by:Lanvent
echo.**********************************************
echo.请输入选择项目的序号:
set /p  ID=
if "%id%"=="1" goto cmd1
if "%id%"=="2" goto cmd2
if "%id%"=="3" goto cmd3
if "%id%"=="4" goto cmd4
if "%id%"=="5" goto cmd5
if "%id%"=="6" exit
echo 输入有误
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
echo.6  返回主菜单
echo.*********************
echo.请输入序号:
set /p  ID=
if "%id%"=="1"  start %str% au%dbg% -port %port1% -log 1a.txt&start %str% bu%dbg% -port %port1% -log 1b.txt
if "%id%"=="2" 	start %str% a%dbg% -port %port2% -log 2a.txt&start %str% b%dbg% -port %port2% -log 2b.txt
if "%id%"=="3"  start %str% afu%dbg% -port %port3% -log 3a.txt&start %str% bfu%dbg% -port %port3% -log 3b.txt
if "%id%"=="4"  start %str% af%dbg% -port %port4% -log 4a.txt&start %str% bf%dbg% -port %port4% -log 4b.txt
if "%id%"=="5"  start %str% af%dbg% -ber 1e-4 -port %port5% -log 5a.txt&start %str% bf%dbg% -ber 1e-4 -port %port5% -log 5b.txt
if "%id%"=="6"  goto menu
echo 输入有误
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
echo 当前设置为 [%tmp%]
echo 1  关闭debug
echo.
echo 2  只开启dbg_event
echo.
echo 3  只开启dbg_frame
echo.
echo 4  debug信息全部开启
echo.
echo 5  返回主菜单
echo.
echo.*********************
echo.请输入序号:
set /p  ID=
if "%id%"=="1"  set dbg=""
if "%id%"=="2" 	set dbg=1
if "%id%"=="3"  set dbg=2
if "%id%"=="4"  set dbg=3
if "%id%"=="5"  goto menu
goto cmd4
:cmd5
cls
echo 1  修改端口1 ^<当前:%port1%^>
echo 2  修改端口2 ^<当前:%port2%^>
echo 3  修改端口3 ^<当前:%port3%^>
echo 4  修改端口4 ^<当前:%port4%^>
echo 5  修改端口5 ^<当前:%port5%^>
echo 6  返回主菜单
echo.请输入序号：
set /p  ID=
if "%id%"=="1"  set /p port1=请输入端口号(不超过65535):
if "%id%"=="2" 	set /p port2=请输入端口号(不超过65535):
if "%id%"=="3"  set /p port3=请输入端口号(不超过65535):
if "%id%"=="4"  set /p port4=请输入端口号(不超过65535):
if "%id%"=="5"  set /p port5=请输入端口号(不超过65535):
if "%id%"=="6"  goto menu
goto cmd5
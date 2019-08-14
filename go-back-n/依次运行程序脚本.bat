@echo off
echo wscript.sleep 1800000 >run.vbs
:: 运行1800000毫秒
::运行str程序，后面是参数
:name
cls
echo.请输入计网程序名(同一文件夹内)
set /p str=
if exist %str% goto menu
::if exist %str%.exe goto menu
goto name
:menu
echo au 运行中...
start %str% au -log 1a.txt
start %str% bu -log 1b.txt
run.vbs
::关闭 str程序
taskkill /f /im %str%
echo a 运行中...
start %str% a -log 2a.txt
start %str% b -log 2b.txt
run.vbs
::关闭 str程序
taskkill /f /im %str%
echo afu 运行中...
start %str% afu -log 3a.txt
start %str% bfu -log 3b.txt
run.vbs
::关闭 str程序
taskkill /f /im %str%
echo af 运行中...
start %str% af -log 4a.txt
start %str% bf -log 4b.txt
run.vbs
::关闭 str程序
taskkill /f /im %str%
echo af -ber 1e-4 运行中...
start %str% af -ber 1e-4 -log 5a.txt
start %str% bf -ber 1e-4 -log 5b.txt
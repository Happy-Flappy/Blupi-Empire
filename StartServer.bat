@echo off
SET "configFile=Settings.txt"
echo fullscreen = false > "%configFile%"
echo width = 480 >> "%configFile%"
echo height = 540 >> "%configFile%"
echo server = true >> "%configFile%"

start "" "Blupi Empire.exe"
exit
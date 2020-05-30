@echo off
date /T > d:\log
time /t >> d:\log
c:\usr\bin\snmpget -v 2c -c public localhost ifOutOctets.2 >> d:\log
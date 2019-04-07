#!/bin/sh
set -v on
cd /root/wang
rm -rf upload.bat.log
make clean >> ./upload.bat.log
make >> ./upload.bat.log
echo "">> ./upload.bat.log
echo "===result===" >> ./upload.bat.log
./test >> ./upload.bat.log
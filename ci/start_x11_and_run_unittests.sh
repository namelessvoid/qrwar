Xorg -noreset +extension GLX +extension RANDR +extension RENDER -logfile /qrw/xdummy.log -config /qrw/ci/xorg.conf :1 &
sleep 5
DISPLAY=:1 ./bin/unittest
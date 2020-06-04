    1  cd janus/
    4  cd janus-gateway-0.8.0/
    9  ./configure --prefix=/home/panpan/janus/janus-gateway-0.8.0/janus --disable-websockets --disable-data-channels --disable-rabbitmq --disable-mqtt
   10  ./configure --prefix=/home/panpan/janus/janus-gateway-0.8.0/janus-test1 --disable-websockets --disable-data-channels --disable-rabbitmq --disable-mqtt
   16  vi janus-test1/etc/janus/janus.jcfg
   17  vi janus-test1/etc/janus/janus.transport.http.jcfg
   43  cd janus-gateway-0.8.0/
   44  vi janus-test1/etc/janus/janus.jcfg
   45  vi janus-test1/etc/janus/janus.transport.http.jcfg
   46  vi janus-test1/etc/janus/janus.jcfg
   47  ./janus-test1/bin/janus -C /home/panpan/janus/janus-gateway-0.8.0/janus-test1/etc/janus/janus.jcfg -d 7 
   48  vi  /home/panpan/janus/janus-gateway-0.8.0/janus-test1/etc/janus/janus.transport.http.jcfg
   49  ./janus-test1/bin/janus -C /home/panpan/janus/janus-gateway-0.8.0/janus-test1/etc/janus/janus.jcfg -d 7 
   50  sudo ./janus-test1/bin/janus -C /home/panpan/janus/janus-gateway-0.8.0/janus-test1/etc/janus/janus.jcfg -d 7 
   51  vi  /home/panpan/janus/janus-gateway-0.8.0/janus-test1/etc/janus/janus.transport.http.jcfg
   52  vi  /home/panpan/janus/janus-gateway-0.8.0/janus-test1/etc/janus/janus.jcfg
   53  sudo ./janus-test1/bin/janus -C /home/panpan/janus/janus-gateway-0.8.0/janus-test1/etc/janus/janus.jcfg -d 7 
   55  ps -aux|grep janus
   56  vi janus-test1/etc/janus/janus.jcfg
   57  vi janus-test1/etc/janus/janus.transport.http.jcfg
   58  ls /home/panpan/janus/cert/cert.pem
   59  ls /home/panpan/janus/cert/key.pem
   61  ./configure --prefix=/home/panpan/janus/janus-gateway-0.8.0/janus-test1 --disable-websockets --disable-data-channels --disable-rabbitmq --disable-mqtt
   64  sudo ./janus-test1/bin/janus -C /home/panpan/janus/janus-gateway-0.8.0/janus-test1/etc/janus/janus.jcfg -d 7 
   66  sudo ./janus-test1/bin/janus -C /home/panpan/janus/janus-gateway-0.8.0/janus-test1/etc/janus/janus.jcfg -d 7 
   67  vi janus-test1/etc/janus/janus.transport.http.jcfg
   68  vi janus-test1/etc/janus/janus.jcfg
   69  sudo ./janus-test1/bin/janus -C /home/panpan/janus/janus-gateway-0.8.0/janus-test1/etc/janus/janus.jcfg -d 7 
   70  sudo ./janus-test1/bin/janus -C /home/panpan/janus/janus-gateway-0.8.0/janus-test1/etc/janus/janus.jcfg 
   71  mkdir janus
   72  cd janus/
   96  git clone https://github.com/meetecho/janus-gateway.git
   98  vi janus/janus-gateway-0.8.0/janus-test1/etc/janus/janus.transport.http.jcfg
  103  ls /home/panpan/janus/janus-gateway/janus-test1/share/janus/demos
  121  cd janus/janus-gateway-0.8.0/
  124  history |grep janus
  125  sudo ./janus-test1/bin/janus -C /home/panpan/janus/janus-gateway-0.8.0/janus-test1/etc/janus/janus.jcfg 
  127  cd janus/janus-gateway-0.8.0/
  129  find . -name "janus_api*"
  133  cd janus/janus-gateway-0.8.0/
  138  cd janus/janus-gateway-0.8.0/
  142  history |grep janus
  143  history |grep janus > start.sh

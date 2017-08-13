================build and install========================
- linux platform:
  - install libevent 2.0.22 dependency
    - 1>. dowload libevent 2.0.22
      - https://github.com/libevent/libevent/releases/download/release-2.0.22-stable/libevent-2.0.22-stable.tar.gz
    - 2>. build and install libevent
      - ./configure
      - make
      - make install 
  - install JsonCPP 0.7.0 dependency
    - https://github.com/open-source-parsers/jsoncpp/archive/0.7.0.zip

  - install boost 1.56.0 dependency
    - 1>. dowload boost 1.56.0
      - http://www.boost.org/users/history/version_1_56_0.html
    - 2>. deflate boost 1.56.0
      - tar --bzip2 -xf /path/to/boost_1_56_0.tar.bz2
    - 3>. build and install boost 1.56.0
      - <1>. cd path/to/boost_1_56_0
      - <2>. config boost：./bootstrap.sh
      - <3>. build boost: 
      
		    - build static boost lib: ./b2 link=static runtime-link=static
		    - build dynamic boost lib: ./b2 link=shared runtime-link=shared
      - <4>. install boost: ./b2 install
  - modify pathOfJsonCPP, pathOfBoost and pathOfLibEvent in project/Makefile and example/Makefile, according to its real install path    
  - make
  - make install
    - default install path:
    	- header files: /usr/local/include
    	- lib: /usr/local/lib
  
- Windows platform:
  - will be supported later

- Mac
  - `brew install jsoncpp`


- check verion:
  - strings librocketmq.so |grep VERSION

- log path:$HOME/logs/metaq-client4cpp

- Before Run:
  - export LD_LIBRARY_PATH=/xxx/rocketmq-client4cpp/bin/:$LD_LIBRARY_PATH;LD_LIBRARY_PATH=/A/lib:$LD_LIBRARY_PATH

=================meaning of each parameter===================
- -n	: nameserver addr, if not set -n and -i ,no nameSrv will be got
- -i	: nameserver domain name,  if not set -n and -i ,no nameSrv will be got
- Notice: oper should only set one option from -n and -i, 
- -g	: groupName, contains producer groupName and consumer groupName
- -t	: msg topic
- -m	: message count(default value:1)
- -c 	: msg content(default value: only test)
- -b	: consume model(default value: CLUSTER)
- -a	: set sync push(default value: async)
- -r	: setup retry times(default value:5 times)
- -u	: select active broker to send msg(default value: false)
- -d	: use AutoDeleteSendcallback by cpp client(defalut value: false)
- -T	: thread count of send msg or consume msg(defalut value: system cpu core number)
- -v 	: print more details information

- Example:
  - sync producer: ./SyncProducer -g producerGroup -t topic -c msgContent -m msgCount -n nameServerAddr
  - async producer: ./AsyncProducer  -g producerGroup -t topic -c msgContent -m msgCount -n nameServerAddr 
  - send delay msg: ./SendDelayMsg  -g producerGroup -t topic -c msgContent -n nameServerAddr
  - sync pushConsumer: ./PushConsumer  -g producerGroup -t topic -c msgContent -m msgCount -n nameServerAddr -s sync
  - async pushConsumer: ./AsyncPushConsumer  -g producerGroup -t topic -c msgContent -m msgCount -n nameServerAddr
  - orderly sync pushConsumer:  ./OrderlyPushConsumer -g producerGroup -t topic -c msgContent -m msgCount -n nameServerAddr -s sync
  - orderly async pushConsumer: ./OrderlyPushConsumer -g producerGroup -t topic -c msgContent -m msgCount -n nameServerAddr
  - sync pullConsumer:./PullConsumer  -g producerGroup -t topic -c msgContent -m msgCount -n nameServerAddr 

==================================Notice=============================================
- producer must invoke following interface:
  - DefaultMQProducer g_producer("please_rename_unique_group_name");
  - g_producer.start();
  - g_producer.send(...);
  - g_producer.shutdown();

- pullconsumer must invoke following interface:
  - DefaultMQPullConsumer     g_consumer("please_rename_unique_group_name");
  - g_consumer.start();
  - g_consumer.fetchSubscribeMessageQueues(..., ...);
  - g_consumer.pull(...)
  - g_consumer.shutdown();

- pushconsumer must invoke following interface:
  - DefaultMQPushConsumer g_consumer("please_rename_unique_group_name_1");
  - g_consumer.subscribe("test_topic", "*");
  - g_consumer.registerMessageListener(listener);
  - g_consumer.start();
  - g_consumer.shutdown();

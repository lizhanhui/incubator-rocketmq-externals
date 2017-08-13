cmake_minimum_required(VERSION 3.8)
project(rocketmq_cpp)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}}/cmake)

set(SOURCE_FILES
        src/common/AsyncCallbackWrap.cpp
        src/common/Arg_helper.cpp
        src/common/ClientRPCHook.cpp
        src/common/dataBlock.cpp
        src/common/InputStream.cpp
        src/common/MemoryInputStream.cpp
        src/common/MemoryOutputStream.cpp
        src/common/MessageSysFlag.cpp
        src/common/MQClient.cpp
        src/common/MQVersion.cpp
        src/common/OutputStream.cpp
        src/common/PermName.cpp
        src/common/PullSysFlag.cpp
        src/common/sync_http_client.cpp
        src/common/TopAddressing.cpp
        src/common/TopicConfig.cpp
        src/common/url.cpp
        src/common/UtilAll.cpp
        src/common/Validators.cpp
        src/common/VirtualEnvUtil.cpp
        src/consumer/ConsumeMessageConcurrentlyService.cpp
        src/consumer/ConsumeMessageOrderlyService.cpp
        src/consumer/DefaultMQPullConsumer.cpp
        src/consumer/DefaultMQPushConsumer.cpp
        src/consumer/OffsetStore.cpp
        src/consumer/PullAPIWrapper.cpp
        src/consumer/PullRequest.cpp
        src/consumer/PullResult.cpp
        src/consumer/Rebalance.cpp
        src/consumer/SubscriptionData.cpp
        src/log/Logging.cpp
        src/message/MQDecoder.cpp
        src/message/MQMessage.cpp
        src/message/MQMessageExt.cpp
        src/message/MQMessageQueue.cpp
        src/producer/DefaultMQProducer.cpp
        src/producer/SendResult.cpp
        src/protocol/CommandHeader.cpp
        src/protocol/ConsumerRunningInfo.cpp
        src/protocol/LockBatchBody.cpp
        src/protocol/MessageQueue.cpp
        src/protocol/RemotingCommand.cpp
        src/thread/task_queue.cpp
        src/transport/ClientRemotingProcessor.cpp
        src/transport/ResponseFuture.cpp
        src/transport/SocketUtil.cpp
        src/transport/TcpRemotingClient.cpp
        src/transport/TcpTransport.cpp
        src/MQClientAPIImpl.cpp
        src/MQClientFactory.cpp
        src/MQClientManager.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src/include)
include_directories(${PROJECT_SOURCE_DIR}/libs/alog/include)
include_directories(${PROJECT_SOURCE_DIR}/libs/signature/include)
include_directories(${PROJECT_SOURCE_DIR}/src/thread/disruptor)

find_package(Boost REQUIRED)

IF(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
ELSE()
    message("Required boost library is not installed")
ENDIF()

find_package(Jsoncpp REQUIRED)
IF(Jsoncpp_FOUND)
    INCLUDE_DIRECTORIES(${Jsoncpp_INCLUDE_DIR})
ENDIF()

add_subdirectory(${PROJECT_SOURCE_DIR}/libs/signature/src)

ADD_LIBRARY(rocketmq ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(rocketmq ${Boost_LIBRARIES} ${Jsoncpp_LIBRARY} signature)
/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "Logging.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include "Appender.h"
#include "Configurator.h"
#include "UtilAll.h"
#define BOOST_DATE_TIME_SOURCE

namespace metaq {

ALogAdapter::~ALogAdapter() {
  if (alogger_ != NULL) {
    alogger_->flush();
  }
  alog::Logger::shutdown();
  alogger_ = NULL;
}

ALogAdapter& ALogAdapter::getLogInstance() {
  static ALogAdapter alogInstance;
  return alogInstance;
}

ALogAdapter::ALogAdapter() : alogger_(0), m_logLevel(eLOG_LEVEL_INFO) {
  string homeDir(UtilAll::getHomeDirectory());
  homeDir.append("/logs/metaq-client4cpp/");
  m_logFile += homeDir;
  std::string strTime =
      boost::gregorian::to_iso_string(boost::gregorian::day_clock::local_day());
  std::string fileName = UtilAll::to_string(getpid()) + "_" + "metaq-cpp.log";
  m_logFile += fileName;

  alogger_ = alog::Logger::getLogger("metaq-cpp", false);
  alogger_->setLevel(alog::LOG_LEVEL_INFO);
  alog::FileAppender* appender = dynamic_cast<alog::FileAppender*>(
      alog::FileAppender::getAppender(m_logFile.c_str()));
  if (appender) {
    appender->setHistoryLogKeepCount(2);
    appender->setMaxSize(100);   // MB
    appender->setCacheLimit(8);  // MB
    alog::PatternLayout* layout = new alog::PatternLayout;
    layout->setLogPattern("[%%d] [%%p:%%t] [%%l] %%m [%%f()[%%n]]");
    appender->setLayout(layout);
    alogger_->setAppender(appender);
    printf("alog init ok,file:%s\n", m_logFile.c_str());
  }
}

void ALogAdapter::setLogLevel(elogLevel logLevel) {
  switch (logLevel) {
    case eLOG_LEVEL_DISABLE:
      alogger_->setLevel(alog::LOG_LEVEL_DISABLE);
      break;
    case eLOG_LEVEL_FATAL:
      alogger_->setLevel(alog::LOG_LEVEL_FATAL);
      break;
    case eLOG_LEVEL_ERROR:
      alogger_->setLevel(alog::LOG_LEVEL_ERROR);
      break;
    case eLOG_LEVEL_WARN:
      alogger_->setLevel(alog::LOG_LEVEL_WARN);
      break;
    case eLOG_LEVEL_INFO:
      alogger_->setLevel(alog::LOG_LEVEL_INFO);
      break;
    case eLOG_LEVEL_DEBUG:
      alogger_->setLevel(alog::LOG_LEVEL_DEBUG);
      break;
    case eLOG_LEVEL_TRACE:
      alogger_->setLevel(alog::LOG_LEVEL_TRACE1);
      break;
    default:
      alogger_->setLevel(alog::LOG_LEVEL_INFO);
      break;
  }
}

elogLevel ALogAdapter::getLogLevel() { return m_logLevel; }

void ALogAdapter::setLogFileNumAndSize(int logNum, int sizeOfPerFile) {
  alog::FileAppender* appender = dynamic_cast<alog::FileAppender*>(
      alog::FileAppender::getAppender(m_logFile.c_str()));
  if (appender) {
    appender->setHistoryLogKeepCount(logNum - 1);
    appender->setMaxSize(sizeOfPerFile);  // MB
  }
}
}

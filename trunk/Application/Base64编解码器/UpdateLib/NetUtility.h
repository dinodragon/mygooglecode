#ifndef __NETUNITUS_H_
#define __NETUNITUS_H_
#pragma once

#include <string>

bool WaitDownload(const std::string& url, std::string& output, int timeout = 0);

#endif
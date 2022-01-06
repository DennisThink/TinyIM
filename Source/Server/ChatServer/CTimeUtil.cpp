#include "CTimeUtil.h"
#include <time.h>
std::string CTimeUtil::GetYMD_HMS_Time() {
	time_t nowTime = time(nullptr);
	struct tm nowTm;
    struct tm* pTime = localtime(&nowTime);
	nowTm = *pTime;
	char buff[32] = { 0 };
	sprintf(buff, "%04d-%02d-%02d %02d:%02d:%02d ",
		nowTm.tm_year + 1900,
		nowTm.tm_mon + 1,
		nowTm.tm_mday,
		nowTm.tm_hour,
		nowTm.tm_min,
		nowTm.tm_sec);
	return buff;
}
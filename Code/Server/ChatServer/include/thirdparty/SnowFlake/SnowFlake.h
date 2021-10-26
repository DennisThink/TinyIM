#include <stdint.h>
#ifndef _WIN32
#include <sys/time.h>
#else
#include <time.h>
#include <windows.h>
static int gettimeofday(struct timeval *tp, void *tzp)
{
	time_t clock;
	struct tm tm;
	SYSTEMTIME wtm;
	GetLocalTime(&wtm);
	tm.tm_year = wtm.wYear - 1900;
	tm.tm_mon = wtm.wMonth - 1;
	tm.tm_mday = wtm.wDay;
	tm.tm_hour = wtm.wHour;
	tm.tm_min = wtm.wMinute;
	tm.tm_sec = wtm.wSecond;
	tm.tm_isdst = -1;
	clock = mktime(&tm);
	tp->tv_sec = static_cast<long>(clock);
	tp->tv_usec = wtm.wMilliseconds * 1000;
	return (0);
}
//-------------------- -
//作者：君盼云淡风清/
//来源：CSDN
//原文：https ://blog.csdn.net/zhudinglym/article/details/71683400 
//版权声明：本文为博主原创文章，转载请附上博文链接！
#endif
#include <stdexcept>
#include <mutex>
//#include "utils/lightlog.h"

class SnowFlake {
private:
    static const uint64_t start_stmp_ = 1480166465631;
    static const uint64_t sequence_bit_ = 12;
    static const uint64_t machine_bit_ = 5;
    static const uint64_t datacenter_bit_ = 5;

    static const uint64_t max_datacenter_num_ = -1 ^ (uint64_t(-1) << datacenter_bit_);
    static const uint64_t max_machine_num_ = -1 ^ (uint64_t(-1) << machine_bit_);
    static const uint64_t max_sequence_num_ = -1 ^ (uint64_t(-1) << sequence_bit_);

    static const uint64_t machine_left = sequence_bit_;
    static const uint64_t datacenter_left = sequence_bit_ + machine_bit_;
    static const uint64_t timestmp_left = sequence_bit_ + machine_bit_ + datacenter_bit_;

    uint64_t datacenterId;
    uint64_t machineId;
    uint64_t sequence;
    uint64_t lastStmp;

    std::mutex mutex_;

    uint64_t getNextMill() {
        uint64_t mill = getNewstmp();
        while (mill <= lastStmp) {
            mill = getNewstmp();
        }
        return mill;
    }

    uint64_t getNewstmp() {
        struct timeval tv;
        gettimeofday(&tv, NULL);

        uint64_t time = tv.tv_usec;
        time /= 1000;
        time += (tv.tv_sec * 1000);
        return time;
    }

public:
    SnowFlake(int datacenter_Id, int machine_Id) {
        if ((uint64_t)datacenter_Id > max_datacenter_num_ || datacenter_Id < 0) {
           // LLOG(ERRO) << "datacenterId can't be greater than max_datacenter_num_ or less than 0";
            exit(0);
        }
        if ((uint64_t)machine_Id > max_machine_num_ || machine_Id < 0) {
           // LLOG(ERRO) << "machineId can't be greater than max_machine_num_or less than 0";
            exit(0);
        }
        datacenterId = datacenter_Id;
        machineId = machine_Id;
        sequence = 0L;
        lastStmp = 0L;
    }

    uint64_t nextId() {
        std::unique_lock<std::mutex> lock(mutex_);
        uint64_t currStmp = getNewstmp();
        if (currStmp < lastStmp) {
           // LLOG(ERRO) << "Clock moved backwards.  Refusing to generate id";
            exit(0);
        }

        if (currStmp == lastStmp) {
            sequence = (sequence + 1) & max_sequence_num_;
            if (sequence == 0) {
                currStmp = getNextMill();
            }
        } else {
            sequence = 0;
        }
        lastStmp = currStmp;
        return (currStmp - start_stmp_) << timestmp_left
                | datacenterId << datacenter_left
                | machineId << machine_left
                | sequence;
    }

};

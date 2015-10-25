/* 
 * File:   TimeTest.hh
 * Author: fys
 *
 * Created on October 24, 2015, 6:13 PM
 */

#ifndef TIMETEST_HH
#define	TIMETEST_HH

#include <ctime>                                                                                                                                                                                                    

class Timer
{
public:
  Timer() { clock_gettime(CLOCK_REALTIME, &beg_); }

  double elapsed() {
    clock_gettime(CLOCK_REALTIME, &end_);
        return end_.tv_sec - beg_.tv_sec +
          (end_.tv_nsec - beg_.tv_nsec) / 1000000000.;
  }

  void reset() { clock_gettime(CLOCK_REALTIME, &beg_); }

private:
  timespec beg_, end_;
};

#endif	/* TIMETEST_HH */


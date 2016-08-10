#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <sstream>
#include <regex>
#include <datetime.hpp>
#include <utils.hpp>

const short DateTime::local_utcOffset_from_standard_time_as_hhmm=-700;
const size_t DateTime::days_in_month[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};

void DateTime::add(std::string units,size_t numToAdd,std::string calendar)
{
  units=strutils::to_lower(units);
  if (units == "hours") {
    addHours(numToAdd,calendar);
  }
  else if (units == "days") {
    addDays(numToAdd,calendar);
  }
  else if (units == "months") {
    addMonths(numToAdd,calendar);
  }
  else if (units == "years") {
    addYears(numToAdd);
  }
  else if (units == "minutes") {
    addMinutes(numToAdd,calendar);
  }
  else if (units == "seconds") {
    addSeconds(numToAdd,calendar);
  }
  else {
    std::cerr << "Error: units " << units << " not recognized" << std::endl;
    exit(1);
  }
}

void DateTime::addDays(size_t daysToAdd,std::string calendar)
{
  size_t days[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
  size_t newdy;

  if (calendar.length() == 0 || calendar != "noleap") {
    if (isLeapYear(yr))
	days[2]=29;
  }
  newdy=dy+daysToAdd;
  while (newdy > days[mo]) {
    newdy-=days[mo];
    mo++;
    if (mo > 12) {
	yr++;
	if (calendar.length() == 0 || calendar != "noleap")
	  days[2]= (isLeapYear(yr)) ? 29 : 28;
	mo=1;
    }
  }
  dy=newdy;
  if (wkdy >= 0) {
    wkdy=(wkdy+daysToAdd) % 7;
  }
}

void DateTime::addHours(size_t hoursToAdd,std::string calendar)
{
  size_t hh,dd;

  dd=hoursToAdd/24;
  hh=hoursToAdd % 24;
  hr+=hh;
  if (hr > 23) {
    hr-=24;
    dd++;
  }
  addDays(dd,calendar);
}

void DateTime::addMinutes(size_t minutesToAdd,std::string calendar)
{
  size_t hh,mm;

  hh=minutesToAdd/60;
  mm=minutesToAdd % 60;
  min+=mm;
  if (min > 59) {
    min-=60;
    hh++;
  }
  addHours(hh,calendar);
}

void DateTime::addMonths(size_t monthsToAdd,std::string calendar)
{
  size_t days[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
  size_t n;

  for (n=0; n < monthsToAdd; n++) {
    days[2]= (isLeapYear(yr)) ? 29 : 28;
    addDays(days[mo],calendar);
  }
}

void DateTime::addSeconds(size_t secondsToAdd,std::string calendar)
{
  size_t mm,ss;

  mm=secondsToAdd/60;
  ss=secondsToAdd % 60;
  sec+=ss;
  if (sec > 59) {
    sec-=60;
    mm++;
  }
  addMinutes(mm,calendar);
}

void DateTime::addTime(size_t hhmmss,std::string calendar)
{
  size_t hh,mm,ss;

  hh=hhmmss/10000;
  mm=hhmmss % 10000;
  ss=mm % 100;
  if (ss > 59) {
    std::cerr << "Error: bad value " << hhmmss << " for hhmmss" << std::endl;
    exit(1);
  }
  mm/=100;
  if (mm > 59) {
    std::cerr << "Error: bad value " << hhmmss << " for hhmmss" << std::endl;
    exit(1);
  }
  addSeconds(ss,calendar);
  addMinutes(mm,calendar);
  addHours(hh,calendar);
}

void DateTime::addYears(size_t yearsToAdd)
{

  yr+=yearsToAdd;
}

DateTime DateTime::added(std::string units,size_t numToAdd,std::string calendar) const
{
  DateTime new_dt=*this;

  new_dt.add(units,numToAdd,calendar);
  return new_dt;
}

DateTime DateTime::daysAdded(size_t daysToAdd,std::string calendar) const
{
  DateTime new_dt=*this;

  new_dt.addDays(daysToAdd,calendar);
  return new_dt;
}

DateTime DateTime::daysSubtracted(size_t daysToSubtract) const
{
  DateTime new_dt=*this;

  new_dt.subtractDays(daysToSubtract);
  return new_dt;
}

int DateTime::getDaysSince(const DateTime& reference,std::string calendar) const
{
  size_t num_days[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
  if (*this < reference) {
    return -1;
  }
  if (*this == reference) {
    return 0;
  }
  auto days=365*this->getYearsSince(reference);
  if (calendar.length() == 0 || calendar != "noleap") {
    if (days > 0 && isLeapYear(reference.yr) && reference.mo <= 2) {
	++days;
    }
    for (short n=reference.yr+1; n < this->yr; ++n) {
	if (isLeapYear(n)) {
	  ++days;
	}
    }
    if (isLeapYear(this->yr) && this->mo > 2) {
	++days;
    }
  }
  days+=(this->dy-reference.dy);
  if (this->getMonthsSince(reference) > 0) {
    if (this->mo < reference.mo || (this->mo == reference.mo && (this->dy < reference.dy || (this->dy == reference.dy && this->getTime() < reference.getTime())))) {
	for (short n=reference.mo; n <= 12; ++n) {
	  days+=num_days[n];
	}
	for (short n=1; n < this->mo; ++n) {
	  days+=num_days[n];
	}
    }
    else {
	for (short n=reference.mo; n < this->mo; ++n) {
	  days+=num_days[n];
	}
    }
  }
  else if (this->dy < reference.dy || (days == 0 && this->mo != reference.mo)) {
    days+=num_days[reference.mo];
  }
  if (this->getTime() < reference.getTime()) {
    --days;
  }
  return days;
}

int DateTime::getHoursSince(const DateTime& reference,std::string calendar) const
{
  int hours;

  if (*this < reference) {
    return -1;
  }
  if (*this == reference) {
    return 0;
  }
  hours=24*this->getDaysSince(reference,calendar);
  hours+=(this->hr-reference.hr);
  if (this->hr < reference.hr || (this->hr == reference.hr && this->getTime() < reference.getTime())) {
    hours+=24;
  }
  if (this->min < reference.min || (this->min == reference.min && this->sec < reference.sec)) {
    --hours;
  }
  return hours;
}

int DateTime::getMinutesSince(const DateTime& reference,std::string calendar) const
{
  int minutes;

  if (*this < reference)
    return -1;
  minutes=60*this->getHoursSince(reference,calendar);
  minutes+=(this->min-reference.min);
  if (this->min < reference.min || (this->min == reference.min && this->sec < reference.sec))
    minutes+=60;
  if (this->sec < reference.sec)
    minutes--;
  return minutes;
}

int DateTime::getMonthsSince(const DateTime& reference) const
{
  int months;

  if (*this < reference)
    return -1;
  months=12*this->getYearsSince(reference);
  months+=(this->mo-reference.mo);
  if (this->mo < reference.mo || (this->mo == reference.mo && (this->dy < reference.dy || (this->dy == reference.dy && this->getTime() < reference.getTime()))))
    months+=12;
  if (this->dy < reference.dy || (this->dy == reference.dy && this->getTime() < reference.getTime()))
    months--;
  return months;
}

long long DateTime::getSecondsSince(const DateTime& reference,std::string calendar) const
{
  long long seconds;

  if (*this < reference)
    return -1;
  seconds=60*static_cast<long long>(this->getMinutesSince(reference,calendar));
  seconds+=(this->sec-reference.sec);
  if (this->sec < reference.sec)
    seconds+=60;
  return seconds;
}

int DateTime::getTimeSince(const DateTime& reference,std::string calendar) const
{
  int hhmmss;
  size_t hh,mm,ss;

  if (*this < reference)
    return -1;
  hh=this->getHoursSince(reference,calendar);
  mm=this->getMinutesSince(reference,calendar) % 60;
  ss=this->getSecondsSince(reference,calendar) % 60;
  hhmmss=hh*10000+mm*100+ss;
  return hhmmss;
}

int DateTime::getYearsSince(const DateTime& reference) const
{
  int years;

  if (*this < reference) {
    return -1;
  }
  years=this->yr-reference.yr;
  if (this->mo < reference.mo) {
    --years;
  }
  else if (this->mo == reference.mo) {
    if (this->dy < reference.dy || (this->dy == reference.dy && this->getTime() < reference.getTime())) {
	years--;
    }
  }
  return years;
}

DateTime DateTime::hoursAdded(size_t hoursToAdd,std::string calendar) const
{
  DateTime new_dt=*this;

  new_dt.addHours(hoursToAdd,calendar);
  return new_dt;
}

DateTime DateTime::hoursSubtracted(size_t hoursToSubtract) const
{
  DateTime new_dt=*this;

  new_dt.subtractHours(hoursToSubtract);
  return new_dt;
}

DateTime DateTime::minutesAdded(size_t minutesToAdd,std::string calendar) const
{
  DateTime new_dt=*this;

  new_dt.addMinutes(minutesToAdd,calendar);
  return new_dt;
}

DateTime DateTime::minutesSubtracted(size_t minutesToSubtract) const
{
  DateTime new_dt=*this;

  new_dt.subtractMinutes(minutesToSubtract);
  return new_dt;
}

DateTime DateTime::monthsAdded(size_t monthsToAdd,std::string calendar) const
{
  DateTime new_dt=*this;

  new_dt.addMonths(monthsToAdd,calendar);
  return new_dt;
}

DateTime DateTime::monthsSubtracted(size_t monthsToSubtract) const
{
  DateTime new_dt=*this;

  new_dt.subtractMonths(monthsToSubtract);
  return new_dt;
}

DateTime DateTime::secondsAdded(size_t secondsToAdd,std::string calendar) const
{
  DateTime new_dt=*this;

  new_dt.addSeconds(secondsToAdd,calendar);
  return new_dt;
}

DateTime DateTime::secondsSubtracted(size_t secondsToSubtract) const
{
  DateTime new_dt=*this;

  new_dt.subtractSeconds(secondsToSubtract);
  return new_dt;
}

void DateTime::set(long long YYYYMMDDHHMMSS)
{
  long long year,month,day,time;

/*
  if (YYYYMMDDHHMMSS > 99999999) {
    time=YYYYMMDDHHMMSS % 1000000;
    YYYYMMDDHHMMSS/=1000000;
  }
  else
    time=0;
  if (YYYYMMDDHHMMSS > 999999) {
    day=YYYYMMDDHHMMSS % 100;
    YYYYMMDDHHMMSS/=100;
  }
  else
    day=0;
  if (YYYYMMDDHHMMSS > 9999) {
    month=YYYYMMDDHHMMSS % 100;
    YYYYMMDDHHMMSS/=100;
  }
  else
    month=0;
  year=YYYYMMDDHHMMSS;
*/
  time=YYYYMMDDHHMMSS % 1000000;
  YYYYMMDDHHMMSS/=1000000;
  if (YYYYMMDDHHMMSS > 0) {
    day=YYYYMMDDHHMMSS % 100;
    YYYYMMDDHHMMSS/=100;
  }
  else {
    day=0;
  }
  if (YYYYMMDDHHMMSS > 0) {
    month=YYYYMMDDHHMMSS % 100;
    YYYYMMDDHHMMSS/=100;
  }
  else {
    month=0;
  }
  if (YYYYMMDDHHMMSS > 0) {
    year=YYYYMMDDHHMMSS;
  }
  else {
    year=0;
  }
  set(year,month,day,time);
}

void DateTime::set(short year,short month,short day,size_t hhmmss)
{
  DateTime base;
  base.yr=1970;
  base.mo=1;
  base.dy=1;
  yr=year;
  mo=month;
  dy=day;
  setTime(hhmmss);
  if (*this == base) {
    wkdy=4;
  }
  else if (*this > base) {
    wkdy=((4+(getDaysSince(base) % 7)) % 7);
  }
  else {
    wkdy=((4-(base.getDaysSince(*this) % 7)) % 7);
  }
}

void DateTime::set(size_t hoursToAdd,const DateTime& reference,std::string calendar)
{
  *this=reference;
  this->addHours(hoursToAdd,calendar);
}

void DateTime::setToCurrent()
{
  time_t tm=time(NULL);
  struct tm *t;
  short tz=0;

  t=localtime(&tm);
  set(t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour*10000+t->tm_min*100+t->tm_sec);
  tz=local_utcOffset_from_standard_time_as_hhmm;
  if (t->tm_isdst > 0)
    tz+=100;
  setUTCOffset(tz);
  wkdy=t->tm_wday;
}

void DateTime::setUTCOffset(short utcOffset_as_hhmm)
{
  if (utcOffset_as_hhmm < -2400 || (utcOffset_as_hhmm > -100 && utcOffset_as_hhmm < 100 && utcOffset_as_hhmm != 0) || utcOffset_as_hhmm > 2400) {
    std::cerr << "Error: bad offset from UTC specified: " << utcOffset_as_hhmm << std::endl;
    exit(1);
  }
  utc_off=utcOffset_as_hhmm;
}

void DateTime::setTime(size_t hhmmss)
{
  sec=hhmmss % 100;
  hhmmss/=100;
  min=hhmmss % 100;
  hhmmss/=100;
  hr=hhmmss;
}

void DateTime::subtract(std::string units,size_t numToSubtract)
{
  units=strutils::to_lower(units);
  if (units == "hours") {
    subtractHours(numToSubtract);
  }
  else if (units == "days") {
    subtractDays(numToSubtract);
  }
  else if (units == "months") {
    subtractMonths(numToSubtract);
  }
  else if (units == "years") {
    subtractYears(numToSubtract);
  }
  else if (units == "minutes") {
    subtractMinutes(numToSubtract);
  }
  else if (units == "seconds") {
    subtractSeconds(numToSubtract);
  }
  else {
    std::cerr << "Error: units " << units << " not recognized" << std::endl;
    exit(1);
  }
}

void DateTime::subtractDays(size_t daysToSubtract)
{
  size_t days[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
  short newdy;

  if (isLeapYear(yr)) days[2]=29;
  newdy=dy-daysToSubtract;
  while (newdy <= 0) {
    mo--;
    if (mo < 1) {
	yr--;
	days[2]= (isLeapYear(yr)) ? 29 : 28;
	mo=12;
    }
    newdy+=days[mo];
  }
  dy=newdy;
}

void DateTime::subtractHours(size_t hoursToSubtract)
{
  size_t hh,dd;

  dd=hoursToSubtract/24;
  hh=hoursToSubtract % 24;
  hr-=hh;
  if (hr < 0) {
    hr+=24;
    dd++;
  }
  subtractDays(dd);
}

void DateTime::subtractMinutes(size_t minutesToSubtract)
{
  size_t hh,mm;

  hh=minutesToSubtract/60;
  mm=minutesToSubtract % 60;
  min-=mm;
  if (min < 0) {
    min+=60;
    hh++;
  }
  subtractHours(hh);
}

void DateTime::subtractMonths(size_t monthsToSubtract)
{
  size_t days[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
  size_t n,mm;

  for (n=0; n < monthsToSubtract; n++) {
    days[2]= (isLeapYear(yr)) ? 29 : 28;
    mm=mo-1;
    if (mm == 0)
	mm=12;
    subtractDays(days[mm]);
  }
}

void DateTime::subtractSeconds(size_t secondsToSubtract)
{
  size_t mm,ss;

  mm=secondsToSubtract/60;
  ss=secondsToSubtract % 60;
  sec-=ss;
  if (sec < 0) {
    sec+=60;
    mm++;
  }
  subtractMinutes(mm);
}

void DateTime::subtractYears(size_t yearsToSubtract)
{

  yr-=yearsToSubtract;
}

DateTime DateTime::subtracted(std::string units,size_t numToSubtract) const
{
  DateTime new_dt=*this;

  new_dt.subtract(units,numToSubtract);
  return new_dt;
}

std::string DateTime::toString() const
{
  std::stringstream dt_str;
  dt_str << std::setfill('0') << std::setw(4) << yr << "-" << std::setw(2) << mo << "-" << std::setw(2) << dy << " " << std::setw(2) << hr << ":" << std::setw(2) << min << ":" << std::setw(2) << sec << " ";
  if (utc_off < 0) {
    if (utc_off > -2400) {
	dt_str << "-" << std::setw(4) << abs(utc_off);
    }
    else if (utc_off == -2400) {
	dt_str << "LST  ";
    }
  }
  else {
    if (utc_off < 2400) {
	dt_str << "+" << std::setw(4) << abs(utc_off);
    }
    else if (utc_off == 2400) {
	dt_str << "LT   ";
    }
  }
  return dt_str.str();
}

std::string DateTime::toString(const char *format) const
{
// uses formats as in cftime, with additions:
//  %mm - month [1-12] with no leading zero for single digits
//  %dd - day [1-31] with no leading zero for single digits
//  %HH - hour (24-hour clock) [0-23] with no leading zero for single digits
//  %hh - full month name
//  %MM - minutes with leading zero for single digits
//  %SS - seconds with leading zero for single digits
//  %ZZ - time zone with ':' between hour and minute
  std::string date_string,tz;
  const char *wkdys[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
  const char *hmonths[]={"","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
  const char *hhmonths[]={"","January","February","March","April","May","June","July","August","September","October","November","December"};

  date_string=format;
  date_string=std::regex_replace(date_string,std::regex("%ISO8601"),"%Y-%m-%dT%H:%MM:%SS%ZZ");
// double-letter formats MUST come before single-letter formats or else the
//  replacement will not work correctly (i.e. - %HH before %H)
  if (std::regex_search(date_string,std::regex("%dd"))) {
    date_string=std::regex_replace(date_string,std::regex("%dd"),strutils::itos(dy));
  }
  if (std::regex_search(date_string,std::regex("%d"))) {
    date_string=std::regex_replace(date_string,std::regex("%d"),strutils::ftos(dy,2,0,'0'));
  }
  if (std::regex_search(date_string,std::regex("%HH"))) {
    date_string=std::regex_replace(date_string,std::regex("%HH"),strutils::itos(hr));
  }
  if (std::regex_search(date_string,std::regex("%H"))) {
    date_string=std::regex_replace(date_string,std::regex("%H"),strutils::ftos(hr,2,0,'0'));
  }
  if (std::regex_search(date_string,std::regex("%hh"))) {
    date_string=std::regex_replace(date_string,std::regex("%hh"),hhmonths[mo]);
  }
  if (std::regex_search(date_string,std::regex("%h"))) {
    date_string=std::regex_replace(date_string,std::regex("%h"),hmonths[mo]);
  }
  if (std::regex_search(date_string,std::regex("%MM"))) {
    date_string=std::regex_replace(date_string,std::regex("%MM"),strutils::ftos(min,2,0,'0'));
  }
  if (std::regex_search(date_string,std::regex("%M"))) {
    date_string=std::regex_replace(date_string,std::regex("%M"),strutils::itos(min));
  }
  if (std::regex_search(date_string,std::regex("%mm"))) {
    date_string=std::regex_replace(date_string,std::regex("%mm"),strutils::itos(mo));
  }
  if (std::regex_search(date_string,std::regex("%m"))) {
    date_string=std::regex_replace(date_string,std::regex("%m"),strutils::ftos(mo,2,0,'0'));
  }
  if (std::regex_search(date_string,std::regex("%R"))) {
    date_string=std::regex_replace(date_string,std::regex("%R"),strutils::ftos(hr,2,0,'0')+":"+strutils::ftos(min,2,0,'0'));
  }
  if (std::regex_search(date_string,std::regex("%SS"))) {
    date_string=std::regex_replace(date_string,std::regex("%SS"),strutils::ftos(sec,2,0,'0'));
  }
  if (std::regex_search(date_string,std::regex("%S"))) {
    date_string=std::regex_replace(date_string,std::regex("%S"),strutils::itos(sec));
  }
  if (std::regex_search(date_string,std::regex("%T"))) {
    date_string=std::regex_replace(date_string,std::regex("%T"),strutils::ftos(hr,2,0,'0')+":"+strutils::ftos(min,2,0,'0')+":"+strutils::ftos(sec,2,0,'0'));
  }
  if (std::regex_search(date_string,std::regex("%Y"))) {
    date_string=std::regex_replace(date_string,std::regex("%Y"),strutils::ftos(yr,4,0,'0'));
  }
  if (std::regex_search(date_string,std::regex("%ZZ"))) {
    if (utc_off > -2400 && utc_off < 2400) {
	tz=strutils::ftos(abs(utc_off),4,0,'0');
	tz.insert(2,":");
	if (utc_off < 0) {
	  tz.insert(0,"-");
	}
	else {
	  tz.insert(0,"+");
	}
	date_string=std::regex_replace(date_string,std::regex("%ZZ"),tz);
    }
    else {
	date_string=std::regex_replace(date_string,std::regex("%ZZ"),"%Z");
    }
  }
  if (std::regex_search(date_string,std::regex("%Z"))) {
    if (utc_off > -2400 && utc_off < 2400) {
	tz=strutils::ftos(abs(utc_off),4,0,'0');
	if (utc_off < 0) {
	  tz.insert(0,"-");
	}
	else {
	  tz.insert(0,"+");
	}
	date_string=std::regex_replace(date_string,std::regex("%Z"),tz);
    }
    else if (utc_off == -2400) {
	date_string=std::regex_replace(date_string,std::regex("%Z"),"LST");
    }
    else if (utc_off == 2400) {
	date_string=std::regex_replace(date_string,std::regex("%Z"),"LT");
    }
  }
  if (std::regex_search(date_string,std::regex("%a")) && wkdy >= 0) {
    date_string=std::regex_replace(date_string,std::regex("%a"),wkdys[wkdy]);
  }
  return date_string;
}

DateTime DateTime::timeAdded(size_t hhmmss,std::string calendar) const
{
  DateTime new_dt=*this;

  new_dt.addTime(hhmmss,calendar);
  return new_dt;
}

DateTime DateTime::yearsAdded(size_t yearsToAdd) const
{
  DateTime new_dt=*this;

  new_dt.addYears(yearsToAdd);
  return new_dt;
}

DateTime DateTime::yearsSubtracted(size_t yearsToSubtract) const
{
  DateTime new_dt=*this;

  new_dt.subtractYears(yearsToSubtract);
  return new_dt;
}

bool operator!=(const DateTime& source1,const DateTime& source2)
{
  if (source1.yr != source2.yr)
    return true;
  if (source1.mo != source2.mo)
    return true;
  if (source1.dy != source2.dy)
    return true;
  if (source1.hr != source2.hr)
    return true;
  if (source1.min != source2.min)
    return true;
  if (source1.sec != source2.sec)
    return true;
  return false;
}

bool operator<(const DateTime& source1,const DateTime& source2)
{
  if (source1.yr < source2.yr)
    return true;
  else if (source1.yr == source2.yr) {
    if (source1.mo < source2.mo)
	return true;
    else if (source1.mo == source2.mo) {
	if (source1.dy < source2.dy)
	  return true;
	else if (source1.dy == source2.dy) {
	  if (source1.hr < source2.hr)
	    return true;
	  else if (source1.hr == source2.hr) {
	    if (source1.min < source2.min)
		return true;
	    else if (source1.min == source2.min) {
		if (source1.sec < source2.sec)
		  return true;
	    }
	  }
	}
    }
  }
  return false;
}

bool operator<=(const DateTime& source1,const DateTime& source2)
{
  if (source1 < source2 || source1 == source2)
    return true;
  return false;
}

bool operator>(const DateTime& source1,const DateTime& source2)
{
  if (source1.yr > source2.yr)
    return true;
  else if (source1.yr == source2.yr) {
    if (source1.mo > source2.mo)
	return true;
    else if (source1.mo == source2.mo) {
	if (source1.dy > source2.dy)
	  return true;
	else if (source1.dy == source2.dy) {
	  if (source1.hr > source2.hr)
	    return true;
	  else if (source1.hr == source2.hr) {
	    if (source1.min > source2.min)
		return true;
	    else if (source1.min == source2.min) {
		if (source1.sec > source2.sec)
		  return true;
	    }
	  }
	}
    }
  }
  return false;
}

bool operator>=(const DateTime& source1,const DateTime& source2)
{
  if (source1 == source2 || source1 > source2)
    return true;
  return false;
}

DateTime getCurrentDateTime()
{
  DateTime dt;

  dt.setToCurrent();
  return dt;
}

bool isLeapYear(size_t year)
{
  if ( (year % 4) == 0 && ( (year % 100 != 0) || (year % 400) == 0)) {
    return true;
  }
  else {
    return false;
  }
}

size_t getDaysInMonth(size_t year,size_t month,std::string calendar)
{
  size_t ndays;

  if (month < 1 || month > 12)
    return 0;
  ndays=DateTime::days_in_month[month];
  if (calendar.length() == 0 || calendar != "noleap") {
    if (month == 2 && isLeapYear(year))
	ndays++;
  }
  return ndays;
}

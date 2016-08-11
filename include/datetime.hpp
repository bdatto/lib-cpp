#ifndef DATETIME_HPP
#define   DATETIME_HPP

#include <string>

class DateTime
{
public:
  static const short local_utcOffset_from_standard_time_as_hhmm;
  static const size_t days_in_month[13];
  DateTime() : yr(0),mo(0),dy(0),hr(0),min(0),sec(0),utc_off(0),wkdy(-1) {}
  DateTime(short year,short month,short day,size_t hhmmss,short utcOffset_as_hhmm) : DateTime() {
    set(yr,mo,dy,hhmmss);
    setUTCOffset(utcOffset_as_hhmm);
  }
  DateTime(long long YYYYMMDDHHMMSS) : DateTime() {
    set(YYYYMMDDHHMMSS);
  }
  void add(std::string units,size_t numToAdd,std::string calendar = "");
  void addDays(size_t daysToAdd,std::string calendar = "");
  void addHours(size_t hoursToAdd,std::string calendar = "");
  void addMinutes(size_t minutesToAdd,std::string calendar = "");
  void addMonths(size_t monthsToAdd,std::string calendar = "");
  void addSeconds(size_t secondsToAdd,std::string calendar = "");
  void addTime(size_t hhmmss,std::string calendar = "");
  void addYears(size_t yearsToAdd);
  DateTime added(std::string units,size_t numToAdd,std::string calendar = "") const;
  DateTime daysAdded(size_t daysToAdd,std::string calendar = "") const;
  DateTime daysSubtracted(size_t daysToSubtract) const;
  short getDay() const { return dy; }
  int getDaysSince(const DateTime& reference,std::string calendar = "") const;
  int getHoursSince(const DateTime& reference,std::string calendar = "") const;
  int getMinutesSince(const DateTime& reference,std::string calendar = "") const;
  short getMonth() const { return mo; }
  int getMonthsSince(const DateTime& reference) const;
  long long getSecondsSince(const DateTime& reference,std::string calendar = "") const;
  size_t getTime() const { return hr*10000+min*100+sec; }
  int getTimeSince(const DateTime& reference,std::string calendar = "") const;
  short getUTCOffset() const { return utc_off; }
  short getWeekDay() const { return wkdy; }
  short getYear() const { return yr; }
  int getYearsSince(const DateTime& reference) const;
  DateTime hoursAdded(size_t hoursToAdd,std::string calendar = "") const;
  DateTime hoursSubtracted(size_t hoursToSubtract) const;
  DateTime minutesAdded(size_t minutesToAdd,std::string calendar = "") const;
  DateTime minutesSubtracted(size_t minutesToSubtract) const;
  DateTime monthsAdded(size_t monthsToAdd,std::string calendar = "") const;
  DateTime monthsSubtracted(size_t monthsToSubtract) const;
  DateTime secondsAdded(size_t secondsToAdd,std::string calendar = "") const;
  DateTime secondsSubtracted(size_t secondsToSubtract) const;
  void set(long long YYYYMMDDHHMMSS);
  void set(short year,short month=0,short day=0,size_t hhmmss = 0);
  void set(size_t hoursToAdd,const DateTime& reference,std::string calendar = "");
  void setDay(short day) { dy=day; }
  void setMonth(short month) { mo=month; }
  void setTime(size_t hhmmss);
  void setToCurrent();
  void setUTCOffset(short utcOffset_as_hhmm);
  void setWeekDay(short weekday) { wkdy=weekday; }
  void setYear(short year) { yr=year; }
  void subtract(std::string units,size_t numToSubtract);
  void subtractDays(size_t daysToSubtract);
  void subtractHours(size_t hoursToSubtract);
  void subtractMinutes(size_t minutesToSubtract);
  void subtractMonths(size_t monthsToSubtract);
  void subtractSeconds(size_t secondsToSubtract);
  void subtractYears(size_t yearsToSubtract);
  DateTime subtracted(std::string units,size_t numToSubtract) const;
  std::string toString() const;
  std::string toString(const char *format) const;
  DateTime timeAdded(size_t hhmmss,std::string calendar = "") const;
  DateTime yearsAdded(size_t yearsToAdd) const;
  DateTime yearsSubtracted(size_t yearsToSubtract) const;
  friend bool operator==(const DateTime& source1,const DateTime& source2)
  { return !(source1 != source2); }
  friend bool operator!=(const DateTime& source1,const DateTime& source2);
  friend bool operator<(const DateTime& source1,const DateTime& source2);
  friend bool operator<=(const DateTime& source1,const DateTime& source2);
  friend bool operator>(const DateTime& source1,const DateTime& source2);
  friend bool operator>=(const DateTime& source1,const DateTime& source2);

private:
  short yr,mo,dy,hr,min,sec,utc_off,wkdy;
};

extern DateTime getCurrentDateTime();
extern size_t getDaysInMonth(size_t year,size_t month,std::string calendar = "");
extern bool isLeapYear(size_t year);

#endif

#ifndef UTILS_HPP
#define   UTILS_HPP

#include <iostream>
#include <fstream>
#include <list>
#include <deque>

namespace summary {

extern std::string convertHTMLSummaryToASCII(std::string summary,size_t wrapLength,size_t indentLength);

} // end namespace summary

namespace metcalcs {

extern double computeRelativeHumidity(double temperature,double dew_point_temperature);
extern double computeDewPointTemperature(double dry_bulb_temperature,double wet_bulb_temperature,double station_pressure);
extern double computeStandardHeightFromPressure(double pressure);
extern double computeHeightFromPressureAndTemperature(double pressure,double temperature);
extern void computeWindDirectionAndSpeedFromUAndV(double u,double v,int& wind_direction,double& wind_speed);

} // end namespace metcalcs

extern void ascii_to_ebc(char *dest,char *src,size_t num);
//extern void chop(char *string);
extern void convertOctal(long long octal,long long& lval,int power = 0);
extern void dump(unsigned char *buffer,int length);
extern void ebc_to_ascii(char *dest,char *src,size_t num);
extern void getLonIndexBoundsFromBitmap(const char *bitmap,size_t& min_lon_index,size_t& max_lon_index);
extern void getLatLonFromLambertConformalGridpoint(size_t i,size_t j,double lat1,double elon1,double dx,double elonv,double tanlat,double& lat,double& elon);
extern void getLatLonFromPolarStereographicGridPoint(size_t i,size_t j,size_t num_i,size_t num_j,double dx,double elonv,char projection,double dx_lat,double& lat,double& elon);
extern void getSpatialDomainFromLambertConformalGrid(size_t num_i,size_t num_j,double lat1,double elon1,double dx,double elonv,double tanlat,double& west_lon,double& south_lat,double& east_lon,double& north_lat);
extern void getSpatialDomainFromPolarStereographicGrid(size_t num_x,size_t num_y,double dx,double elonv,char projection,double dx_lat,double& west_lon,double& south_lat,double& east_lon,double& north_lat);
extern void getSpatialDomainFromPolarStereographicGrid2(size_t num_x,size_t num_y,double start_lat,double start_elon,double dx,double elonv,char projection,double dx_lat,double& west_lon,double& south_lat,double& east_lon,double& north_lat);
extern void julianDay(int jul_day,size_t& year,size_t& month,size_t& day,size_t base_year = 1900);
extern void marsdenToLatLon(std::string msquare_spec,double& lat,double& lon);
extern void putLocalFile(std::string server_name,std::string remote_directory,std::string local_filename,std::string dssRoot);
extern void sendmail(std::string to_list,std::string from,std::string bcc_list,std::string subject,std::string body);
extern void strput(char *string,int numeric,int num_chars,char fill = ' ',bool is_signed = false);
extern void untar(std::string dirname,std::string filename);

#if defined(_AIX)
extern "C" void gbyte(long long *buffer,long long& loc,long long& offset,long long& bits);
extern "C" void gbytes(long long *buffer,long long *loc,long long& offset,long long& bits,long long& skip,long long& num);
extern "C" void sbyte(long long *buffer,long long& loc,long long& offset,long long& bits);
extern "C" void sbytes(long long *buffer,long long *loc,long long& offset,long long& bits,long long& skip,long long& num);
#else
extern "C" void gbyte_(long long *buffer,long long& loc,long long& offset,long long& bits);
extern "C" void gbytes_(long long *buffer,long long *loc,long long& offset,long long& bits,long long& skip,long long& num);
extern "C" void sbyte_(long long *buffer,long long& loc,long long& offset,long long& bits);
extern "C" void sbytes_(long long *buffer,long long *loc,long long& offset,long long& bits,long long& skip,long long& num);
#endif

extern int convertBoxToCenterLatLon(size_t box_size,size_t lat_index,size_t lon_index,double& lat,double& lon);
extern int convertLatLonToBox(size_t box_size,double lat,double lon,size_t& lat_index,size_t& lon_index);
extern int hostSync(std::string local_filename,std::string remote_filename,std::string& error);
extern int hostSyncFrom(std::string remote_filename,std::string local_filename,std::stringstream& ess);
extern int hostUnsync(std::string remote_filename,std::string& error);
extern int julianDay(size_t year,size_t month,size_t day,size_t base_year = 1900);
extern int lock(const std::string& filename,std::string contents = "");
extern int makeRDAWebDirectory(std::string remote_directory,std::stringstream& ess);
//extern int mysystem(std::string command,std::string& output,std::string& error);
extern int mysystem2(std::string command,std::stringstream& output,std::stringstream& error);
extern int otoi(int octal);
#if defined(MathExtras)
extern int round(double val);
#endif
extern int roundp(int val,size_t place);
extern int strcnt(char *string,char *separator);
extern int strsplit(const char *string,const char *separator,char ***array);
extern int unlock(const std::string& filename);

extern long long cdcconv(double native_real,size_t sign_representation);
extern long long checksum(const unsigned char *buf,size_t num_words,size_t word_size,long long& sum);
extern long long getCalendarTime(std::string dateTimeSpecification);
extern long long getLittleEndian(unsigned char *buffer,size_t num_bytes);
extern long long hex2long(char *hex_string,int num_chars);
extern long long htoi(char *hex_string);
extern long long itoo(int ival);
#if defined(MathExtras)
extern long long lround(double val);
#endif
extern long long ltoo(long long ival);
extern long long otoll(long long octal);

extern double arc_distance(double lat1,double lon1,double lat2,double lon2);
extern double cdcconv(const unsigned char *buf,size_t off,size_t sign_representation);
extern double crayconv(const unsigned char *buf,size_t off);
extern double cyberconv(const unsigned char *buf,size_t off);
extern double cyberconv64(const unsigned char *buf,size_t off);
extern double gc_distance(double lat1,double lon1,double lat2,double lon2);
extern double ibmconv(const unsigned char *buf,size_t off);

extern char *ascebc(char *dest,char *src);
extern char *ascndpc(char *dest,char *src,size_t num);
extern char *ascnebc(char *dest,char *src,size_t num);
extern char *btoa(bool b);
extern char *dpcnasc(char *dest,char *src,size_t num);
extern char *ebcasc(char *dest,char *src);
extern char *ebcdnasc(char *dest,char *src,size_t num);
extern char *ebcdnebc(char *dest,char *src,size_t num);
extern char *ebcnasc(char *dest,char *src,size_t num);
extern char *ibcdnasc(char *dest,char *src,size_t num);
extern char *ibcdnebc(char *dest,char *src,size_t num);
extern char *itoa(size_t num);
extern char *itoa(size_t num,size_t width,char pad);
extern char *itoh(int ival);
extern char *lltoh(long long llval);
extern char *tilde(const char *tilde_string);

extern size_t ibmconv(double native_real);
extern size_t latLonToMarsden(double& lat,double& lon,size_t q);

extern std::string buildLockName(const std::string& filename);
extern std::string findHsiCommand();
extern std::string getHostName();
extern std::string getRemoteFile(std::string server_name,std::string local_tmpdir,std::string remote_filename,std::string& error);
extern std::string getRemoteWebFile_old(std::string URL,std::string local_tmpdir,std::string dssRoot);
extern std::string getRemoteWebFile(std::string URL,std::string local_tmpdir);
extern std::string getUnixArgsString(int argc,char **argv,char separator = ':');
extern std::string retryCommand(std::string command,int num_retries);
extern std::string strand(size_t length);
extern std::string transformSuperscripts(std::string s);

extern bool existsOnRDAWebServer(std::string server_name,std::string remote_filename,struct stat& buf);
extern bool isLocked(const std::string& filename);
extern bool isNumeric(const char *string);
extern bool myequalf(double a,double b);
extern bool myequalf(double a,double b,double tol);
extern bool openLockFile(const std::string& filename,std::ifstream& ifs);
extern bool tar(std::string tarfile,std::list<std::string>& filenames);
extern bool withinPolygon(std::string polygon,std::string point);

inline bool system_is_big_endian()
{
  union {
    uint32_t i;
    char c[4];
  } test;

  test.i=0x04030201;
  return (test.c[0] == 4);
}

#endif

#ifndef UTILS_HPP
#define   UTILS_HPP

#include <iostream>
#include <fstream>
#include <list>
#include <deque>
#include <complex>
#include <mymap.hpp>

namespace summary {

extern std::string convertHTMLSummaryToASCII(std::string summary,size_t wrapLength,size_t indentLength);

} // end namespace summary

namespace hereDoc {

struct IfEntry {
  IfEntry() : key() {}

  std::string key;
};
struct RepeatEntry {
  RepeatEntry() : key(),list(nullptr) {}

  std::string key;
  std::shared_ptr<std::deque<std::string>> list;
};
struct Tokens {
  Tokens() : replaces(),ifs(),repeats() {}
  void clear() {
    replaces.clear();
    ifs.clear();
    repeats.clear();
  }

  std::list<std::string> replaces;
  my::map<IfEntry> ifs;
  my::map<RepeatEntry> repeats;
};
extern void print(std::string filename,Tokens* tokens = NULL);
extern void print(std::string filename,Tokens* tokens,std::ostream& ofs,size_t indent_length = 0);

} // end namespace hereDoc

namespace strutils {

extern void chop(std::string& s,size_t num_chars = 1);
extern void convertUnicode(std::string& s);
extern void replace_all(std::string& s,const std::string& old_s,const std::string& new_s);
extern void trim_back(std::string& s);
extern void trim_front(std::string& s);
extern void trim(std::string& s);

extern bool contains(const std::string& s,const std::string& sub_s);
extern bool has_beginning(const std::string& s,const std::string& beginning);
extern bool has_ending(const std::string& s,const std::string& ending);
extern bool has_no_letters(const std::string& s);
extern bool is_alpha(const std::string& s);
extern bool is_alphanumeric(const std::string& s);
extern bool is_numeric(const std::string& s);

extern size_t occurs(const std::string& s,const std::string& find_s);

extern std::deque<std::string> split(const std::string& s,const std::string& separator = "");
extern std::deque<std::string> xml_split(const std::string& s);

extern std::string capitalize(const std::string& s);
extern std::string dtos(double val,size_t max_d = 0);
extern std::string dtos(double val,size_t w,size_t d,char fill = ' ');
extern std::string ftos(float val,size_t max_d = 0);
extern std::string ftos(float val,size_t w,size_t d,char fill = ' ');
extern std::string get_env(const std::string& name);
extern std::string itos(int val);
extern std::string lltos(long long val,size_t w = 0,char fill = ' ');
extern std::string number_with_commas(std::string s);
extern std::string number_with_commas(long long l);
extern std::string soundex(const std::string& s);
extern std::string substitute(const std::string& s,const std::string& old_s,const std::string& new_s);
extern std::string to_lower(const std::string& s);
extern std::string to_upper(const std::string& s,size_t start,size_t num_chars);
extern std::string to_upper(const std::string& s);
extern std::string token(const std::string& s,const std::string& separator,size_t token_number);

} // end namespace strutils

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

// Templates

template <class MaskType>
inline void createMask(MaskType& mask,size_t size)
{
  size_t n;

  mask=1;
  for (n=1; n < size; n++)
    (mask<<=1)++;
}

template <class BufType,class LocType>
inline void extractBits(const BufType *buf,LocType *loc,size_t off,const size_t bits,size_t skip = 0,const size_t num = 1)
{
// create a mask to use when right-shifting (necessary because different
// compilers do different things when right-shifting a signed bit-field)
  BufType bmask;
  size_t loc_size=sizeof(LocType)*8,buf_size=sizeof(BufType)*8,wskip;
  int rshift;
  LocType lmask,temp;

  if (bits > loc_size) {
    std::cerr << "Error: trying to unpack " << bits << " bits into a " << loc_size << "-bit location" << std::endl;
    exit(1);
  }
  else {
    createMask(bmask,buf_size);
    skip+=bits;
    if (loc_size <= buf_size) {
	for (size_t n=0; n < num; ++n) {
// skip to the word containing the packed field
	  wskip=off/buf_size;
// right shift the bits in the packed buffer word to eliminate unneeded bits
	  rshift=buf_size-(off % buf_size)-bits;
// check for a packed field spanning two words
	  if (rshift < 0) {
	    loc[n]=(buf[wskip]<<-rshift);
	    loc[n]+=(buf[++wskip]>>(buf_size+rshift))&~(bmask<<-rshift);
	  }
	  else {
	    loc[n]=(buf[wskip]>>rshift);
	  }
// remove any unneeded leading bits
	  if (bits != buf_size) loc[n]&=~(bmask<<bits);
	  off+=skip;
	}
    }
    else {
	createMask(lmask,loc_size);
// get difference in bits between word size of packed buffer and word size of
// unpacked location
	for (size_t n=0; n < num; ++n) {
// skip to the word containing the packed field
	  wskip=off/buf_size;
// right shift the bits in the packed buffer word to eliminate unneeded bits
	  rshift=buf_size-(off % buf_size)-bits;
// check for a packed field spanning multiple words
	  if (rshift < 0) {
	    LocType not_bmask;
	    createMask(not_bmask,loc_size-buf_size);
	    not_bmask=~(not_bmask<<buf_size);
	    loc[n]=0;
	    while (rshift < 0) {
		temp=buf[wskip++]&not_bmask;
		loc[n]+=(temp<<-rshift);
		rshift+=buf_size;
	    }
	    if (rshift != 0) {
		loc[n]+=(buf[wskip]>>rshift)&~(bmask<<(buf_size-rshift));
	    }
	    else {
		loc[n]+=buf[wskip]&not_bmask;
	    }
	  }
	  else {
	    loc[n]=(buf[wskip]>>rshift);
	  }
// remove any unneeded leading bits
	  if (bits != loc_size) loc[n]&=~(lmask<<bits);
	  off+=skip;
	}
    }
  }
}

template <class BufType,class LocType>
void getBits(const BufType *buf,LocType *loc,const size_t off,const size_t bits,const size_t skip,const size_t num)
{
// no work to do
  if (bits == 0) return;

  extractBits(buf,loc,off,bits,skip,num);
}

template <class BufType,class LocType>
void getBits(const BufType *buf,LocType& loc,const size_t off,const size_t bits)
{
// no work to do
  if (bits == 0) return;

  extractBits(buf,&loc,off,bits);
}

template <class BufType,class SrcType>
inline void putBits(BufType *buf,const SrcType *src,size_t off,const size_t bits,size_t skip = 0,const size_t num = 1)
{
// create a mask to use when right-shifting (necessary because different
// compilers do different things when right-shifting a signed bit-field)
  size_t src_size=sizeof(SrcType)*8,buf_size=sizeof(BufType)*8;
  size_t n,wskip,bskip,lclear,rclear,more;
  BufType bmask,left,right;
  SrcType smask;

  if (bits > src_size) {
//    std::cerr << "Error: packing " << bits << " bits from a " << src_size << "-bit field" << std::endl;
    exit(1);
  }
  else {
    createMask(bmask,buf_size);
    createMask(smask,src_size);
    skip+=bits;
    for (n=0; n < num; n++) {
// get number of words and bits to skip before packing begins
	wskip=off/buf_size;
	bskip=off % buf_size;
	lclear=bskip+bits;
	rclear=buf_size-bskip;
	left= (rclear != buf_size) ? (buf[wskip]&(bmask<<rclear)) : 0;
	if (lclear <= buf_size) {
// all bits to be packed are in the current word
// clear the field to be packed
	  right=
          (lclear != buf_size) ? (buf[wskip]&~(bmask<<(buf_size-lclear))) : 0;
// fill the field to be packed
	  buf[wskip]= (src_size != bits) ? (src[n]&~(smask<<bits)) : src[n];
	  buf[wskip]=left|right|(buf[wskip]<<(rclear-bits));
	}
	else {
// bits to be packed cross a word boundary(ies)
// clear the bit field to be packed
	  more=bits-rclear;
//	  buf[wskip]= (buf_size > src_size) ? left|((src[n]>>more)&~(bmask<<(bits-more))) : left|(src[n]>>more);
	  buf[wskip]=(left|((src[n]>>more)&~(smask<<(bits-more))));
// clear the next (or part of the next) word and pack those bits
	  while (more > buf_size) {
	    more-=buf_size;
	    buf[++wskip]=((src[n]>>more)&~(smask<<(src_size-more)));
	  }
	  wskip++;
	  more=buf_size-more;
	  right= (more != buf_size) ? (buf[wskip]&~(bmask<<more)) : 0;
	  buf[wskip]= (buf_size > src_size) ? (src[n]&~(bmask<<src_size)) : src[n];
	  buf[wskip]=right|(buf[wskip]<<more);
	}
	off+=skip;
    }
  }
}

template <class BufType,class SrcType>
void setBits(BufType *buf,const SrcType *src,const size_t off,const size_t bits,const size_t skip = 0,const size_t num = 1)
{
// no work to do
  if (bits == 0) return;

  putBits(buf,src,off,bits,skip,num);
}

template <class BufType,class SrcType>
void setBits(BufType *buf,const SrcType src,const size_t off,const size_t bits)
{
// no work to do
  if (bits == 0) return;

  putBits(buf,&src,off,bits);
}

template <class Type>
void strget(const char *str,Type& numeric_val,int num_chars)
{
  std::string cval(str,num_chars);
  int n,decimal;
  char *chr=const_cast<char *>(cval.c_str());
  double mult;
  bool neg_val=false,neg_exp=false;
  bool reading_exponent=false;
  int exp=0;

  strutils::trim(cval);
  num_chars=decimal=cval.length();
  numeric_val=0;
  for (n=0; n < num_chars; n++) {
    if (chr[n] == '.') {
	numeric_val*=0.1;
	decimal=n;
    }
    else if (chr[n] == 'E')
	reading_exponent=true;
    else {
	if (chr[n] == ' ' || chr[n] == '+' || chr[n] == '-') {
	  if (chr[n] == '-') {
	    if (!reading_exponent)
		neg_val=true;
	    else
		neg_exp=true;
	  }
	  chr[n]='0';
	}
	if (!reading_exponent)
	  numeric_val+=static_cast<Type>((chr[n]-48)*std::pow(10.,num_chars-n-1));
	else
	  exp+=static_cast<int>((chr[n]-48)*std::pow(10.,num_chars-n-1));
    }
  }
  if (neg_val) numeric_val=-numeric_val;
  if (decimal != num_chars) {
    mult=std::pow(0.1,num_chars-decimal-1);
    numeric_val*=static_cast<Type>(mult);
  }
  if (reading_exponent) {
    if (neg_exp) exp=-exp;
    numeric_val*=static_cast<Type>(std::pow(10.,exp));
  }
}

#endif

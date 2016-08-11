#ifndef STRUTILS_HPP
#define   STRUTILS_HPP

#include <string>
#include <deque>

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

#endif

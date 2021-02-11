#ifndef __SELECT_CONTAINS_HPP__
#define __SELECT_CONTAINS_HPP__

#include "select.hpp"
#include <cstring>

class Select_Contains : public Select_Column {
	private:
		std::string keyWord; 
	public:
		Select_Contains(const Spreadsheet* sheet, const std::string& colName, const std::string& subString):Select_Column(sheet, colName)
		{
			keyWord = subString;
		}
		virtual bool select(const std::string& s) const
                {
       	            	if (s.find(keyWord)!=std::string::npos){
           			return true;
     			}
   			return false;
                 }
		virtual ~Select_Contains()=default;
};

#endif // __SELECT_CONTAINS_HPP__

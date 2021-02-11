#ifndef __SELECT_AND_HPP__
#define __SELECT_AND_HPP__

#include "select.hpp"
#include "select_contains.hpp"
#include <cstring>

class Select_And : public Select {
   private:
	Select* left; 
	Select* right;
   public:
   	Select_And(Select* l, Select* r):Select()
    	{
		right=r;
		left=l;
	}

	 virtual bool select(const Spreadsheet* sheet, int row) const
    	{	
		return left->select(sheet, row) && right->select(sheet, row);
    	}
	virtual ~Select_And(){delete right; delete left;}
};
#endif

#ifndef __SELECT_OR_HPP__
#define __SELECT_OR_HPP__

#include "select.hpp"
#include "select_contains.hpp"
#include <cstring>

class Select_Or : public Select {
   private:
        Select* left;
        Select* right;
   public:
        Select_Or(Select* l, Select* r):Select()
        {
                right=r;
                left=l;
        }

         virtual bool select(const Spreadsheet* sheet, int row) const
        {
                return left->select(sheet, row) || right->select(sheet, row);
        }
	virtual ~Select_Or(){delete right; delete left;}
};
#endif

#ifndef __SELECT_NOT_HPP__
#define __SELECT_NOT_HPP__

#include "select.hpp"
#include "select_contains.hpp"
#include <cstring>

class Select_Not : public Select {
   private:
        Select* operand;
   public:
        Select_Not(Select* op):Select()
        {
                operand=op;
        }

         virtual bool select(const Spreadsheet* sheet, int row) const
        {
                return !operand->select(sheet, row);
        }
	virtual ~Select_Not(){delete operand;}
};
#endif

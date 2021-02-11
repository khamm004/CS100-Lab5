#include "spreadsheet.hpp"
#include "select_contains.hpp"
#include "select.hpp"
#include "select_and.hpp"
#include "select_or.hpp"
#include "select_not.hpp"
#include "gtest/gtest.h"
#include <iostream>

TEST(Spreadsheet, Print){
	Spreadsheet sheet;
	std:: stringstream s;
    sheet.set_column_names({"First","Last","Age","Major"});
    sheet.add_row({"Amanda","Andrews","22","business"});
    sheet.add_row({"Brian","Becker","21","computer science"});
   sheet.add_row({"Carol","Conners","21","computer science"});

    sheet.print_selection(s);
    EXPECT_EQ(s.str(), "Amanda Andrews 22 business \nBrian Becker 21 computer science \nCarol Conners 21 computer science \n");
    std::cout << std::endl;
}

TEST(Select_Contains, sameLetterInFirstName){
	Spreadsheet sheet;
	std:: stringstream s;
    sheet.set_column_names({"First","Last","Age","Major"});
    sheet.add_row({"Amanda","Andrews","22","business"});
    sheet.add_row({"Brian","Becker","21","computer science"});
    sheet.add_row({"Carol","Conners","21","computer science"});

    sheet.set_selection(new Select_Contains(&sheet,"First","a"));
    sheet.print_selection(s);
    EXPECT_EQ(s.str(), "Amanda Andrews 22 business \nBrian Becker 21 computer science \nCarol Conners 21 computer science \n");
    std::cout << std::endl;
}

TEST(Select_Contains, CapitalLetterInFirstName){
	Spreadsheet sheet;
	std:: stringstream s;
    sheet.set_column_names({"First","Last","Age","Major"});
    sheet.add_row({"Amanda","Andrews","22","business"});
    sheet.add_row({"Brian","Becker","21","computer science"});
    sheet.add_row({"Carol","Conners","21","computer science"});

    sheet.set_selection(new Select_Contains(&sheet,"First","A"));
    sheet.print_selection(s);
    EXPECT_EQ(s.str(), "Amanda Andrews 22 business \n");
    std::cout << std::endl;
}

TEST(Select_Contains, lowerCaseFirstName){
	Spreadsheet sheet;
	std:: stringstream s;
    sheet.set_column_names({"First","Last","Age","Major"});
    sheet.add_row({"Amanda","Andrews","22","business"});
    sheet.add_row({"Brian","Becker","21","computer science"});
    sheet.add_row({"Carol","Conners","21","computer science"});

    sheet.set_selection(new Select_Contains(&sheet,"First","amanda"));
    sheet.print_selection(s);
    EXPECT_EQ(s.str(), "");
    std::cout << std::endl;
}

TEST(Select_Contains, emptyString){
	Spreadsheet sheet;
	std:: stringstream s;
    sheet.set_column_names({"First","Last","Age","Major"});
    sheet.add_row({"Amanda","Andrews","22","business"});
    sheet.add_row({"Brian","Becker","21","computer science"});
    sheet.add_row({"Carol","Conners","21","computer science"});

    sheet.set_selection(new Select_Contains(&sheet,"Major",""));
    sheet.print_selection(s);
    EXPECT_EQ(s.str(), "Amanda Andrews 22 business \nBrian Becker 21 computer science \nCarol Conners 21 computer science \n");
    std::cout << std::endl;
}

TEST(Select_Contains, ColumnDNE){
	Spreadsheet sheet;
	std:: stringstream s;
    sheet.set_column_names({"First","Last","Age","Major"});
    sheet.add_row({"Amanda","Andrews","22","business"});
    sheet.add_row({"Brian","Becker","21","computer science"});
    sheet.add_row({"Carol","Conners","21","computer science"});

    sheet.set_selection(new Select_Contains(&sheet,"Year","1996"));
    sheet.print_selection(s);
    std::cout << "DNE"<< std::endl;
    EXPECT_EQ(s.str(),"");
    std::cout << std::endl;
}

TEST(Select_Contains, SameColumn){
	Spreadsheet sheet;
	std:: stringstream s;
   sheet.set_column_names({"First","Last","Age","Major", "Major"});
    sheet.add_row({"Amanda","Andrews","22","business", "business"});
    sheet.add_row({"Brian","Becker","21","computer science", "computer science"});
    sheet.add_row({"Carol","Conners","21","computer science", "math"});

    sheet.set_selection(new Select_Contains(&sheet,"Major","computer science"));
    sheet.print_selection(s);
    EXPECT_EQ(s.str(), "Brian Becker 21 computer science computer science \nCarol Conners 21 computer science math \n");
    std::cout << std::endl;
}

TEST(Select, PrintAnd){
	Spreadsheet sheet;
	std:: stringstream s;
    sheet.set_column_names({"Name","Species","Age",});
    sheet.add_row({"Tucker","dog","3"});
    sheet.add_row({"Daisy","dog","4"});
    sheet.add_row({"Patches","cat","2"});
    sheet.add_row({"Lily","fish","1"});
    sheet.add_row({"Tweety","bird","2"});

    sheet.set_selection(new Select_And(new Select_Contains(&sheet,"Species","dog"), new Select_Contains(&sheet,"Age","3")));
    sheet.print_selection(s);
    EXPECT_EQ(s.str(), "Tucker dog 3 \n");
    std::cout << std::endl;
}


TEST(Select_Or, PrintOr){
	Spreadsheet sheet;
	std:: stringstream s;
    sheet.set_column_names({"Name","Species","Age", "Legs"});
    sheet.add_row({"Tucker","dog","3","4"});
    sheet.add_row({"Daisy","dog","4","4"});
    sheet.add_row({"Patches","cat","2","4"});
    sheet.add_row({"Lily","fish","1","0"});
    sheet.add_row({"Tweety","bird","2","2"});

    sheet.set_selection(new Select_Or(new Select_Contains(&sheet,"Species","cat"), new Select_Contains(&sheet,"Age","3")));
    sheet.print_selection(s);
    EXPECT_EQ(s.str(), "Tucker dog 3 4 \nPatches cat 2 4 \n");
    std::cout << std::endl;
}

TEST(Select_Not, PrintNot){
	Spreadsheet sheet;
	std:: stringstream s;
    sheet.set_column_names({"Name","Species","Age", "Legs"});
    sheet.add_row({"Tucker","dog","3","4"});
    sheet.add_row({"Daisy","dog","4","4"});
    sheet.add_row({"Patches","cat","2","4"});
    sheet.add_row({"Lily","fish","1","0"});
    sheet.add_row({"Tweety","bird","2","2"});

    sheet.set_selection(new Select_Not(new Select_Contains(&sheet,"Legs","4")));
    sheet.print_selection(s);
    EXPECT_EQ(s.str(), "Lily fish 1 0 \nTweety bird 2 2 \n");
    std::cout << std::endl;
}

TEST(Select_And, PrintTwoAnd){
	Spreadsheet sheet;
	std:: stringstream s;
    sheet.set_column_names({"Name","Species","Age", "Legs"});
    sheet.add_row({"Tucker","dog","3","4"});
    sheet.add_row({"Daisy","dog","4","4"});
    sheet.add_row({"Patches","cat","2","4"});
    sheet.add_row({"Lily","fish","1","0"});
    sheet.add_row({"Tweety","bird","2","2"});
    sheet.add_row({"Tucker","hamster","2","4"});

    sheet.set_selection(new Select_And(new Select_Contains(&sheet,"Species","dog"), new Select_And(new Select_Contains(&sheet,"Age","3"), new Select_Contains(&sheet, "Name", "Tucker"))));

    sheet.print_selection(s);
    EXPECT_EQ(s.str(), "Tucker dog 3 4 \n");
    std::cout << std::endl;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

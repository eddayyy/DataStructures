#include <exception>
#include <iomanip>                                                        // setprecision()
#include <iostream>                                                       // boolalpha(), showpoint(), fixed()
#include <string>                                                         // to_string()

#include "CheckResults.hpp"
#include "GroceryItem.hpp"
#include "GroceryList.hpp"



namespace    // anonymous
{
  class GroceryListRegressionTest
  {
    public:
      GroceryListRegressionTest();

    private:
      void test();

      Regression::CheckResults affirm;
  } run_grocery_list_tests;




  void GroceryListRegressionTest::test()
  {
    const GroceryItem gItem_1( "gItem_1" ),
                      gItem_2( "gItem_2" ),
                      gItem_3( "gItem_3" ),
                      gItem_4( "gItem_4" ),
                      gItem_5( "gItem_5" ),
                      gItem_6( "gItem_6" );

    {
      GroceryList list;
      affirm.is_equal( "Default construction:  Size", 0U, list.size() );
    }

    {
      GroceryList list1 = { gItem_2, gItem_3, gItem_1, gItem_4 };
      GroceryList list2( list1 );
      affirm.is_equal( "Copy construction and equality", list1, list2 );

      GroceryList list3 = { gItem_3, gItem_1, gItem_4, gItem_5 };
      affirm.is_less_than   ("Relational 1", list1, list3);
      affirm.is_greater_than("Relational 2", list3, list1);
    }

    {
      GroceryList list;
      list.insert( gItem_3                             );
      list.insert( gItem_4, GroceryList::Position::BOTTOM );
      list.insert( gItem_1, 1                          );
      list.insert( gItem_2                             );

      GroceryList expected = {gItem_2, gItem_3, gItem_1, gItem_4};

      affirm.is_equal( "Initializer list constructor:  Size",    4U,       list.size() );
      affirm.is_equal( "Initializer list constructor:  content", expected, list        );
    }

    {
      GroceryList list1 = {gItem_2, gItem_3, gItem_1, gItem_4};
      list1 += {gItem_3, gItem_1, gItem_2, gItem_5};

      GroceryList list2 = {gItem_2, gItem_6, gItem_1, gItem_4};
      list1 += list2;

      GroceryList expected = {gItem_2, gItem_3, gItem_1, gItem_4, gItem_5, gItem_6};

      affirm.is_equal( "Initializer list concatenation:  Size",    6U,       list1.size() );
      affirm.is_equal( "Initializer list concatenation:  content", expected, list1        );

      affirm.is_equal( "Search - gItem_2",    0U, list1.find( gItem_2        ) );
      affirm.is_equal( "Search - gItem_3",    1U, list1.find( gItem_3        ) );
      affirm.is_equal( "Search - gItem_1",    2U, list1.find( gItem_1        ) );
      affirm.is_equal( "Search - gItem_4",    3U, list1.find( gItem_4        ) );
      affirm.is_equal( "Search - gItem_5",    4U, list1.find( gItem_5        ) );
      affirm.is_equal( "Search - gItem_6",    5U, list1.find( gItem_6        ) );
      affirm.is_equal( "Search - not there", 6U, list1.find( {"not there"} ) );
    }

    {
      GroceryList list = { gItem_3, gItem_3, gItem_3 };
      affirm.is_equal( "Silently ignore duplicates - size", list.size(), 1U );
      affirm.is_equal( "Silently ignore duplicates - content", list, GroceryList {gItem_3} );
    }

    {
      GroceryList list = {gItem_2, gItem_1, gItem_4, gItem_5, gItem_6};

      list.remove( gItem_1 );
      affirm.is_equal( "Remove by grocery item - middle", GroceryList {gItem_2, gItem_4, gItem_5, gItem_6}, list );

      list.remove( gItem_6 );
      affirm.is_equal( "Remove by grocery item - bottom", GroceryList {gItem_2, gItem_4, gItem_5}, list );

      list.remove( gItem_2 );
      affirm.is_equal( "Remove by grocery item - top", GroceryList {gItem_4, gItem_5}, list );

      list.remove( {"not there"} );
      affirm.is_equal( "Remove by grocery item - not there", GroceryList {gItem_4, gItem_5}, list );
    }

    {
      GroceryList list = {gItem_2, gItem_1, gItem_4, gItem_5, gItem_6};

      list.remove( 1 );
      affirm.is_equal( "Remove by position - middle", GroceryList {gItem_2, gItem_4, gItem_5, gItem_6}, list );

      list.remove( 3 );
      affirm.is_equal( "Remove by position - bottom", GroceryList {gItem_2, gItem_4, gItem_5}, list );

      list.remove( 0 );
      affirm.is_equal( "Remove by position - top", GroceryList {gItem_4, gItem_5}, list );

      list.remove( 10 );
      affirm.is_equal( "Remove by position - bad index", GroceryList {gItem_4, gItem_5}, list );
    }

    {
      GroceryList list = {gItem_2, gItem_1, gItem_4, gItem_5, gItem_6};

      list.moveToTop( gItem_5        );
      list.moveToTop( gItem_6        );
      list.moveToTop( gItem_6        );
      list.moveToTop( gItem_5        );
      list.moveToTop( gItem_4        );
      list.moveToTop( {"not there"} );

      GroceryList expected = {gItem_4, gItem_5, gItem_6, gItem_2, gItem_1};
      affirm.is_equal( "Move to top", expected, list );
    }

    {
      GroceryList list;

      try
      {
        for( unsigned i = 0; i < 100; ++i ) list.insert( GroceryItem{ "GroceryItem-" + std::to_string( i ) } );
        affirm.is_true( "Fixed size array capacity check", false );
      }
      catch ( const GroceryList::CapacityExceeded_Ex & )  // expected
      {
        affirm.is_true( "Fixed size array capacity check", true );
      }
    }
  }




  GroceryListRegressionTest::GroceryListRegressionTest()
  {
    // affirm.policy = Regression::CheckResults::ReportingPolicy::ALL;
    std::clog << std::boolalpha << std::showpoint << std::fixed << std::setprecision( 2 );


    try
    {
      std::clog << "\nGroceryList Regression Tests:\n";
      test();

      std::clog << "\n\nGroceryList Regression Test " << affirm << "\n\n";
    }
    catch( const std::exception & ex )
    {
      std::clog << "FAILURE:  Regression test for \"class GroceryList\" failed with an unhandled exception. \n\n\n"
                << ex.what() << std::endl;
    }
  }
}    // namespace

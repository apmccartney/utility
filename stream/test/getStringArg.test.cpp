#include <sstream>

#include "catch.hpp"

#include "utility/stream.hpp"

extern int testNumber;

SCENARIO("getStringArg returns the proper string from a stream with valid string",
	 "[utility],[stream]"){

  LOG(INFO) << "Test " << ++testNumber << ": No Errors Expected";

  const std::string name("testString");
  bool found;
  std::istringstream buffer;
  std::vector<std::string> bufferQueue;
  std::vector<int> lengthQueue;
  bufferQueue.emplace_back("\"\"");
  bufferQueue.emplace_back("\'\'");
  lengthQueue.emplace_back(0);
  bufferQueue.emplace_back("\"test\"");
  bufferQueue.emplace_back("\'test\'");
  lengthQueue.emplace_back(4);
  bufferQueue.emplace_back("\"test\'s\"");
  bufferQueue.emplace_back("\'test\"s\'");
  lengthQueue.emplace_back(6);
  bufferQueue.emplace_back("\"test/s\"");
  bufferQueue.emplace_back("\'test/s\'");
  lengthQueue.emplace_back(6);

  GIVEN("a stream with a valid string argument without found argument"){

    WHEN("passed to getStringArg with length argument equal to string length without found argument"){
      THEN("returns the correct string"){      
	auto stringIter = bufferQueue.begin();
	for (int length : lengthQueue){
	  buffer.clear();
	  buffer.str(*stringIter);
	  REQUIRE((*stringIter) == 
		  utility::stream::getStringArg(buffer, name, length));
	  stringIter++;
	  buffer.clear();
	  buffer.str(*stringIter);
	  REQUIRE((*stringIter) == 
		  utility::stream::getStringArg(buffer, name, length));
	  stringIter++;
	}  
      }
    }

    WHEN("passed to getStringArg with length argument greater than string length without found argument"){
      THEN("returns the correct string"){
	auto stringIter = bufferQueue.begin();
	for (int length : lengthQueue){
	  buffer.clear();
	  buffer.str(*stringIter);
	  REQUIRE((*stringIter) == 
		  utility::stream::getStringArg(buffer, name, length + 1));
	  stringIter++;
	  buffer.clear();
	  buffer.str(*stringIter);
	  REQUIRE((*stringIter) == 
		  utility::stream::getStringArg(buffer, name, length + 1));
	  stringIter++;
	}  
      }
    }

    WHEN("passed to getStringArg with length argument equal to string length and found argument"){
      THEN("returns the correct string and sets found to true"){
	auto stringIter = bufferQueue.begin();
	for (int length : lengthQueue){
	  buffer.clear();
	  buffer.str(*stringIter);
	  found = false;
	  REQUIRE((*stringIter) == 
		  utility::stream::getStringArg(buffer, name, length, found));
	  REQUIRE(true == found);
	  stringIter++;
	  buffer.clear();
	  buffer.str(*stringIter);
	  found = false;
	  REQUIRE((*stringIter) == 
		  utility::stream::getStringArg(buffer, name, length, found));
	  REQUIRE(true == found);
	  stringIter++;
	}
      }  
    }

    WHEN("passed to getStringArg with length argument greater than string length and found argument"){
      THEN("returns the correct string and sets found to true"){
	auto stringIter = bufferQueue.begin();
	for (int length : lengthQueue){
	  buffer.clear();
	  buffer.str(*stringIter);
	  found = false;
	  REQUIRE((*stringIter) == 
		  utility::stream::getStringArg(buffer, name, length + 1, found));
	  REQUIRE(true == found);
	  stringIter++;
	  buffer.clear();
	  buffer.str(*stringIter);
	  found = false;
	  REQUIRE((*stringIter) == 
		  utility::stream::getStringArg(buffer, name, length + 1, found));
	  REQUIRE(true == found);
	  stringIter++;
	}
      }
    }  
  }
}


SCENARIO("getStringArg throws when the stream string is greater than the length argument",
	 "[utility],[stream]"){

  LOG(INFO) << "Test " << ++testNumber << ": Errors Expected";

  const std::string name("testString");
  bool found;
  std::istringstream buffer;
  std::vector<std::string> bufferQueue;
  std::vector<int> lengthQueue;
  bufferQueue.emplace_back("\"\"");
  bufferQueue.emplace_back("\'\'");
  lengthQueue.emplace_back(0);
  bufferQueue.emplace_back("\"test\"");
  bufferQueue.emplace_back("\'test\'");
  lengthQueue.emplace_back(4);
  bufferQueue.emplace_back("\"test\'s\"");
  bufferQueue.emplace_back("\'test\"s\'");
  lengthQueue.emplace_back(6);
  bufferQueue.emplace_back("\"test/s\"");
  bufferQueue.emplace_back("\'test/s\'");
  lengthQueue.emplace_back(6);

  GIVEN("a stream with a valid string argument"){

    WHEN("passed to getStringArg with length argument less than string length without found argument"){
      THEN("throws"){
	auto stringIter = bufferQueue.begin();
	for (int length : lengthQueue){
	  buffer.clear();
	  buffer.str(*stringIter);
	  REQUIRE_THROWS(utility::stream::getStringArg(buffer, name, length - 1));
	  stringIter++;
	  buffer.clear();
	  buffer.str(*stringIter);
	  REQUIRE_THROWS(utility::stream::getStringArg(buffer, name, length - 1));
	  stringIter++;
	}
      }
    }
  
    WHEN("passed to getStringArg with length argument less than string length and found argument"){
      THEN("throws"){
	auto stringIter = bufferQueue.begin();
	for (int length : lengthQueue){
	  buffer.clear();
	  buffer.str(*stringIter);
	  REQUIRE_THROWS(utility::stream::getStringArg(buffer, name, length - 1, found));
	  stringIter++;
	  buffer.clear();
	  buffer.str(*stringIter);
	  REQUIRE_THROWS(utility::stream::getStringArg(buffer, name, length - 1, found));
	  stringIter++;
	}
      }
    }
  }
}

SCENARIO("getStringArg throws when the stream string is invalid",
	 "[utility],[stream]"){

  LOG(INFO) << "Test " << ++testNumber << ": Errors Expected";

  const std::string name("testString");
  bool found;
  std::istringstream buffer;
  std::vector<std::string> bufferQueue;
  std::vector<int> lengthQueue;
  bufferQueue.emplace_back("\"   "); //unmatched quote
  bufferQueue.emplace_back("\'   ");
  lengthQueue.emplace_back(4);
  bufferQueue.emplace_back("\"   \'"); //mismatched quote
  bufferQueue.emplace_back("\'   \"");
  lengthQueue.emplace_back(5);

  GIVEN("a stream with an invalid string argument"){

    WHEN("passed to getStringArg with length argument less than string length without found argument"){
      THEN("throws"){
	auto stringIter = bufferQueue.begin();
	for (int length : lengthQueue){
	  buffer.clear();
	  buffer.str(*stringIter);
	  REQUIRE_THROWS(utility::stream::getStringArg(buffer, name, length));
	  stringIter++;
	  buffer.clear();
	  buffer.str(*stringIter);
	  REQUIRE_THROWS(utility::stream::getStringArg(buffer, name, length));
	  stringIter++;
	}
      }
    }

    WHEN("passed to getStringArg with length argument less than string length and found argument"){
      THEN("throws"){
	auto stringIter = bufferQueue.begin();
	for (int length : lengthQueue){
	  buffer.clear();
	  buffer.str(*stringIter);
	  REQUIRE_THROWS(utility::stream::getStringArg(buffer, name, length, found));
	  stringIter++;
	  buffer.clear();
	  buffer.str(*stringIter);
	  REQUIRE_THROWS(utility::stream::getStringArg(buffer, name, length, found));
	  stringIter++;
	}
      }
    }
  }
}

SCENARIO("mandatory getStringArg throws for streams with badbit",
         "[utility],[stream]"){
  LOG(INFO) << "Test " << ++testNumber << ": Errors Expected";

  const std::string name("testString");
  GIVEN("empty stream"){
    std::istringstream buffer;

    WHEN("passed to getStringArg without found argument"){
      THEN("will throw"){
	REQUIRE_THROWS(utility::stream::getStringArg(buffer, name, 10));
      }
    }
  }
}

SCENARIO("optional getStringArg sets found flag to false for streams with badbit",
         "[utility],[stream]"){
  LOG(INFO) << "Test " << ++testNumber << ": No Errors Expected";

  const std::string name("testString");
  bool found = true;
  GIVEN("empty stream"){
    std::istringstream buffer;

    WHEN("passed to getStringArg with found argument"){
      THEN("will set found flag to false"){
	found = true;
	REQUIRE_NOTHROW(utility::stream::getStringArg(buffer, name, 10, found));
	REQUIRE(found == false);
      }
    }
  }
}

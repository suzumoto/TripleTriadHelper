add_library(TripleTriad STATIC CardData.cpp Rules.cpp Board.cpp)
target_include_directories(TripleTriad PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(TripleTriad STATIC CardData.cpp Rules.cpp Board.cpp io-util.cpp)
target_include_directories(TripleTriad PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(main.exe main.cpp)
target_link_libraries(main.exe TripleTriad)
add_executable(analysis.exe analysis.cpp)
target_link_libraries(analysis.exe TripleTriad)

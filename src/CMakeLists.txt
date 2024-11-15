cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(cataboard

  main.cpp
  ActionLog.cpp
  ActionLogItem.cpp
  CategoryInfo.cpp
  CategoryList.cpp
  DataEntry.cpp
  Directory.cpp
  Member.cpp
  MemberList.cpp
  Note.cpp
  NoteList.cpp
  Task.cpp
  TaskBoard.cpp

  Commands.cpp
  _command_index.cpp
)

target_link_libraries(cataboard libstdc++fs.a)
cmake_minimum_required(VERSION 3.5)

project(database)

# automatisk brug af moc uic, og rcc filer.
set(CMAKE_AUTOMOC ON) #.moc filer
set(CMAKE_AUTOUIC ON)  # .ui filer
set(CMAKE_AUTORCC ON)  # .qrc filer

# finder de pakker som er brug for at blive anvendt
find_package(Qt5 COMPONENTS Core Gui Sql REQUIRED)

# includerer directories hvor header filerne er fundet
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# viser filer der skal kompileres
add_executable(${PROJECT_NAME}
    database.cpp
    database.h
    testafdatabase.cpp
    # eventuelt tilføj flere filer
)

# Link af diverse anvnedte biblioteker
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Sql)

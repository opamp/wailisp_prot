set(MAINSRC
  ${SRC_DIR}/main.cpp
  ${SRC_DIR}/MainWindow.cpp
  ${SRC_DIR}/CentralWidget.cpp
  ${SRC_DIR}/Console.cpp
  ${SRC_DIR}/TextEditConsole.cpp
  ${SRC_DIR}/FileEdit.cpp
  ${SRC_DIR}/CodeEditors.cpp
  ${SRC_DIR}/LispRunner.cpp
  ${SRC_DIR}/LispPort.cpp)


add_executable(${EXEFILE_NAME} ${MAINSRC})
target_link_libraries(${EXEFILE_NAME} PRIVATE Qt6::Widgets ${GUILE3_LIBRARIES})

set_target_properties(${EXEFILE_NAME} PROPERTIES
  # Set c++ standard
  CXX_STANDARD 17
  # Do you want to use custom compiler extensions?
  CXX_EXTENSION ON)

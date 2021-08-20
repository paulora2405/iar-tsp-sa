include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME}.out
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ingest.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/simulated_annealing.cpp
)

target_link_libraries(${PROJECT_NAME}.out)
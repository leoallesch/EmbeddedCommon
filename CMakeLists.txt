# Specify the minimum CMake version required
cmake_minimum_required(VERSION 3.16)

# Define the component
idf_component_register(
    SRCS "src/Event.c"
         "src/EventSubscription.c"
         "src/LinkedList.c"
         "src/Timer.c"
    INCLUDE_DIRS "include" # No include directory
)
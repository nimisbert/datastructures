# Author : Nicolas Misbert
# Notes  :
# CMakeLists.txt to compile code from the book and some examples

cmake_minimum_required(VERSION 3.22.1)

project( algorithm_in_C )

include_directories( include ${catkin_INCLUDE_DIRS} )

file( GLOB_RECURSE algorithm_in_C_HEADERS include/*.h )
file( GLOB_RECURSE algorithm_in_C_SOURCES src/*.c )
file( GLOB_RECURSE algorithm_in_C_EXAMPLE examples/*.c)

add_library(
    calgo SHARED
    src/sll.c
    src/dll.c
    src/cll.c
    src/stack.c
    src/queue.c
    src/set.c
    src/chtbl.c
    src/bitree.c
    src/bistree.c
    src/heap.c
    src/graph.c
    src/issort.c
    src/qksort.c
)

#Chapitre 2 : Manipulation de pointeur
add_executable(main_ptr examples/main_ptr.c)

#Chapitre 3 : Recursions
add_executable(main_rec examples/main_rec.c)

#Chapitre 5 :
## Listes simplements chainees 
add_executable(main_sll examples/main_sll.c)
target_link_libraries(main_sll calgo)
add_dependencies(main_sll calgo)
## Listes circulaires simplement chainees
add_executable(main_cll examples/main_cll.c)
target_link_libraries(main_cll calgo)
add_dependencies(main_cll calgo)

#Chapitre 6 : 
## Piles (LIFO)
add_executable(main_stack examples/main_stack.c)
target_link_libraries(main_stack calgo)
add_dependencies(main_stack calgo)
## Files (FIFO)
add_executable(main_queue examples/main_queue.c)
target_link_libraries(main_queue calgo)
add_dependencies(main_queue calgo)
## Exemple Files : Event Queue
add_executable(main_events examples/main_events.c)
target_link_libraries(main_events calgo)
add_dependencies(main_events calgo)

#Chapitre 7 : 
## Sets
add_executable(main_set examples/main_set.c)
target_link_libraries(main_set calgo)
add_dependencies(main_set calgo)

#Chapitre 10:
## Heap & Priority Queue
add_executable(main_tri_postal examples/main_tri_postal.c)
target_link_libraries(main_tri_postal calgo)
add_dependencies(main_tri_postal calgo)

#Chapitre 11:
## Graph
### BFS example 
add_executable(main_net_hops examples/main_net_hops.c)
target_link_libraries(main_net_hops calgo)
add_dependencies(main_net_hops calgo)
### DFS example 
add_executable(main_tri_topo examples/main_tri_topo.c)
target_link_libraries(main_tri_topo calgo)
add_dependencies(main_tri_topo calgo)
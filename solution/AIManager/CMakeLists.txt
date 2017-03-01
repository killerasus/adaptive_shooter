# AIManager CMakeLists.txt

add_library(AIManager STATIC
  "../src/AIManager/AIAgent.h"
  "../src/AIManager/AIAgent.cpp"
  "../src/AIManager/AIManager.h"
  "../src/AIManager/AIManager.cpp"
  "../src/AIManager/PlayerModel.h"
  "../src/AIManager/PlayerModel.cpp"
  "../src/AIManager/Trait.h"
)

target_include_directories(AIManager PUBLIC ../src/AIManager)

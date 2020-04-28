#pragma once

namespace pac_man {
enum class direction : int32_t { right, down, left, up, none };
}

namespace pac_man::data {
enum class entity { player, blinky, inky, pinky, clyde };
//enum class pickup { cherry, strawberry, orange, bell, apple, grape, wand, key };
}  // namespace pac_man::data
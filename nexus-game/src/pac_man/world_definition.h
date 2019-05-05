#pragma once
#include "world_cell.h"
#include "world_model.h"

namespace pac_man::data {
const auto size = nx::vector2i(28, 31);
const auto content = R"(
xxxxxxxxxxxxxxxxxxxxxxxxxxxx
x............xx............x
x.xxxx.xxxxx.xx.xxxxx.xxxx.x
x*xxxx.xxxxx.xx.xxxxx.xxxx*x
x.xxxx.xxxxx.xx.xxxxx.xxxx.x
x..........................x
x.xxxx.xx.xxxxxxxx.xx.xxxx.x
x.xxxx.xx.xxxxxxxx.xx.xxxx.x
x......xx....xx....xx......x
xxxxxx.xxxxx xx xxxxx.xxxxxx
xxxxxx.xxxxx xx xxxxx.xxxxxx
xxxxxx.xx          xx.xxxxxx
xxxxxx.xx xxxxxxxx xx.xxxxxx
xxxxxx.xx x      x xx.xxxxxx
xxxxxx.xx x      x xx.xxxxxx
p     .   x      x   .     p
xxxxxx.xx x      x xx.xxxxxx
xxxxxx.xx xxxxxxxx xx.xxxxxx
xxxxxx.xx          xx.xxxxxx
xxxxxx.xx xxxxxxxx xx.xxxxxx
xxxxxx.xx xxxxxxxx xx.xxxxxx
x............xx............x
x.xxxx.xxxxx.xx.xxxxx.xxxx.x
x.xxxx.xxxxx.xx.xxxxx.xxxx.x
x*..xx.......__.......xx..*x
xxx.xx.xx.xxxxxxxx.xx.xx.xxx
xxx.xx.xx.xxxxxxxx.xx.xx.xxx
x......xx....xx....xx......x
x.xxxxxxxxxx.xx.xxxxxxxxxx.x
x.xxxxxxxxxx.xx.xxxxxxxxxx.x
x..........................x
xxxxxxxxxxxxxxxxxxxxxxxxxxxx
)";
}  // namespace pac_man::data

namespace pac_man::model {
std::unique_ptr<world> get_default_world() {
	const auto cell_count = data::size.x * data::size.y;
	std::vector<cell> cells;
	cells.reserve(cell_count);
	for (int y = 0; y < data::size.y; ++y) {
		for (int x = 0; x < data::size.x; ++x) {
			const auto index = y * data::size.x + x;
			const auto element = data::content[index + 2];

			switch (element) {
				case 'x':
					cells.emplace_back(cell{nx::vector2i(x, y), cell_content::wall});
					break;
				case '\n':
					// don't add cells for newline chars
					break;
				default:
					cells.emplace_back(cell{nx::vector2i(x, y), std::optional<cell_content>()});
					break;
			}
		}
	}

	return std::make_unique<model::world>(std::move(cells), data::size);
}
}  // namespace pac_man::model

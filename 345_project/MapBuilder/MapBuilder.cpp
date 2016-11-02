#include "MapBuilder.h"

void MapBuilder::createNewMap(int x, int y) {
	{
		map = new Map(x, y);
	}
}

Map* MapBuilder::getMap() {
	return map;
}
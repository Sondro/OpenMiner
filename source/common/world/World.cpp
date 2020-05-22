/*
 * =====================================================================================
 *
 *  OpenMiner
 *
 *  Copyright (C) 2018-2020 Unarelith, Quentin Bazin <openminer@unarelith.net>
 *  Copyright (C) 2019-2020 the OpenMiner contributors (see CONTRIBUTORS.md)
 *
 *  This file is part of OpenMiner.
 *
 *  OpenMiner is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  OpenMiner is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with OpenMiner; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 *
 * =====================================================================================
 */
#include <glm/gtc/matrix_transform.hpp>

#include <gk/resource/ResourceHandler.hpp>

#include "EngineConfig.hpp"
#include "World.hpp"

bool World::isReloadRequested = false;

Chunk *World::getChunkAtBlockPos(int x, int y, int z) const {
	return getChunk(
		(x & -CHUNK_WIDTH)  / CHUNK_WIDTH,
		(y & -CHUNK_DEPTH)  / CHUNK_DEPTH,
		(z & -CHUNK_HEIGHT) / CHUNK_HEIGHT
	);
}

BlockData *World::getBlockData(int x, int y, int z) const {
	Chunk *chunk = getChunkAtBlockPos(x, y, z);
	if (chunk)
		return chunk->getBlockData(x & (CHUNK_WIDTH - 1), y & (CHUNK_DEPTH - 1), z & (CHUNK_HEIGHT - 1));

	return nullptr;
}

BlockData *World::addBlockData(int x, int y, int z, int inventoryWidth, int inventoryHeight) const {
	Chunk *chunk = getChunkAtBlockPos(x, y, z);
	if (chunk)
		return chunk->addBlockData(x & (CHUNK_WIDTH - 1), y & (CHUNK_DEPTH - 1), z & (CHUNK_HEIGHT - 1), inventoryWidth, inventoryHeight);

	return nullptr;
}

u16 World::getBlock(int x, int y, int z) const {
	Chunk *chunk = getChunkAtBlockPos(x, y, z);
	if (chunk)
		return chunk->getBlock(x & (CHUNK_WIDTH - 1), y & (CHUNK_DEPTH - 1), z & (CHUNK_HEIGHT - 1));

	return 0;
}

void World::setBlock(int x, int y, int z, u16 id) const {
	Chunk *chunk = getChunkAtBlockPos(x, y, z);
	if (chunk)
		chunk->setBlock(x & (CHUNK_WIDTH - 1), y & (CHUNK_DEPTH - 1), z & (CHUNK_HEIGHT - 1), id);
}

u16 World::getData(int x, int y, int z) const {
	Chunk *chunk = getChunkAtBlockPos(x, y, z);
	if (chunk)
		return chunk->getData(x & (CHUNK_WIDTH - 1), y & (CHUNK_DEPTH - 1), z & (CHUNK_HEIGHT - 1));

	return 0;
}

void World::setData(int x, int y, int z, u16 data) const {
	Chunk *chunk = getChunkAtBlockPos(x, y, z);
	if (chunk)
		chunk->setData(x & (CHUNK_WIDTH - 1), y & (CHUNK_DEPTH - 1), z & (CHUNK_HEIGHT - 1), data);
}

// Please update 'docs/lua-api-cpp.md' if you change this
void World::initUsertype(sol::state &lua) {
	lua.new_usertype<World>("World",
		"get_block", &World::getBlock,
		"set_block", &World::setBlock,

		"get_data", &World::getData,
		"set_data", &World::setData,

		"get_block_data", &World::getBlockData,
		"add_block_data", &World::addBlockData
	);
}


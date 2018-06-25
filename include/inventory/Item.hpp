/*
 * =====================================================================================
 *
 *       Filename:  Item.hpp
 *
 *    Description:
 *
 *        Created:  23/06/2018 22:29:41
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef ITEM_HPP_
#define ITEM_HPP_

#include "Types.hpp"

class Item {
	public:
		Item(u32 id, u32 textureID, bool m_isBlock = false);

		u32 id() const { return m_id; }
		u32 textureID() const { return m_textureID; }

		bool isBlock() const { return m_isBlock; }

	private:
		u32 m_id = 0;
		u32 m_textureID = 0;

		bool m_isBlock;
};

#endif // ITEM_HPP_

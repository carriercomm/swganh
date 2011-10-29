/*
 This file is part of SWGANH. For more information, visit http://swganh.com
 
 Copyright (c) 2006 - 2011 The SWG:ANH Team

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SWGANH_OBJECT_CELL_CELL_H_
#define SWGANH_OBJECT_CELL_CELL_H_

#include "swganh/object/object.h"

namespace swganh {
namespace object {
namespace cell {

class Cell : public swganh::object::Object {

public:
    // SCLT
    virtual uint32_t GetType() const { return Cell::type; }
    const static uint32_t type = 0x53434c54;

    /**
    *   @brief Gets the current cell number
    *   @returns cell number
    */
    uint32_t GetCell();

    /**
    *   @brief sets the current cell number
    *   @param cell number
    */
    void SetCell(uint32_t cell_number);

    virtual boost::optional<swganh::messages::BaselinesMessage> GetBaseline3(void);
    virtual boost::optional<swganh::messages::BaselinesMessage> GetBaseline6(void);

private:
    uint32_t cell_number_;			//update 3

};

}}} // swganh::object::cell

#endif //SWGANH_OBJECT_CELL_CELL_H_

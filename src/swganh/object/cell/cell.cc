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


#include "swganh/object/cell/cell.h"
#include "swganh/object/cell/cell_message_builder.h"

using namespace std;
using namespace swganh::object;
using namespace swganh::object::cell;
using namespace swganh::messages;
using boost::optional;

void Cell::SetCell(uint32_t cell_number) {
    boost::lock_guard<boost::recursive_mutex> lock(mutex_);
    cell_number_ = cell_number;
    CellMessageBuilder::BuildCellIdDeltas(this);
}

uint32_t Cell::GetCell(void) {
    boost::lock_guard<boost::recursive_mutex> lock(mutex_);
    return cell_number_;
}

optional<BaselinesMessage> Cell::GetBaseline3(void)
{
    return CellMessageBuilder::GetBaseline3(this);
}

optional<BaselinesMessage> Cell::GetBaseline6(void)
{
    return CellMessageBuilder::GetBaseline6(this);
}
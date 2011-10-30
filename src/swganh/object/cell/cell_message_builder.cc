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

#include "cell_message_builder.h"

using namespace swganh::object::cell;
using namespace swganh::messages;

void CellMessageBuilder::BuildCellIdDeltas(Cell* cell)
{
    if(cell->HasObservers())
    {
        auto message = cell->CreateDeltasMessage(Object::VIEW_3, 4);
        message.data.write<uint32_t>(cell->cell_number_);
        cell->AddDeltasUpdate(message);
    }
}

boost::optional<BaselinesMessage> CellMessageBuilder::GetBaseline3(Cell* cell)
{
    auto message = cell->CreateBaselinesMessage(Object::VIEW_3, 5);
    message.data.append(cell->Object::GetBaseline3().get().data);
    message.data.write<uint32_t>(0); // Unknown
    message.data.write<uint32_t>(0); // Unknown
    return boost::optional<BaselinesMessage>();
}

boost::optional<BaselinesMessage> CellMessageBuilder::GetBaseline6(Cell* cell)
{
    auto message = cell->CreateBaselinesMessage(Object::VIEW_6, 5);
    message.data.append(cell->Object::GetBaseline6().get().data);
    message.data.write<uint32_t>(cell->cell_number_);
    return boost::optional<BaselinesMessage>();
}

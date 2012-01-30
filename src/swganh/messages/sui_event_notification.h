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

#ifndef SWGANH_MESSAGES_SUI_EVENT_NOTIFICATION_H_
#define SWGANH_MESSAGES_SUI_EVENT_NOTIFICATION_H_

#include <cstdint>
#include <iostream>
#include "anh/byte_buffer.h"
#include "swganh/messages/base_swg_message.h"

namespace swganh {
namespace messages {
    
struct SuiEventNotification : public swganh::messages::BaseSwgMessage<SuiEventNotification> {
    static uint16_t opcount() { return 0x04; }
    static uint32_t opcode() { return 0x092D3564; }

    uint32_t window_id;
    uint32_t cancel;
    std::list<std::pair<std::wstring, std::wstring>> options;


    void onSerialize(anh::ByteBuffer& buffer) const {

    }

    void onDeserialize(anh::ByteBuffer buffer) {
        window_id = buffer.read<uint32_t>();
        cancel = buffer.read<uint32_t>();

        uint32_t count = buffer.read<uint32_t>();

        if(count)
        {
            buffer.read<uint32_t>();
            std::wstring str = buffer.read<std::wstring>();
            std::wstring str2 = buffer.read<std::wstring>();
            std::cout << "First: " << std::string(str.begin(), str.end()) << std::endl;
            std::cout << "Second: " << std::string(str2.begin(), str2.end()) << std::endl;
        }
        else
        {
            std::wstring str = buffer.read<std::wstring>();
            std::cout << "First: " << std::string(str.begin(), str.end()) << std::endl;
        }
    }
};

}}  // namespace swganh::messages

#endif  // SWGANH_MESSAGES_SUI_EVENT_NOTIFICATION_H_


/*
 This file is part of SWGANH. For more information, visit http://swganh.com
 
 Copyright (c) 2006 - 2012 The SWG:ANH Team

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

#ifndef SWGANH_SUI_SUI_WINDOW_H_
#define SWGANH_SUI_SUI_WINDOW_H_

#include <string>
#include <memory>

#include "anh/byte_buffer.h"
#include "swganh/object/object.h"

namespace swganh {
namespace sui {

class SuiWindow
{
public:
    SuiWindow(void);
    ~SuiWindow(void);

    virtual void onSerialize(anh::ByteBuffer& message);

    uint64_t getId() { return id_; }
    std::string getUIScript() { return ui_script_; }

    void setElement(std::string, std::wstring);
    void setHeader();

private:
    uint64_t id_;
    std::string ui_script_;
    std::shared_ptr<swganh::object::Object> owner_;
    float max_distance_;
};

}} // namespace swganh::sui

#endif // SWGANH_SUI_SUI_WINDOW_H_
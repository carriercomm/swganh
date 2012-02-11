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
#include <functional>
#include <tuple>

#include "anh/byte_buffer.h"
#include "swganh/object/object.h"

namespace swganh {
namespace sui {

typedef std::tuple<std::string, std::string, std::wstring> BodyElement;
typedef std::vector<BodyElement> BodyElements;

typedef std::pair<std::string, std::string> ReturnElement;
typedef std::vector<ReturnElement> ReturnElements;

class SuiService;
class SuiWindow
{
public:
    SuiWindow(void);
    ~SuiWindow(void);

    virtual void onSerialize(anh::ByteBuffer& message);

    uint32_t GetId() { return id_; }

    std::string GetUiScript() { return ui_script_; }
	void SetUiScript(std::string ui_script) { ui_script_ = ui_script; }

	float GetMaxDistance() { return max_distance_; }
	void SetMaxDistance(float max_distance) { max_distance_ = max_distance; }

	void SetCancelCallback(std::function<void()> callback) { cancel_callback_ = callback; }
	void SetSuccessCallback(std::function<void(ReturnElements)> callback) { success_callback_ = callback; }

	void SetHandlerString(std::string handler) { handler_ = handler; }
	std::string GetHandlerString(void) { return handler_; }

    void AddReturnElement(std::string, std::string);
	void SetBodyElement(std::string object, std::string variable, std::wstring value);

private:
	friend SuiService;

	void SetId(uint32_t id) { id_ = id; }
	void OnEventNotification();

    uint32_t id_;
    std::string ui_script_;
	std::string handler_;
    std::shared_ptr<swganh::object::Object> owner_;
	ReturnElements return_elements_;
	BodyElements elements_;
    float max_distance_;

	std::function<void(ReturnElements)> success_callback_;
	std::function<void()> cancel_callback_;
};

}} // namespace swganh::sui

#endif // SWGANH_SUI_SUI_WINDOW_H_
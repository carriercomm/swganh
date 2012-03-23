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

#include "swganh/sui/form/list_box.h"

namespace swganh {
namespace sui {
namespace form {

ListBox::ListBox()
{
	SetUiScript("Script.listBox");
}

ListBox::ListBox(std::wstring caption, std::wstring prompt)
	: caption_(caption)
	, prompt_(prompt)
{
	SetUiScript("Script.listBox");
}

ListBox::~ListBox()
{
}

void ListBox::AddItem(std::wstring index, std::wstring value)
{
	auto i = items_.find(index);
	if(i == items_.end())
		items_.insert(std::pair<std::wstring, std::wstring>(index, value));
	else
		i->second = value;
}

void ListBox::RemoveItem(std::wstring index)
{
	auto i = items_.find(index);
	if(i != items_.end())
	{
		items_.erase(i);
	}
}

messages::SuiCreatePageMessage ListBox::onCreate(void)
{
	messages::SuiCreatePageMessage message = SuiWindow::onCreate();
	message.AddPropertyResult("List.lstList", "SelectedRow");
	message.AddPropertyValue("bg.caption.lblTitle", "Text", caption_);
	message.AddPropertyValue("Prompt.lblPrompt", "Text", prompt_);
	
	message.AddPropertyContainer("List.dataList");
	std::for_each(items_.begin(), items_.end(), [&message](const std::pair<std::wstring, std::wstring>& item) {
		message.AddPropertyHeader("List.dataList", "Name", item.first);
		message.AddPropertyValue(std::string("List.dataList.") + std::string(item.first.begin(), item.first.end()), "Text", item.second);
	});

	return message;
}

}}} // namespace swganh::sui::form
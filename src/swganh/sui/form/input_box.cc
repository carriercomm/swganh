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

#include "input_box.h"
#include <glog\logging.h>

namespace swganh {
namespace sui {
namespace form {

InputBox::InputBox(std::wstring title, std::wstring caption)
	: title_(title)
	, caption_(caption)
{
	SetUiScript("Script.inputBox");
}

InputBox::~InputBox(void)
{
}

messages::SuiCreatePageMessage InputBox::onCreate()
{
	messages::SuiCreatePageMessage message = SuiWindow::onCreate();
	message.AddPropertyResult("txtInput", "LocalText");
	message.AddPropertyValue("inputBox", "MinimumSize", L"900,400");
	message.AddPropertyValue("cmbInput", "Visible", L"false");
	message.AddPropertyValue("cmbInput", "Enabled", L"false");
	message.AddPropertyValue("bg.caption.lblTitle", "Text", std::wstring(title_.begin(), title_.end()));
	message.AddPropertyValue("Prompt.lblPrompt", "Text", std::wstring(caption_.begin(), caption_.end()));
	return message;
}

void InputBox::SetTitle(std::wstring title)
{
	title_ = title;
}

void InputBox::SetCaption(std::wstring caption)
{
	caption_ = caption;
}

}}} // swganh::sui::form
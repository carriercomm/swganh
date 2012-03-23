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

#include "sui_window.h"

#include <glog/logging.h>

#include "anh/crc.h"

namespace swganh {
namespace sui {

SuiWindow::SuiWindow(void)
	 : id_(0)
	 , ui_script_("")
	 , handler_("")
	 , max_distance_(0)
	 , target_id_ (0)
{
}

SuiWindow::~SuiWindow(void)
{
}

messages::SuiCreatePageMessage SuiWindow::onCreate(void)
{
	messages::SuiCreatePageMessage message;
	message.id = id_;
	message.ui_script = ui_script_;
	message.handler = handler_;
	message.max_distance = max_distance_;
	message.target_id = target_id_;
	return message;
}

}} // swganh::sui
// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE
#pragma once

#include <swganh_core/simulation/player_view_box.h>
#include <swganh_core/object/permissions/default_permission.h>

using namespace swganh::simulation;
using namespace swganh::object;

static double VIEWING_RANGE = 128.0f;

PlayerViewBox::PlayerViewBox(std::shared_ptr<Object> player)
	: Object()
	, player_(player)
{
	SetInSnapshot(true); // We don't actually spawn this object.
	SetDatabasePersisted(false); // We don't store it.
	SetCollidable(true);
	SetCollisionBoxSize((float)VIEWING_RANGE * 2.0f,(float) VIEWING_RANGE * 2.0f);
	SetTemplate("server/anh_view_box");
	SetPosition(player->GetPosition());
	SetObjectId(player->GetObjectId() + 16);
	SetPermissions(std::make_shared<swganh::object::DefaultPermission>());
}

PlayerViewBox::~PlayerViewBox()
{
}


void PlayerViewBox::OnCollisionEnter(std::shared_ptr<Object> collider)
{
	// Add collided object to view.
	auto& controller = player_->GetController();
	if(controller != nullptr)
	{
		if(collider->IsInSnapshot() == false)
		{
			//std::cout << "Creating [ " << collider->GetTemplate() << ":" << collider->GetObjectId(); 
			//if(collider->GetContainer() != nullptr)
			//	std::cout << ":" << collider->GetContainer()->GetObjectId();
			//std::cout << "] for ";
			//std::wcout << player_->GetCustomName() << std::endl;
			collider->Subscribe(controller);
			collider->SendCreateByCrc(controller);
			collider->CreateBaselines(controller);
		}

		/**collider->ViewObjects(nullptr, 0, true, [=](std::shared_ptr<swganh::object::Object> child) {
			if(collider->IsInSnapshot() == false)
			{
				child->Subscribe(controller);
				child->SendCreateByCrc(controller);
				child->CreateBaselines(controller);
			}
		});*/
	}
}

void PlayerViewBox::OnCollisionLeave(std::shared_ptr<Object> collider)
{
	// Remove collided object from view.
	auto& controller = player_->GetController();
	if(controller != nullptr)
	{
		if(collider->IsInSnapshot() == false)
		{
			//std::cout << "Destroying [ " << collider->GetTemplate() << ":" << collider->GetObjectId(); 
			//if(collider->GetContainer() != nullptr)
			//	std::cout << ":" << collider->GetContainer()->GetObjectId();
			//std::cout << "] for ";
			//std::wcout << player_->GetCustomName() << std::endl;
			collider->SendDestroy(controller);
			collider->Unsubscribe(controller);
		}

		/**collider->ViewObjects(nullptr, 0, true, [=](std::shared_ptr<swganh::object::Object> child) {
			if(collider->IsInSnapshot() == false)
			{
				child->SendDestroy(controller);
				child->Unsubscribe(controller);
			}
		});*/
	}
}
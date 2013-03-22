// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "world_container.h"

#include "swganh_core/simulation/spatial_provider_interface.h"

using namespace swganh::simulation;

void WorldContainer::AddObject(std::shared_ptr<swganh::object::Object> requester, std::shared_ptr<swganh::object::Object> newObject, int32_t arrangement_id) 
{ 
	std::cout << "WorldContainer::AddObject" << std::endl; 
	spatial_provider_->AddObject(newObject, arrangement_id);
}
	
void WorldContainer::RemoveObject(std::shared_ptr<swganh::object::Object> requester, std::shared_ptr<swganh::object::Object> oldObject) 
{ 
	std::cout << "WorldContainer::RemoveObject" << std::endl; 
	spatial_provider_->RemoveObject(oldObject);
}
	
void WorldContainer::TransferObject(std::shared_ptr<swganh::object::Object> requester, std::shared_ptr<swganh::object::Object> object, std::shared_ptr<ContainerInterface> newContainer, glm::vec3 position, int32_t arrangement_id) 
{ 
	std::cout << "WorldContainer::TransferObject" << std::endl; 
}
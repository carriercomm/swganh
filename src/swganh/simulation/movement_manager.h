
#ifndef SWGANH_SIMULATION_MOVEMENT_MANAGER_H_
#define SWGANH_SIMULATION_MOVEMENT_MANAGER_H_

#include <memory>

#include <tbb/concurrent_unordered_map.h>

#include "swganh/messages/obj_controller_message.h"

namespace anh {
    class EventDispatcher;
namespace event_dispatcher {
    class EventDispatcherInterface;
}}  // namespace anh::event_dispatcher

namespace swganh {
namespace object {
    class Object;
    class ObjectController;
}}  // namespace swganh::object

namespace swganh {
namespace simulation {

    class MovementManager
    {
    public:
        explicit MovementManager(anh::EventDispatcher* event_dispatcher);

        void HandleDataTransform(
            const std::shared_ptr<swganh::object::ObjectController>&, 
            const swganh::messages::ObjControllerMessage&);

        void HandleDataTransformWithParent(
            const std::shared_ptr<swganh::object::ObjectController>&, 
            const swganh::messages::ObjControllerMessage&);
        
        void SendDataTransformMessage(const std::shared_ptr<swganh::object::Object>& object, uint32_t unknown = 0x0000000B);
        void SendUpdateDataTransformMessage(const std::shared_ptr<swganh::object::Object>& object);
        
        void SendDataTransformWithParentMessage(const std::shared_ptr<swganh::object::Object>& object, uint32_t unknown = 0x0000000B);
        void SendUpdateDataTransformWithParentMessage(const std::shared_ptr<swganh::object::Object>& object);

    private:
        void RegisterEvents_(const std::shared_ptr<anh::event_dispatcher::EventDispatcherInterface>& event_dispatcher);
        void RegisterEvents(anh::EventDispatcher* event_dispatcher);

        bool ValidateCounter_(uint64_t object_id, uint32_t counter);

        typedef tbb::concurrent_unordered_map<
            uint64_t, uint32_t
        > UpdateCounterMap;

        UpdateCounterMap counter_map_;
    };

}}  // namespace swganh::simulation

#endif  // SWGANH_SIMULATION_MOVEMENT_MANAGER_H_

#include "EventBus.h"

EventBus::EventBus(){
    
}

void EventBus::Subscribe(EventType type, Layer* layer) {
    _subscribers[type].push_back(layer);
}

void EventBus::Unsubscribe(EventType type, Layer* layer) {
    auto it = std::find(_subscribers[type].begin(), _subscribers[type].end(), layer);

    if(it != _subscribers[type].end()) {
        _subscribers[type].erase(it);
    }
}

void EventBus::Notify(Event& event){
    if(event.HasBeenHandled()){
        return;
    }

    for(Layer* layer : _subscribers[event.GetEventType()]){
        layer->HandleEvent(event);

        if (event.HasBeenHandled()) break;

    }

    // This can be used to debug when an event has not been handled
    if (!event.HasBeenHandled())
    {
        std::cout << "Event has not been handled" << std::endl;
    }

    // std::cout << "=== End of Event Bus NOTIFY ===" << std::endl;

}
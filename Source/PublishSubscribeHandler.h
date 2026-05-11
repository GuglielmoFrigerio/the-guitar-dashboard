/*
  ==============================================================================

    PublishSubscribeHandler.h
    Created: 30 Dec 2022 1:37:25pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <functional>
#include <queue>

enum class PublishSubscribeEvent {
    SongStatusChanged
};

class PublishSubscribeHandler {
private:
    struct Item {
        PublishSubscribeEvent Event;
        std::uint64_t ContextData;        
    };

public:
    void subscribe(PublishSubscribeEvent event, std::function<void(PublishSubscribeEvent, std::uint64_t)> handler);
    void publish(PublishSubscribeEvent event, std::uint64_t contextData);
    void onTimer();
};
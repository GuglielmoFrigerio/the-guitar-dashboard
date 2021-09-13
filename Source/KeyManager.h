/*
  ==============================================================================

    KeyManager.h
    Created: 13 Sep 2021 1:37:10pm
    Author:  gugli

  ==============================================================================
*/

#pragma once
#include <functional>

class KeyManager
{
private:
    int m_primaryKeyCode;
    int m_aliasKeyCode;
    enum KeyState {
        Idle,
        Armed,
        Holding
    };

    KeyState m_keyState;

public:
    KeyManager(int primamryKeyCode, int aliasKeyCode);

    void keyPressed(int keyCode);
    void keyStateChanged(bool isKeyDown);

    std::function<void(bool)> onKeyPressed;
};

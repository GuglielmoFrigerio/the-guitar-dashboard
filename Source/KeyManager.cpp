/*
  ==============================================================================

    KeyManager.cpp
    Created: 13 Sep 2021 1:37:10pm
    Author:  gugli

  ==============================================================================
*/

#include "KeyManager.h"

KeyManager::KeyManager(int primamryKeyCode, int aliasKeyCode)
    :   m_primaryKeyCode(primamryKeyCode), m_aliasKeyCode(aliasKeyCode), m_keyState(Idle)
{
}

void KeyManager::keyPressed(int keyCode)
{
    if (keyCode != m_primaryKeyCode && keyCode != m_aliasKeyCode)
        m_keyState = Idle;
    else {
        if (m_keyState == Idle)
            m_keyState = Armed;
        else if (m_keyState == Armed) {
            if (onKeyPressed != nullptr)
                onKeyPressed(true);
            m_keyState = Holding;
        }
    }
}

void KeyManager::keyStateChanged(bool isKeyDown)
{
    if (!isKeyDown) {
        if (m_keyState == Armed) {
            if (onKeyPressed != nullptr)
                onKeyPressed(false);
        }
        m_keyState = Idle;
    }
}

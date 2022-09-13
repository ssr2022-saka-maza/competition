#include "ps4operation/Systemctl.hpp"

ps4operation::Systemctl::Systemctl(uint8_t childCapacity)
: _childCount(0), _children(nullptr), _state(State::moving), _lastValue(), _stateUpdateTime(0), childCapacity(childCapacity) {
    _children = new Resetable*[this->childCapacity];
    for (uint8_t i = 0; i < this->childCapacity; ++i) {
        _children[i] = nullptr;
    }
}

ps4operation::Systemctl::~Systemctl() {
    delete[] _children;
}

void ps4operation::Systemctl::reset() noexcept {
    for (uint8_t i = 0; i < _childCount; ++i) {
        _children[i]->reset();
    }
}

void ps4operation::Systemctl::addChild(Resetable * child) noexcept {
    if (_childCount < childCapacity) {
        _children[_childCount] = child;
        ++_childCount;
    }
}

void ps4operation::Systemctl::removeChild(Resetable * child) noexcept {
    for (uint8_t i = 0; i < _childCount; ++i) {
        if (_children[i] == child) {
            _children[i] = _children[_childCount - 1];
            _children[_childCount - 1] = nullptr;
            --_childCount;
            break;
        }
    }
}

void ps4operation::Systemctl::operate(const ssr::PS4Value & value) noexcept {
    bool square = value.square;
    bool ps = value.ps;
    bool otherwise = _lastValue != value;
    State newState = _state;
    switch (_state) {
        case State::moving:
            if (ps) {
                newState = State::stop;
                _lastValue = value;
            } else if (square) {
                newState = State::automate;
                _lastValue = value;
            } else if (otherwise) {
                newState = State::moving;
            }
            break;
        case State::stop:
            if (ps) {
                newState = State::stop;
                _lastValue = value;
            } else if (square) {
                newState = State::automate;
                _lastValue = value;
            } else if (otherwise) {
                newState = State::moving;
            }
            break;
        case State::automate:
            if (ps) {
                newState = State::stop;
                _lastValue = value;
            } else if (square) {
                newState = State::automate;
                _lastValue = value;
            } else if (otherwise) {
                newState = State::moving;
            }
            break;
    }
    if (newState != _state) {
        #ifdef ps4operation_verbose
        char buffer[256] = "";
        char * ptr = buffer;
        ptr += snprintf_P(ptr, 40, PSTR("[ps4operation::Systemctl] new state: "));
        switch (newState) {
            case State::moving:
                ptr += snprintf_P(ptr, 10, PSTR("moving"));
                break;
            case State::stop:
                ptr += snprintf_P(ptr, 10, PSTR("stop"));
                break;
            case State::automate:
                ptr += snprintf_P(ptr, 10, PSTR("automate"));
                break;
        }
        Serial.println(buffer);
        #endif /* ps4operation_verbose */
        _stateUpdateTime = millis();
        _state = newState;
    }
    switch (_state) {
        case State::moving:
            for (uint8_t i = 0; i < _childCount; ++i) {
                _children[i]->operate(value);
            }
            break;
        case State::stop:
            if (millis() - _stateUpdateTime > 1000) {
                reset();
            }
            break;
        case State::automate:
            uint64_t dt = (millis() - _stateUpdateTime) / 1000;
            ssr::PS4Value newValue = value;
            newValue.square = false;
            newValue.ps = false;
            /*
            0- 3: ハンドを閉じる
            3- 6: ハンドを回転
            6- 9: ハンドを開く
            9-12: ハンドを閉じながらハンドを回転
            */
            if (dt < 3) {
                newValue.r1 = true;
            } else if (dt < 6) {
                newValue.triangle = true;
            } else if (dt < 9) {
                newValue.l1 = true;
            } else if (dt < 12) {
                newValue.r1 = true;
                newValue.cross = true;
            }
            for (uint8_t i = 0; i < _childCount; ++i) {
                _children[i]->operate(newValue);
            }
            break;
    }
}

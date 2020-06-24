//
// Created by Pavel Bibichenko on 24.06.2020.
//

#ifndef ECOMPILER_EXTENSIONS_H
#define ECOMPILER_EXTENSIONS_H

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

#endif //ECOMPILER_EXTENSIONS_H

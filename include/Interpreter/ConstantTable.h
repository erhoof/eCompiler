//
// Created by Pavel Bibichenko on 21.06.2020.
//

#ifndef ECOMPILER_CONSTANTTABLE_H
#define ECOMPILER_CONSTANTTABLE_H

class ConstantTable {
public:
    static ConstantTable& instance();

    ConstantTable(const ConstantTable&) = delete;
    ConstantTable& operator=(const ConstantTable&) = delete;

    // Constant Table
    Constant* c_true;
    Constant* c_false;
private:
    ConstantTable();
};

#endif //ECOMPILER_CONSTANTTABLE_H

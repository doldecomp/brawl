#pragma once

#include <StaticAssert.h>
#include <types.h>

// Note: The name of this class is hypothesized and does not appear in the
// compiled code files. Its existence is inferred from the use of multiple
// inheritance in its derived classes.
class soNull {
// fix for bug in Clang fork not producing empty vtable.
// This is technically incorrect as it will make soNull
// always 4 bytes when the bug only affects multiple
// inheritance, however soNull is never used on it's own
// so this shouldn't be an issue (for now?)
#ifndef __MWERKS__
    int pad;
#endif
};

class soNullableInterface {
public:
    virtual bool isNull() const = 0;
};

class soNullable {
public:
    soNullable() { m_isNull = false; }
    soNullable(bool isNull) { m_isNull = isNull; }
    virtual bool isNull() const { return m_isNull; }
    void setNull(bool is_null) { m_isNull = is_null; }

    bool m_isNull;
};
static_assert(sizeof(soNullable) == 8, "Class is wrong size!");

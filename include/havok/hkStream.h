#pragma once

#include <havok/hkBase.h>

// Abstract byte source. Only skip() is out-of-line; the rest are trivial defaults.
struct hkStreamReader : hkReferencedObject {
    virtual bool isOk() const = 0;
    virtual int read(void* buf, int nbytes) = 0;
    virtual int skip(int nbytes);
    virtual bool markSupported() const;
    virtual hkResult setMark(int markLimit);
    virtual hkResult rewindToMark();
    virtual bool seekTellSupported() const;
    virtual hkResult seek(int offset, int whence);
    virtual int tell() const;
};

// Abstract byte sink.
struct hkStreamWriter : hkReferencedObject {
    virtual bool isOk() const = 0;
    virtual int write(const void* buf, int nbytes) = 0;
    virtual void flush() = 0;
    virtual bool seekTellSupported() const;
    virtual hkResult seek(int offset, int whence);
    virtual int tell() const;
};

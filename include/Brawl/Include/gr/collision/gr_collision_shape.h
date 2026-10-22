#pragma once

#include <StaticAssert.h>
#include <mt/mt_coll2d.h>
#include <mt/mt_vector.h>
#include <types.h>

class grCollShape {
public:
    virtual void init();
    virtual int getType() const;
    virtual void getAABBox(clAABBox2D& aabBox);
    virtual void setDownPos(const Vec2f& downPos);
    virtual void setLeftPos(const Vec2f& leftPos);
    virtual void setRightPos(const Vec2f& rightPos);
    virtual void setCenterPos(const Vec2f& centerPos);
    virtual void setTopPos(const Vec2f& topPos);
    virtual Vec2f getCenterPos() const;
    virtual Vec2f getDownPos() const;
    virtual Vec2f getLeftPos() const;
    virtual Vec2f getRightPos() const;
    virtual Vec2f getTopPos() const;
    virtual void move(const Vec2f& displacement);
    virtual void set(grCollShape& collShape);
    virtual float getHeight() const;
    virtual float getWidth() const;
    virtual void test();
    virtual void updateAABBox();
    virtual void setLR(const Vec2f& centerPos, const Vec2f& left, const Vec2f& right);
    virtual void setUD(const Vec2f& centerPos, const Vec2f& up, const Vec2f& down);
    virtual void setLR(const Vec2f& left, const Vec2f& right);
    virtual void modifyDownY(float downY);

    static const float gUnk805a2a20;
    static const float gUnk805a2a24;
    static const float gUnk805a2a28;
};
static_assert(sizeof(grCollShape) == 4, "Class is wrong size!");

#pragma once

#include <StaticAssert.h>
#include <gr/collision/gr_collision_shape.h>
#include <types.h>

class grCollShapeRhombus : public grCollShape {
    clRhombus2D m_rhombus;
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
};
static_assert(sizeof(grCollShapeRhombus) == 60, "Class is wrong size!");

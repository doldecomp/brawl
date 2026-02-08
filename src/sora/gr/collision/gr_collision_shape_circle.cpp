#include <gr/collision/gr_collision_shape_circle.h>
#include <types.h>

void grCollShapeCircle::init() {
    m_circle.m_radius = 0.0f;
    m_circle.m_centerPos.m_y = 0.0f;
    m_circle.m_centerPos.m_x = 0.0f;
}

void grCollShapeCircle::set(grCollShape& orig) {
    const grCollShapeCircle& o = static_cast<const grCollShapeCircle&>(orig);
    m_circle.m_centerPos = o.m_circle.m_centerPos;
    m_circle.m_radius = o.m_circle.m_radius;
}

void grCollShapeCircle::setDownPos(const Vec2f& downPos) {
    Vec2f pos(downPos.m_x, downPos.m_y + m_circle.m_radius + gUnk805a2a20);
    m_circle.m_centerPos = pos;
}

void grCollShapeCircle::setRightPos(const Vec2f& rightPos) {
    Vec2f pos(rightPos.m_x - gUnk805a2a20 - m_circle.m_radius, rightPos.m_y);
    m_circle.m_centerPos = pos;
}

void grCollShapeCircle::setLeftPos(const Vec2f& leftPos) {
    Vec2f pos(leftPos.m_x + gUnk805a2a20 + m_circle.m_radius, leftPos.m_y);
    m_circle.m_centerPos = pos;
}

void grCollShapeCircle::setCenterPos(const Vec2f& centerPos) {
    Vec2f pos(centerPos.m_x, centerPos.m_y);
    m_circle.m_centerPos = pos;
}

void grCollShapeCircle::setTopPos(const Vec2f& topPos) {
    Vec2f pos(topPos.m_x, topPos.m_y - gUnk805a2a20 - m_circle.m_radius);
    m_circle.m_centerPos = pos;
}

void grCollShapeCircle::setLR(const Vec2f& centerPos, const Vec2f& left, const Vec2f& right) {
    float rx;
    float lx;
    float cx;
    float upper;
    float lower;

    cx = centerPos.m_x;
    rx = right.m_x;
    lx = left.m_x;
    upper = rx - cx;
    lower = cx - lx;
    m_circle.m_centerPos = centerPos;
    m_circle.m_radius = (upper > lower) ? lower : upper;
}

void grCollShapeCircle::setLR(const Vec2f& left, const Vec2f& right) {
    Vec2f v;
    Vec2f::copy(v, ((left + right) / 2.0f));
    setLR(v, left, right);
}

void grCollShapeCircle::setUD(const Vec2f& centerPos, const Vec2f& up, const Vec2f& down) {
    float uy;
    float dy;
    float cy;
    float upper;
    float lower;

    cy = centerPos.m_y;
    uy = up.m_y;
    dy = down.m_y;
    upper = uy - cy;
    lower = cy - dy;
    m_circle.m_centerPos = centerPos;
    m_circle.m_radius = (upper > lower) ? lower : upper;
}

void grCollShapeCircle::updateAABBox() { }

void grCollShapeCircle::test() { }

void grCollShapeCircle::modifyDownY(float downY) {
    float diameter = m_circle.m_centerPos.m_y + m_circle.m_radius - downY;
    if (diameter > 0) {
        const float rad = 0.5f * diameter;
        m_circle.m_radius = rad;
        m_circle.m_centerPos.m_y = downY + rad;
    }
}

float grCollShapeCircle::getWidth() const {
    return 2.0f * m_circle.m_radius;
}

float grCollShapeCircle::getHeight() const {
    return 2.0f * m_circle.m_radius;
}

void grCollShapeCircle::move(const Vec2f& displacement) {
    m_circle.m_centerPos.m_x += displacement.m_x;
    m_circle.m_centerPos.m_y += displacement.m_y;
}

Vec2f grCollShapeCircle::getTopPos() const {
    Vec2f pos(m_circle.m_centerPos.m_x, m_circle.m_centerPos.m_y + m_circle.m_radius);
    return pos;
}

Vec2f grCollShapeCircle::getRightPos() const {
    Vec2f pos(m_circle.m_centerPos.m_x + m_circle.m_radius, m_circle.m_centerPos.m_y);
    return pos;
}

Vec2f grCollShapeCircle::getLeftPos() const {
    Vec2f pos(m_circle.m_centerPos.m_x - m_circle.m_radius, m_circle.m_centerPos.m_y);
    return pos;
}

Vec2f grCollShapeCircle::getDownPos() const {
    Vec2f pos(m_circle.m_centerPos.m_x, m_circle.m_centerPos.m_y - m_circle.m_radius);
    return pos;
}

Vec2f grCollShapeCircle::getCenterPos() const {
    Vec2f pos(m_circle.m_centerPos.m_x, m_circle.m_centerPos.m_y);
    return pos;
}

void grCollShapeCircle::getAABBox(clAABBox2D& aabBox) {
    m_circle.getAABBox(aabBox);
}

int grCollShapeCircle::getType() const {
    return 0;
}

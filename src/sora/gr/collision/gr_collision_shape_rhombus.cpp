#include <gr/collision/gr_collision_shape_rhombus.h>
#include <math.h>
#include <types.h>

void grCollShapeRhombus::init() {
    m_rhombus.m_centerPos.m_x = gUnk805a2a24;
    m_rhombus.m_centerPos.m_y = gUnk805a2a24;

    m_rhombus.m_upPos.m_x = gUnk805a2a24;
    m_rhombus.m_upPos.m_y = gUnk805a2a24;

    m_rhombus.m_downPos.m_x = gUnk805a2a24;
    m_rhombus.m_downPos.m_y = gUnk805a2a24;

    m_rhombus.m_leftPos.m_x = gUnk805a2a24;
    m_rhombus.m_leftPos.m_y = gUnk805a2a24;

    m_rhombus.m_rightPos.m_x = gUnk805a2a24;
    m_rhombus.m_rightPos.m_y = gUnk805a2a24;

    m_rhombus.m_aabBox.m_unk1 = gUnk805a2a24;
    m_rhombus.m_aabBox.m_unk2 = gUnk805a2a24;
    m_rhombus.m_aabBox.m_unk3 = gUnk805a2a24;
    m_rhombus.m_aabBox.m_unk4 = gUnk805a2a24;
}

void grCollShapeRhombus::set(grCollShape& orig) {
    m_rhombus = static_cast<const grCollShapeRhombus&>(orig).m_rhombus;
}

void grCollShapeRhombus::move(const Vec2f& displacement) {
    m_rhombus.move(displacement);
}

void grCollShapeRhombus::setDownPos(const Vec2f& downPos) {
    Vec2f newDownPos(downPos.m_x, gUnk805a2a28 + downPos.m_y);
    Vec2f disp;
    Vec2f::copy(disp, newDownPos - m_rhombus.m_downPos);
    m_rhombus.move(disp);
}

void grCollShapeRhombus::setRightPos(const Vec2f& rightPos) {
    Vec2f newRightPos(rightPos.m_x - gUnk805a2a28, rightPos.m_y);
    Vec2f disp;
    Vec2f::copy(disp, newRightPos - m_rhombus.m_rightPos);
    m_rhombus.move(disp);
}

void grCollShapeRhombus::setLeftPos(const Vec2f& leftPos) {
    Vec2f newLeftPos(gUnk805a2a28 + leftPos.m_x, leftPos.m_y);
    Vec2f disp;
    Vec2f::copy(disp, newLeftPos - m_rhombus.m_leftPos);
    m_rhombus.move(disp);
}

void grCollShapeRhombus::setCenterPos(const Vec2f& centerPos) {
    Vec2f newCenterPos(centerPos.m_x, centerPos.m_y - gUnk805a2a28);
    Vec2f disp;
    Vec2f::copy(disp, newCenterPos - m_rhombus.m_centerPos);
    m_rhombus.move(disp);
}

void grCollShapeRhombus::setTopPos(const Vec2f& topPos) {
    Vec2f newTopPos(topPos.m_x, topPos.m_y - gUnk805a2a28);
    Vec2f disp;
    Vec2f::copy(disp, newTopPos - m_rhombus.m_upPos);
    m_rhombus.move(disp);
}

void grCollShapeRhombus::setLR(const Vec2f& centerPos, const Vec2f& left, const Vec2f& right) {
    m_rhombus.m_centerPos.m_x = centerPos.m_x;
    m_rhombus.m_centerPos.m_y = centerPos.m_y;

    m_rhombus.m_leftPos.m_x = gUnk805a2a28 + left.m_x;
    m_rhombus.m_leftPos.m_y = centerPos.m_y;

    m_rhombus.m_rightPos.m_x = right.m_x - gUnk805a2a28;
    m_rhombus.m_rightPos.m_y = centerPos.m_y;

    m_rhombus.m_upPos.m_x = centerPos.m_x;
    m_rhombus.m_downPos.m_x = centerPos.m_x;
}

void grCollShapeRhombus::setLR(const Vec2f& left, const Vec2f& right) {
    const float dx = m_rhombus.m_rightPos.m_x - m_rhombus.m_leftPos.m_x;
    float frac = fabs(m_rhombus.m_centerPos.m_x - m_rhombus.m_leftPos.m_x);
    frac /= dx;
    const float f0 = frac * (right.m_x - left.m_x);

    Vec2f center;
    center.m_x = left.m_x + f0;
    center.m_y = m_rhombus.m_centerPos.m_y;
    setLR(center, left, right);
}

void grCollShapeRhombus::setUD(const Vec2f& centerPos, const Vec2f& up, const Vec2f& down) {
    m_rhombus.m_centerPos.m_x = centerPos.m_x;
    m_rhombus.m_centerPos.m_y = centerPos.m_y;

    m_rhombus.m_upPos.m_x = centerPos.m_x;
    m_rhombus.m_upPos.m_y = up.m_y - gUnk805a2a28;

    m_rhombus.m_downPos.m_x = centerPos.m_x;
    m_rhombus.m_downPos.m_y = gUnk805a2a28 + down.m_y;

    m_rhombus.m_rightPos.m_y = centerPos.m_y;
    m_rhombus.m_leftPos.m_y = centerPos.m_y;
}

void grCollShapeRhombus::modifyDownY(float downY) {
    if (m_rhombus.m_centerPos.m_y > downY)
        m_rhombus.m_downPos.m_y = downY;
}

void grCollShapeRhombus::test() { }

#ifdef MATCHING
// These functions may have had some debugging purpose at one point,
// but they amount to no-ops in the release build and are only included
// to match the binary.
static inline int isFinite(float f) {
    int res = 1;
    u32 i;
    __memcpy(&i, &f, 4);
    if ((i >> 23 & 0xFF) == 0xFF)
        res = 0;
    return res;
}

static inline void checkFinite(float lx, const clAABBox2D& aabBox) {
    if (isFinite((lx))) {
        // The argument passed here (and below) doesn't matter
        static_cast<void>(isFinite(0));
    }
    if (isFinite((aabBox.m_unk3))) {
        static_cast<void>(isFinite(0));
    }
}
#endif

void grCollShapeRhombus::updateAABBox() {
    float upY, rightX, downY, leftX;

    leftX = m_rhombus.m_leftPos.m_x;
    downY = m_rhombus.m_downPos.m_y;
    upY = m_rhombus.m_upPos.m_y;
    rightX = m_rhombus.m_rightPos.m_x;

    m_rhombus.m_aabBox.m_unk1 = leftX;
    m_rhombus.m_aabBox.m_unk2 = downY;
    m_rhombus.m_aabBox.m_unk3 = rightX;
    m_rhombus.m_aabBox.m_unk4 = upY;

#ifdef MATCHING
    // Effectively dead code
    checkFinite(m_rhombus.m_leftPos.m_x, m_rhombus.m_aabBox);
#endif
}

float grCollShapeRhombus::getWidth() const {
    return m_rhombus.m_rightPos.m_x - m_rhombus.m_leftPos.m_x;
}

float grCollShapeRhombus::getHeight() const {
    return m_rhombus.m_upPos.m_y - m_rhombus.m_downPos.m_y;
}

Vec2f grCollShapeRhombus::getTopPos() const {
    return m_rhombus.m_upPos;
}

Vec2f grCollShapeRhombus::getRightPos() const {
    return m_rhombus.m_rightPos;
}

Vec2f grCollShapeRhombus::getLeftPos() const {
    return m_rhombus.m_leftPos;
}

Vec2f grCollShapeRhombus::getDownPos() const {
    return m_rhombus.m_downPos;
}

Vec2f grCollShapeRhombus::getCenterPos() const {
    return m_rhombus.m_centerPos;
}

void grCollShapeRhombus::getAABBox(clAABBox2D& aabBox) {
    float downY, leftX, upY, rightX;

    leftX = m_rhombus.m_leftPos.m_x;
    downY = m_rhombus.m_downPos.m_y;
    aabBox.m_unk1 = leftX;
    aabBox.m_unk2 = downY;

    upY = m_rhombus.m_upPos.m_y;
    rightX = m_rhombus.m_rightPos.m_x;
    aabBox.m_unk3 = rightX;
    aabBox.m_unk4 = upY;

#ifdef MATCHING
    // Effectively dead code
    checkFinite(leftX, aabBox);
#endif
}

int grCollShapeRhombus::getType() const {
    return 2;
}

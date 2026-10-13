#pragma once

#include <StaticAssert.h>
#include <types.h>

class soLinkModule;
class soLinkConnection;

class soLinkNode {
    char _0x0[0xC];
    soLinkConnection* m_connection;
    soLinkModule* m_linkModule;
};
static_assert(0x14 == sizeof(soLinkNode), "Class is wrong size!");

class soLinkConnection {
    char _0x0[0x4];
    soLinkNode m_node1;
    soLinkNode m_node2;
    union {
        struct {
            u32 : 21;
            bool m_attributeReferenceParentScale : 1;
            bool m_attributeReferenceParentShake : 1;
            bool m_attributeReferenceParentStop : 1;
            u8 m_id : 7;
            bool : 1;
        };
        struct {
            u32 m_attribute : 24;
            u8 : 7;
            bool : 1;
        };
    };

    char _0x30[0x4];

public:
    enum Attribute {
        Attribute_Reference_Parent_Stop = 0x0,
        Attribute_Reference_Parent_Shake = 0x1,
        Attribute_Reference_Parent_Scale = 0x2,

        Attribute_Reference_Parent_Unknown_4 = 0x4,

        Attribute_Reference_Parent_Visibility = 0x7,

        Attribute_Reference_Parent_Power_Up = 0xA, // glow
    };
};
static_assert(0x34 == sizeof(soLinkConnection), "Class is wrong size!");

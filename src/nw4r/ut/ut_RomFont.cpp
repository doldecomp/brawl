#include <nw4r/ut/ut_RomFont.h>

namespace nw4r {
namespace ut {

u16 RomFont::mFontEncode = 0xFFFF;

RomFont::RomFont() : mFontHeader(nullptr), mAlternateChar('?') {
    mDefaultWidths.left = 0;
    mDefaultWidths.glyphWidth = 0;
    mDefaultWidths.charWidth = 0;
}

RomFont::~RomFont() { }

int RomFont::GetWidth() const {
    return mFontHeader->width;
}

int RomFont::GetHeight() const {
    return GetAscent() + GetDescent();
}

int RomFont::GetAscent() const {
    return mFontHeader->ascent;
}

int RomFont::GetDescent() const {
    return mFontHeader->descent;
}

int RomFont::GetBaselinePos() const {
    return mFontHeader->ascent;
}

int RomFont::GetCellHeight() const {
    return mFontHeader->cellHeight;
}

int RomFont::GetCellWidth() const {
    return mFontHeader->cellWidth;
}

int RomFont::GetMaxCharWidth() const {
    return mFontHeader->width;
}

Font::Type RomFont::GetType() const {
    return TYPE_ROM;
}

GXTexFmt RomFont::GetTextureFormat() const {
    return GX_TF_I4;
}

int RomFont::GetLineFeed() const {
    return mFontHeader->leading;
}

CharWidths RomFont::GetDefaultCharWidths() const {
    return mDefaultWidths;
}

void RomFont::SetDefaultCharWidths(const CharWidths& rWidths) {
    mDefaultWidths = rWidths;
}

namespace detail {

inline bool IsSjisSingleByte(u16 ch) { // Name unknown
    if (ch > 0xFF) {
        return false;
    }
    return (ch >= 0x20 && ch <= 0x7E) || (ch >= 0xA1 && ch <= 0xDF);
}

inline bool IsSjisDoubleByte(u16 ch) { // Name unknown
    u8 trail = ch;
    u8 lead = ch >> 8;
    return lead >= 0x81 && lead <= 0x98 && trail >= 0x40 && trail <= 0xFC;
}

} // namespace detail

inline u16 RomFont::HandleUndefinedChar(u16 ch) const {
    // Requires ANSI or SJIS ROM font encoding.
    bool valid;
    switch (mFontEncode) {
        case OS_FONT_ENCODE_ANSI:
            valid = ch >= 0x20 && ch <= 0xFF;
            break;
        case OS_FONT_ENCODE_SJIS:
            valid = detail::IsSjisSingleByte(ch) || detail::IsSjisDoubleByte(ch);
            break;
    }
    return valid ? ch : mAlternateChar;
}

bool RomFont::SetAlternateChar(u16 ch) {
    const u16 old = mAlternateChar;
    mAlternateChar = 0xFFFF;
    const u16 alternate = HandleUndefinedChar(ch);
    if (alternate != 0xFFFF) {
        mAlternateChar = ch;
        return true;
    }
    mAlternateChar = old;
    return false;
}

void RomFont::SetLineFeed(int lf) {
    mFontHeader->leading = lf;
}

inline void RomFont::MakeCharPtr(char* pBuffer, u16 ch) const {
    u8 high = ch >> 8;
    if (high == 0) {
        pBuffer[0] = ch;
        pBuffer[1] = 0;
    } else {
        pBuffer[0] = high;
        pBuffer[1] = ch;
        pBuffer[2] = 0;
    }
}

int RomFont::GetCharWidth(u16 ch) const {
    u32 width;
    char buffer[CHAR_PTR_BUFFER_SIZE];
    MakeCharPtr(buffer, HandleUndefinedChar(ch));
    OSGetFontWidth(buffer, &width);
    return width;
}

CharWidths RomFont::GetCharWidths(u16 ch) const {
    int width = GetCharWidth(ch);
    CharWidths widths;
    widths.left = 0;
    widths.glyphWidth = width;
    widths.charWidth = width;
    return widths;
}

void RomFont::GetGlyph(Glyph* pGlyph, u16 ch) const {
    void* texture;
    u32 x, y, width;
    char buffer[CHAR_PTR_BUFFER_SIZE];
    MakeCharPtr(buffer, HandleUndefinedChar(ch));
    OSGetFontTexture(buffer, &texture, &x, &y, &width);
    pGlyph->pTexture = texture;
    pGlyph->widths.left = 0;
    pGlyph->widths.glyphWidth = width;
    pGlyph->widths.charWidth = width;
    pGlyph->height = mFontHeader->cellHeight;
    pGlyph->texFormat = GX_TF_I4;
    pGlyph->texWidth = mFontHeader->sheetWidth;
    pGlyph->texHeight = mFontHeader->sheetHeight;
    pGlyph->cellX = x;
    pGlyph->cellY = y;
}

FontEncoding RomFont::GetEncoding() const {
    switch (mFontEncode) {
        case OS_FONT_ENCODE_ANSI:
            return FONT_ENCODING_CP1252;
        case OS_FONT_ENCODE_SJIS:
            return FONT_ENCODING_SJIS;
        default:
            return FONT_ENCODING_CP1252;
    }
}

} // namespace ut
} // namespace nw4r

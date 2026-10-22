#pragma once

#include <StaticAssert.h>
#include <ms/ms_char_writer.h>
#include <nw4r/ut/ut_Rect.h>
#include <types.h>

namespace ms {
  template <class T>
  class TextWriterBase : public CharWriter {
   public:
    enum DrawFlag {
      DRAWFLAG_ALIGN_TEXT_BASELINE = 0,
      DRAWFLAG_ALIGN_TEXT_CENTER = (1 << 0),
      DRAWFLAG_ALIGN_TEXT_RIGHT = (1 << 1),

      DRAWFLAG_ALIGN_H_BASELINE = 0,
      DRAWFLAG_ALIGN_H_CENTER = (1 << 4),
      DRAWFLAG_ALIGN_H_RIGHT = (1 << 5),

      DRAWFLAG_ALIGN_V_BASELINE = 0,
      DRAWFLAG_ALIGN_V_CENTER = (1 << 8),
      DRAWFLAG_ALIGN_V_TOP = (1 << 9),
    };

    TextWriterBase();
    ~TextWriterBase();

    /* Layout / spacing */
    void SetLineHeight(float height);
    float GetLineHeight() const;
    void SetLineSpace(float space);
    void SetCharSpace(float space);
    float GetCharSpace() const;
    int GetTabWidth() const;
    void SetDrawFlag(u32 flags);  // arg width matches nw4r; unverified for ms
    u32 GetDrawFlag() const;

    /* Measurement */
    float CalcLineWidth(const T* str, int len);
    float CalcStringWidth(const T* str, int len) const;
    void CalcStringRect(nw4r::ut::Rect* out, const T* str, int len) const;

    /* Drawing */
    float Print(const T* str, int len);

   private:
    // Fields past ms::CharWriter; left as the spacer the stub already carried.
    char _112[48];
  };
}  // namespace ms

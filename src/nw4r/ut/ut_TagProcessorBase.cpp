#include <nw4r/ut/ut_Rect.h>
#include <nw4r/ut/ut_TextWriterBase.h>

#include <nw4r/ut/ut_TagProcessorBase.h>

namespace nw4r {
namespace ut {

template <typename T>
TagProcessorBase<T>::TagProcessorBase() { }

template <typename T>
TagProcessorBase<T>::~TagProcessorBase() { }

template <typename T>
void TagProcessorBase<T>::ProcessLinefeed(ContextType* pCtx) {
    TextWriterBase<T>* writer = pCtx->writer;
    f32 x = pCtx->x;
    f32 y = writer->GetCursorY() + writer->GetLineHeight();
    writer->SetCursor(x, y);
}

template <typename T>
void TagProcessorBase<T>::ProcessTab(ContextType* pCtx) {
    TextWriterBase<T>* writer = pCtx->writer;
    int tabWidth = writer->GetTabWidth();
    if (tabWidth > 0) {
        f32 charWidth = writer->IsWidthFixed() ? writer->GetFixedWidth() : writer->GetFontWidth();
        f32 offset = writer->GetCursorX() - pCtx->x;
        f32 tabSize = tabWidth * charWidth;
        int tab = static_cast<int>(offset / tabSize) + 1;
        writer->SetCursorX(pCtx->x + tabSize * tab);
    }
}

template <typename T>
typename TagProcessorBase<T>::Operation TagProcessorBase<T>::Process(u16 ch, ContextType* pCtx) {
    switch (ch) {
        case '\n':
            ProcessLinefeed(pCtx);
            return OPERATION_NEXT_LINE;
        case '\t':
            ProcessTab(pCtx);
            return OPERATION_NO_CHAR_SPACE;
        default:
            return OPERATION_DEFAULT;
    }
}

template <typename T>
typename TagProcessorBase<T>::Operation TagProcessorBase<T>::CalcRect(Rect* pRect, u16 ch, ContextType* pCtx) {
    switch (ch) {
        case '\n': {
            TextWriterBase<T>* writer = pCtx->writer;
            pRect->right = writer->GetCursorX();
            pRect->top = writer->GetCursorY();
            ProcessLinefeed(pCtx);
            pRect->left = writer->GetCursorX();
            pRect->bottom = writer->GetCursorY() + pCtx->writer->GetFontHeight();
            pRect->Normalize();
            return OPERATION_NEXT_LINE;
        }
        case '\t': {
            TextWriterBase<T>* writer = pCtx->writer;
            pRect->left = writer->GetCursorX();
            ProcessTab(pCtx);
            pRect->right = writer->GetCursorX();
            pRect->top = writer->GetCursorY();
            pRect->bottom = pRect->top + writer->GetFontHeight();
            pRect->Normalize();
            return OPERATION_NO_CHAR_SPACE;
        }
        default:
            return OPERATION_DEFAULT;
    }
}

template class TagProcessorBase<char>;
template class TagProcessorBase<wchar_t>;

} // namespace ut
} // namespace nw4r

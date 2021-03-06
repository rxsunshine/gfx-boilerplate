#pragma once

#include <vector>
#include <string>

#include "text.hpp"
#include "gl_texture.hpp"
#include "gl_prim.hpp"

#include <glm/vec2.hpp>
#include "wrapped_gl.h"

struct GL_GlyphAtlas {
    GLuint tex;
    GlyphAtlas atlas;
};

struct GL_Glyph {
    GLuint atlas;
    glm::vec2 tl;
    glm::vec2 br;
    glm::vec2 pos;
    GlyphMetrics metrics;
};

struct GL_FontContext {
    std::vector<GL_GlyphAtlas> atlases;
    int size;
    FT_Face face;
};

struct GL_TextRenderer {
    GLuint atlasprog;
    GLint atlasprog_image;
    GLint atlasprog_tl;
    GLint atlasprog_br;
    GLint atlasprog_pos;
    GLint atlasprog_size;
    GLint atlasprog_res;

    Primative quad;

    glm::vec2 res;
};

struct GL_TextLayoutInfo {
    enum Align {
        A_Left,
        A_Center,
        A_Right,
    };

    float width = 0.0f;
    float height = 0.0f;
    Align align = A_Left;
    bool breakWord = false;
};

struct GL_TextLayout {
    std::vector<GL_Glyph> glyphs;
    glm::vec2 viewport {};
};

GL_GlyphAtlas GL_CreateGlyphAtlas(FT_Face face, int size, uint32_t codept);
void GL_DestroyGlyphAtlas(GL_GlyphAtlas& atlas);

GL_FontContext GL_CreateFontContext(FT_Face face, int size);
GL_Glyph GL_GetGlyph(GL_FontContext& ctx, uint32_t codept);
GL_TextLayout GL_GetGlyphString(
    GL_FontContext& ctx, std::string str, 
    const GL_TextLayoutInfo& info = {});
void GL_DestroyFontContext(GL_FontContext& ctx);

GL_TextRenderer GL_CreateTextRenderer();
void GL_DestroyTextRenderer(GL_TextRenderer& r);
void GL_DrawString(GL_TextRenderer& r, const GL_TextLayout& layout, glm::vec2 pos, glm::vec2 offset, float size);
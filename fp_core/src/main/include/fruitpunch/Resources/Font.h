/*
 * Font.h
 *
 *  Created on: 2012-06-13
 *      Author: leo
 */

#ifndef FONT_H_
#define FONT_H_

#include <boost/shared_ptr.hpp>
#include <fruitpunch/Graphics/Color.h>
#include <fruitpunch/Graphics/Image.h>
#include <fruitpunch/Resources/Resource.h>
#include <fruitpunch/Graphics/Vertex.h>
#include <ft2build.h>
#include <cairo/cairo.h>
#include <vector>
#include <string>


#include FT_FREETYPE_H

namespace fp_core {

class Font : public Resource {
public:
    typedef boost::shared_ptr<Font> ref;

    enum ALIGNMENT{ LEFT, CENTER, RIGHT};
    Font();
    Font(std::string path);
    virtual void load(std::string fullPath);

    /**
     * Converts the text string in the argument into a text image, taking into
     * account all the font properties of the current object.
     *
     * @param text
     * @return
     */
    boost::shared_ptr<Image> makeImage(std::string text);

    // ---------------------------------------------------------------------------
    // Getters
    // ---------------------------------------------------------------------------

    ALIGNMENT getAlignment() const;
    void setAlignment(ALIGNMENT alignment);
    bool isAntialias() const;
    void setAntialias(bool antialias);
    bool isBold() const;
    void setBold(bool bold);
    boost::shared_ptr<Color> getColor() const;
    void setColor(boost::shared_ptr<Color> color);
    bool isItalic() const;
    void setItalic(bool italic);
    int getLineSpacing() const;
    void setLineSpacing(int lineSpacing);
    int getSize() const;
    void setSize(int size);

    FT_Library getFtLibrary() const;
    FT_Face getFtFace() const;

private:
    FT_Library mLibrary;
    FT_Face mFace;
    int mSize;
    bool mAntialias;
    boost::shared_ptr<Color> mColor;
    ALIGNMENT mAlignment;
    int mLineSpacing;
    bool mBold;
    bool mItalic;
    void throwError(std::string path, int code);


    /**
     * Predicts what will be the minimum size – width and height - of the
     * image that will contain the text specified by the lines argument.
     *
     * @param lines
     * @param cairoContext
     * @return
     */
    point canvasDimensions(const std::vector<std::string>& lines,
        cairo_t * cairoContext);

    /**
     * Helper function for make image. Returns the x,y position of where the
     * drawing of a text line should start, given the contents of the line and
     * the line number.
     *
     * @param lineNumber
     * @param text
     * @param cairoContext
     * @param canvasSize
     * @return
     */
    point penPosition(int lineNumber, std::string text, cairo_t * cairoContext,
        point canvasSize);

    /**
     *  Loads the font characteristics, such as size and face, into the cairo
     *  context provided. Returns a cairo_font_face_t pointer that MUST be
     *  destroyed after its used to avoid memory leaks.
     */
    cairo_font_face_t * loadFontData(cairo_t * cairoContext);

};

} /* namespace fp_core */
#endif /* FONT_H_ */

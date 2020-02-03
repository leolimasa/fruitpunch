from fruitpunch.native.native_class import NativeClass
import libfp_core

class Font(NativeClass):
    '''
    Loads a font file as a resource. The font can then be used in a Text
    object.
    '''

    def __init__(self, font_file=None):
        NativeClass.__init__(self)
        
        if not font_file is None:
            self.store(libfp_core.Font(font_file))        

    # ---------------------------------------------------------------------
    # Native Methods
    # ---------------------------------------------------------------------

    def make_image(self, text):
        '''        
        Converts the text string in the argument into a text image, taking 
        into account all the font properties of the current object.
        '''

        return self.run_native("make_image", text)
    # _____________________________________________________________________

    def get_alignment(self):
        return self.run_native("get_alignment")
    # _____________________________________________________________________

    def set_alignment(self, alignment):
        return self.run_native("set_alignment", alignment)
    # _____________________________________________________________________

    def is_antialias(self):
        return self.run_native("is_antialias")
    # _____________________________________________________________________

    def set_antialias(self, antialias):
        return self.run_native("set_antialias", antialias)
    # _____________________________________________________________________

    def is_bold(self):
        return self.run_native("is_bold")
    # _____________________________________________________________________

    def set_bold(self, bold):
        return self.run_native("set_bold", bold)
    # _____________________________________________________________________

    def get_color(self):
        return self.run_native("get_color")
    # _____________________________________________________________________

    def set_color(self, color):
        return self.run_native("set_color", color)
    # _____________________________________________________________________

    def is_italic(self):
        return self.run_native("is_italic")
    # _____________________________________________________________________

    def set_italic(self, italic):
        return self.run_native("set_italic", italic)
    # _____________________________________________________________________

    def get_line_spacing(self):
        return self.run_native("get_line_spacing")
    # _____________________________________________________________________

    def set_line_spacing(self, lineSpacing):
        return self.run_native("set_line_spacing", lineSpacing)
    # _____________________________________________________________________

    def get_size(self):
        return self.run_native("get_size")
    # _____________________________________________________________________

    def set_size(self, size):
        return self.run_native("set_size", size)


    # ---------------------------------------------------------------------
    # Properties
    # ---------------------------------------------------------------------

    alignment = property(get_alignment, set_alignment)
    color = property(get_color, set_color)
    line_spacing = property(get_line_spacing, set_line_spacing)
    size = property(get_size, set_size)

NativeClass.class_map[libfp_core.Font] = Font
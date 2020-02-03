from fruitpunch.native.native_class import NativeClass
import libfp_core

class Color(NativeClass):
    '''   
    Represents a 32 bit color in the RGBA format     
    '''

    def __init__(self, color=None):
        NativeClass.__init__(self)
        
        if not color is None:
            self.store(libfp_core.Color(color))        

    # ---------------------------------------------------------------------
    # Native Methods
    # ---------------------------------------------------------------------

    # _____________________________________________________________________

    def from_long(self, hexColor):
        '''
        Creates a color using a hex value, or a long if you are hardcore enough.
        The hex value is in the format RGBA. 
        
        So the example below: 
        
        Color(0x00FF00FF)
        
        Will be r=0, g=255, b=0, a=255
        '''

        return self.run_native("from_long", hexColor)
    # _____________________________________________________________________

    def to_long(self):
        '''
        Converts the color to a ulong in the pixel order RGBA.
        '''

        return self.run_native("to_long")
    # _____________________________________________________________________

    def set_red(self, red):
        return self.run_native("set_red", red)
    # _____________________________________________________________________

    def set_green(self, green):
        return self.run_native("set_green", green)
    # _____________________________________________________________________

    def set_blue(self, blue):
        return self.run_native("set_blue", blue)
    # _____________________________________________________________________

    def set_alpha(self, alpha):
        return self.run_native("set_alpha", alpha)
    # _____________________________________________________________________

    def get_red(self):
        return self.run_native("get_red")
    # _____________________________________________________________________

    def get_green(self):
        return self.run_native("get_green")
    # _____________________________________________________________________

    def get_blue(self):
        return self.run_native("get_blue")
    # _____________________________________________________________________

    def get_alpha(self):
        return self.run_native("get_alpha")

    # ---------------------------------------------------------------------
    # Properties
    # ---------------------------------------------------------------------

    red = property(get_red, set_red)
    green = property(get_green, set_green)
    blue = property(get_blue, set_blue)
    alpha = property(get_alpha, set_alpha)
    
NativeClass.class_map[libfp_core.Color] = Color
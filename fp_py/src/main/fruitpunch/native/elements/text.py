import libfp_core
from fruitpunch.native.graphics.sprite import Sprite
from fruitpunch.native.native_class import NativeClass

class Text(Sprite):
    '''
    A text that can be drawn on a scene.     
    '''

    def __init__(self, text=None):
        NativeClass.__init__(self)
        
        if text is not None:
            self.store(libfp_core.Text(text))        

    # ---------------------------------------------------------------------
    # Native Methods
    # ---------------------------------------------------------------------

    def render_frame(self):
        '''
        Called by the scene every frame.
        '''
        
        return self.run_native("render_frame")
    # _____________________________________________________________________

    def update(self):
        '''
        Updates the internal sprite with a new texture of the text.
        '''

        return self.run_native("update")
    # _____________________________________________________________________

    def get_text(self):
        return self.run_native("get_text")
    # _____________________________________________________________________

    def get_font(self):
        return self.run_native("get_font")
    # _____________________________________________________________________

    def set_text(self, text):
        return self.run_native("set_text", text)
    # _____________________________________________________________________

    def set_font(self, font):
        return self.run_native("set_font", font)

    # ---------------------------------------------------------------------
    # Properties
    # ---------------------------------------------------------------------

    text = property(get_text, set_text)
    font = property(get_font, set_font)
    
NativeClass.class_map[libfp_core.Text] = Text
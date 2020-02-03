import libfp_core
from fruitpunch.native.graphics.primitive import Primitive
from fruitpunch.native.native_class import NativeClass
from fruitpunch.native.graphics.image import Image

class Sprite(Primitive):
    '''
    Creates an Element that will store an Image and display on the screen. 
    '''

    def __init__(self, image=None):
        NativeClass.__init__(self)
        
        if isinstance(image, NativeClass):
            self.store(libfp_core.Sprite(image._native))
        elif image is not None:
            self.store(libfp_core.Sprite(image))
        else:
            self.store(libfp_core.Sprite())
            
    def set_image_url(self, url):
        self._image_url = url
        self.image = Image(url)
        
    def get_image_url(self):
        return self._image_url
    
    def crop(self, x, y, width, height):
        return self.run_native("crop", x, y, width, height)
    
    image_url = property(get_image_url, set_image_url)
    
NativeClass.class_map[libfp_core.Sprite] = Sprite
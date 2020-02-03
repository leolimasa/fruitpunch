import libfp_core
from fruitpunch.native.native_class import NativeClass

class Image(NativeClass):
    '''
    
Represents the raw data of an Image file, and loads files from the hard drive.     
    
    
This class is able to automatically open a file from the hard drive, detect its extension, and create a char array that represents the image in a pixel format that OpenGl can understand.Currently, only the PNG file format is supported.     
    '''

    def __init__(self, image=None):
        NativeClass.__init__(self)
        
        if image is not None:
            self.store(libfp_core.Image(image))     

    # ---------------------------------------------------------------------
    # Native Methods
    # ---------------------------------------------------------------------

    # _____________________________________________________________________

    def pixel_at(self, row, col):
        '''
        Returns the color of the pixel at the coordinates specified.
        Images with different pixel orders will behave differently:
        
        RGBA: returns the color as it is 
        RGB: returns the color with a 1 alpha channel 
        MASK: sets all the three rgb components with the single byte value
        '''

        return self.run_native("pixel_at", row, col)
    
    # _____________________________________________________________________

    def fill(self, color):
        '''
        Converts the entire image to a solid color and sets the alpha 
        channel to a value from 0 to 255 according to the value of each pixel.
        '''

        return self.run_native("fill", color)
    # _____________________________________________________________________

    def set_pixel(self, row, col, color):
        '''
        Changes the color of the pixel at the specified coordinates. 
        '''

        return self.run_native("set_pixel", row, col, color)
    # _____________________________________________________________________

    def apply_alpha(self, image):
        '''
        
        Sets the alpha channel based on pixel data of another image. The target image must have the same width and height as this one.
        '''

        return self.run_native("apply_alpha", image)
    # _____________________________________________________________________

    def get_bytes_per_pixel(self):
        '''
        Returns the amount of bytes per pixel according to the image format 
        as follows:
        
        RGBA: 4 
        RGB: 3 
        MASK: 1
        '''

        return self.run_native("get_bytes_per_pixel")

    # _____________________________________________________________________

    def flip_y(self):
        '''
        reorders the pixels so that the Y is flipped
        '''

        return self.run_native("flip_y")
    # _____________________________________________________________________

    def copy_to(self, image):
        '''
        Copies the content of this image to another. This actually copies 
        the entire pixel array - not just a reference.
        '''

        return self.run_native("copy_to", image)

    # _____________________________________________________________________

    def get_height(self):
        return self.run_native("get_height")
    # _____________________________________________________________________

    def get_width(self):
        return self.run_native("get_width")
    # _____________________________________________________________________

    def get_image_id(self):
        return self.run_native("get_image_id")
    # _____________________________________________________________________

    def get_format(self):
        return self.run_native("get_format")

    # ---------------------------------------------------------------------
    # Properties
    # ---------------------------------------------------------------------

    bytes_per_pixel = property(get_bytes_per_pixel)
    height = property(get_height)
    width = property(get_width)
    image_id = property(get_image_id)
    format = property(get_format)

NativeClass.class_map[libfp_core.Image] = Image
import libfp_core
from fruitpunch.native.elements.element import Element
from fruitpunch.native.graphics.vertex import Point
from fruitpunch.native.native_class import NativeClass

class Scene(Element):
    '''
    Controls what is displayed on the screen and its underlying application logic.     
    
    In an MVC model, the Scene can be considered the Controller. Only one scene
    may be loaded at a time per application. Scenes are made up of Elements, 
    that attach to the scene's render event and therefore are able to 
    encapsulate fine grained application logic. 

    Abstract class.     
    '''

    def __init__(self):
        NativeClass.__init__(self)
        
        self.store(libfp_core.Scene())
        self.listen({"init": self.on_init,
                     "post_render": self.on_render})

    # ---------------------------------------------------------------------
    # Native Methods
    # ---------------------------------------------------------------------

    # _____________________________________________________________________

    def init(self):
        '''
        Called by the App to initialize the scene.
        '''

        return self.run_native("init")
    # _____________________________________________________________________

    def destroy(self):
        '''
        Called by the App when the scene is no longer needed
        '''

        return self.run_native("destroy")

    # _____________________________________________________________________

    def on_destroy(self):
        '''
        Called when the scene is destroyed.
        
        '''

        return self.run_native("on_destroy")
    # _____________________________________________________________________

    def get_pointer(self):
        '''
        Returns a point representing the current absolute position of the pointer on the screen
        '''
        #return Point.create_attached(self._native.get_pointer, self._native.set_pointer)
        return self.run_native("get_pointer")
    # _____________________________________________________________________

    def get_runtime(self):
        return self.run_native("get_runtime")
    # _____________________________________________________________________

    def get_window(self):
        return self.run_native("get_window")
    # _____________________________________________________________________

    def get_app(self):
        return self.run_native("get_app")
    # _____________________________________________________________________

    def get_width(self):
        return self.run_native("get_width")
    # _____________________________________________________________________

    def get_height(self):
        return self.run_native("get_height")
    # _____________________________________________________________________

    def set_app(self, app):
        return self.run_native("set_app", app)
    
    # _____________________________________________________________________
    
    def set_pointer(self, pointer):
        return self.run_native("set_pointer", pointer)

    # _____________________________________________________________________
    
    def set_pointer_x(self, x):
        return self.run_native("set_pointer_x", x)
    
    # _____________________________________________________________________
    
    def set_pointer_y(self, y):
        return self.run_native("set_pointer_y", y)
    
    # _____________________________________________________________________
    
    def on_init(self, e):
        pass

    # _____________________________________________________________________
    
    def on_render(self, e):
        pass


    # ---------------------------------------------------------------------
    # Properties
    # ---------------------------------------------------------------------

    pointer = property(get_pointer, set_pointer)
    runtime = property(get_runtime)
    window = property(get_window)
    app = property(get_app, set_app)
    width = property(get_width)
    height = property(get_height)
    
NativeClass.class_map[libfp_core.Scene] = Scene
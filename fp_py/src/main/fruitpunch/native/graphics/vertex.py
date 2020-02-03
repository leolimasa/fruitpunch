import libfp_core

class Vertex(libfp_core.Vertex):
    '''
    One vertex of a primitive.     
    
    Stores both the vertex position in space, and the uv coordinates of that
    particular vertex     
    '''
    pass

class Point:
    def __init__(self, x=0.0, y=0.0):
        self.owner_setter = None
        self.owner_getter = None
        self.x = x
        self.y = y
        
    @staticmethod
    def create_attached(getter, setter):
        p = Point()
        p.owner_setter = setter
        p.owner_getter = getter
        return p
    
    def get_x(self):
        if self.owner_getter is None:
            return self.x
        
        return self.owner_getter().x
    
    def get_y(self):
        if self.owner_getter is None:
            return self.y
        
        return self.owner_getter().y
    
    def set_x(self, value):
        if self.owner_setter is None:
            self.x = value
            return
        
        p = self.owner_getter()
        p.x = value
        self.owner_setter(p)
        
    def set_y(self, value):
        if self.owner_setter is None:
            self.y = value
            return
        
        p = self.owner_getter()
        p.y = value
        self.owner_setter(p)
        
    x = property(get_x, set_x)
    y = property(get_y, set_y)
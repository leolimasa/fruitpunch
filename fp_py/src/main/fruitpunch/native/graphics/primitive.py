
import libfp_core
from fruitpunch.native.graphics.vertex import Point
from fruitpunch.native.elements.element import Element
from fruitpunch.native.native_class import NativeClass

class Primitive(Element):
    '''
    A polygon that is able to receive events and be rendered to the screen.     
    
    A Primitive is the base class for everything that will be shown on the screen. It is formed by a list of vertices that will form a polygon, and a texture to be applied to that polygon.     
    '''

    def __init__(self):
        NativeClass.__init__(self)
        
        self.store(libfp_core.Primitive())        

    # ---------------------------------------------------------------------
    # Native Methods
    # ---------------------------------------------------------------------

    def add_vertex(self, vertex):
        '''
        Adds a new vertex that will be part of this primitive.
        
        '''
        return self.run_native("add_vertex", vertex)
    
    # _____________________________________________________________________

    def point_vector(self):
        '''
        Returns a vector of points with transformations applied.
        Goes through each vertex of the Primitive and transforms its position, 
        scale, and rotation with the values given to the Primitive. The original 
        vertex list is not changed. The result is just a copy of the vertices, 
        but with transformations applied.
        '''

        return self.run_native("point_vector")
    # _____________________________________________________________________

    def uv_point_vector(self):
        '''
        Returns a vector of points with all the vertices UV coordinates.
        
        Returns a point vector of all the uv point coordinates of every single 
        vertex of this primitive. The order of those points will match the 
        order of point_vector()
        '''

        return self.run_native("uv_point_vector")
    # _____________________________________________________________________

    def bounding_box(self):
        '''
        Calculates and returns the primitive's bounding box.
        Returns a box representing a bounding box around the primitive
        '''

        return self.run_native("bounding_box")
    # _____________________________________________________________________

    def boundaries(self):
        '''
        Returns the minimum and maximum values of X and Y of all vertices.
        
        Returns a vector of points that represent the minimum and maximum 
        vertex coordinates. This information can be used to create a bounding box. 
        Format: [min, max]
        '''

        return self.run_native("boundaries")
    # _____________________________________________________________________

    def transformed_bounds(self):
        '''
        The bounding box of all vertices after they have been transformed.
        '''

        return self.run_native("transformed_bounds")
    # _____________________________________________________________________

    def contains(self, p):
        '''
        Checks if a point is inside a primitive.
        
        Checks if the specified point is inside the area delimited by the 
        primitive. The area already accounts for transformations

        @return: true if the point is inside the area. False otherwise.
        '''

        return self.run_native("contains", p)
    # _____________________________________________________________________

    def vertices_center(self):
        '''
        Center of the primitive.
        Returns a point that represents the center of a bonding box that 
        encapsulates all the vertices in the primitive.
        '''

        return self.run_native("vertices_center")
    # _____________________________________________________________________

    def move(self, x, y):
        '''
        Increases the Primitive position by the specified value.
        
        '''

        return self.run_native("move", x, y)
    # _____________________________________________________________________

    def rotate(self, amount):
        '''
        Increases the Primitive rotation by the specified value.
        
        '''

        return self.run_native("rotate", amount)
    # _____________________________________________________________________

    def scale(self, x, y):
        '''
        Increases the Primitive scale by the specified value.
        '''

        self.run_native("scale", x, y)
    # _____________________________________________________________________

    def on_add(self):
        '''
        Element event. Adds the primitive to the window.
        '''

        return self.run_native("on_add")
    # _____________________________________________________________________

    def on_remove(self):
        '''
        Element event. Remove the primitive from the window.
        
        '''

        return self.run_native("on_remove")
    # _____________________________________________________________________

    def get_center(self):
        '''
        Center that will be used when the primitive is rotated or scaled.
        This center is local space, and will not ever be transformed.
        '''
        return Point.create_attached(self._native.get_center, self._native.set_center)
    # _____________________________________________________________________

    def get_width(self):
        '''
        Width of the bounding box after scale transformation.
        '''

        return self.run_native("get_width")
    # _____________________________________________________________________

    def get_height(self):
        '''
        Height of the bounding box after scale transformation.
        '''

        return self.run_native("get_height")
    # _____________________________________________________________________

    def get_x(self):
        '''
        X component of the position.
        
        '''

        return self.run_native("get_x")
    # _____________________________________________________________________

    def get_y(self):
        '''
        Y component of the position.
        
        '''

        return self.run_native("get_y")
    # _____________________________________________________________________

    def get_top(self):
        '''
        Distance between the top of the bounding box and the screen.
        
        '''

        return self.run_native("get_top")
    # _____________________________________________________________________

    def get_left(self):
        '''
        Distance between the left edge of the bounding box and the screen.
        
        '''

        return self.run_native("get_left")
    # _____________________________________________________________________

    def get_tex_center(self):
        '''
        UV coordinate that is the transformation center for the texture.
        
        '''

        return self.run_native("get_tex_center")
        
    # _____________________________________________________________________
    
    def get_tex_x(self):
        
        return self.run_native("get_tex_x")
    
    # _____________________________________________________________________
        
    def get_tex_y(self):
        
        return self.run_native("get_tex_y")
    
    # _____________________________________________________________________
        
    def set_tex_x(self, val):
        
        return self.run_native("set_tex_x", val)
    
    # _____________________________________________________________________
        
    def set_tex_y(self, val):
        
        return self.run_native("set_tex_y", val)
    # _____________________________________________________________________

    def get_tex_position(self):
        '''
        UV position offset of the texture inside this primitive.
        
        '''

        return Point.create_attached(self._native.get_tex_position, self._native.set_tex_position)
    # _____________________________________________________________________

    def get_tex_scale(self):
        '''
        UV scale factor of the texture.
        '''

        return Point.create_attached(self._native.get_tex_scale, self._native.set_tex_scale)
    # _____________________________________________________________________

    def get_tex_rotation(self):
        return self.run_native("get_tex_rotation")
    # _____________________________________________________________________

    def get_position(self):
        return Point.create_attached(self._native.get_position, self._native.set_position)
    # _____________________________________________________________________

    def get_rotation(self):
        return self.run_native("get_rotation")
    # _____________________________________________________________________

    def get_scale(self):
        return Point.create_attached(self._native.get_scale, self._native.set_scale)
    # _____________________________________________________________________

    def get_vertices(self):
        return self.run_native("get_vertices")

    # _____________________________________________________________________

    def is_stick(self):
        return self.run_native("is_stick")
    # _____________________________________________________________________

    def get_trans_vertices(self):
        return self.run_native("get_trans_vertices")
    # _____________________________________________________________________

    def get_image(self):
        return self.run_native("get_image")
    # _____________________________________________________________________

    def get_alpha(self):
        return self.run_native("get_alpha")
    # _____________________________________________________________________

    def set_center(self, center):
        '''
        Center that will be used when the primitive is rotated or scaled.
        This center is local space, and will not ever be transformed.
        '''

        return self.run_native("set_center", center)
    # _____________________________________________________________________

    def set_width(self, width):
        '''
        Recalculates the scale to attain the desired width AFTER scale 
        transformation.
        '''

        return self.run_native("set_width", width)
    # _____________________________________________________________________

    def set_height(self, height):
        '''
        Recalculates the scale to attain the desired height AFTER scale 
        transformation.
        '''

        return self.run_native("set_height", height)
    # _____________________________________________________________________

    def set_x(self, x):
        '''
        Sets the X component of the position.
        
        '''

        return self.run_native("set_x", x)
    # _____________________________________________________________________

    def set_y(self, y):
        '''
        Sets the Y component of the position.
        
        '''

        return self.run_native("set_y", y)
    # _____________________________________________________________________

    def set_top(self, top):
        '''
        Sets the distance of the topmost vertex to the top of the screen.
        '''

        return self.run_native("set_top", top)
    # _____________________________________________________________________

    def set_left(self, left):
        '''
        Sets the distance of the leftmost vertex to the top of the screen.
        
        '''

        return self.run_native("set_left", left)
    # _____________________________________________________________________

    def set_alpha(self, alpha):
        return self.run_native("set_alpha", alpha)
    # _____________________________________________________________________

    def set_trans_vertices(self, transVertices):
        '''
        Sets vertices after they are transformed by an outside class.
        This usually represents vertices transformed by the window. 
        The primitive can store those vertices to make accessing them 
        easier in the future.
        '''

        return self.run_native("set_trans_vertices", transVertices)
    # _____________________________________________________________________

    def set_position(self, position):
        return self.run_native("set_position", position)
    # _____________________________________________________________________

    def set_rotation(self, rotation):
        return self.run_native("set_rotation", rotation)
    # _____________________________________________________________________

    def set_scale(self, scale):
        return self.run_native("set_scale", scale)
    
    # _____________________________________________________________________

    def set_stick(self, stick):
        return self.run_native("set_stick", stick)
    # _____________________________________________________________________

    def set_image(self, image):
        return self.run_native("set_image", image)
    # _____________________________________________________________________

    def set_tex_center(self, texCenter):
        return self.run_native("set_tex_center", texCenter)
    # _____________________________________________________________________

    def set_tex_position(self, texPosition):
        return self.run_native("set_tex_position", texPosition)
    # _____________________________________________________________________

    def set_tex_scale(self, texScale):
        return self.run_native("set_tex_scale", texScale)
    # _____________________________________________________________________

    def set_tex_rotation(self, texRotation):
        return self.run_native("set_tex_rotation", texRotation)
    # _____________________________________________________________________

    def copy_from(self, p):
        return self.run_native("copy_from", p)
    # _____________________________________________________________________

    def transformation_matrix(self):
        '''
        Returns the transformation matrix for this primitive.
        '''

        return self.run_native("transformation_matrix")

    # ---------------------------------------------------------------------
    # Properties
    # ---------------------------------------------------------------------

    center = property(get_center, set_center)
    width = property(get_width, set_width)
    height = property(get_height, set_height)
    x = property(get_x, set_x)
    y = property(get_y, set_y)
    top = property(get_top, set_top)
    left = property(get_left, set_left)
    tex_center = property(get_tex_center, set_tex_center)
    tex_position = property(get_tex_position, set_tex_position)
    tex_scale = property(get_tex_scale, set_tex_scale)
    tex_rotation = property(get_tex_rotation, set_tex_rotation)
    rotation = property(get_rotation, set_rotation)
    vertices = property(get_vertices)
    trans_vertices = property(get_trans_vertices, set_trans_vertices)
    image = property(get_image, set_image)
    alpha = property(get_alpha, set_alpha)
    tex_x = property(get_tex_x, set_tex_x)
    tex_y = property(get_tex_y, set_tex_y)

NativeClass.class_map[libfp_core.Primitive] = Primitive

from fruitpunch.native.elements import Element
import libfp_core
from fruitpunch.native.native_class import NativeClass
from fruitpunch.native.graphics.vertex import Point

class BodyType:
    static = libfp_core.BodyType.static
    dynamic = libfp_core.BodyType.dynamic
    kinematic = libfp_core.BodyType.kinematic

class Body(Element):
    '''
    Represents a box2d body and inherits Element.     
    
    Any element that is a transformable and has a body added to it will 
    automatically be transformed into a body that behaves physically on 
    the screen by the means of Shapers registered into the world class.     
    '''

    def __init__(self, bodytype=None):
        NativeClass.__init__(self)
        
        self.store(libfp_core.Body())
        
        if not bodytype is None:
            self.type = bodytype        

    # ---------------------------------------------------------------------
    # Native Methods
    # ---------------------------------------------------------------------

    def create(self):
        '''
        Creates the body fixture and shape based on its parent.
        
        '''

        return self.run_native("create")
    # _____________________________________________________________________

    def render_frame(self):
        '''
        Updates the parent with the position and rotation of the body in 
        the physics world.
        '''

        return self.run_native("render_frame")
    # _____________________________________________________________________

    def get_transformable(self):
        return self.run_native("get_transformable")
    # _____________________________________________________________________

    def set_transformable(self, transformable):
        return self.run_native("set_transformable", transformable)
    # _____________________________________________________________________

    def get_world(self):
        return self.run_native("get_world")
    # _____________________________________________________________________

    def set_world(self, world):
        return self.run_native("set_world", world)
    # _____________________________________________________________________

    def get_type(self):
        return self.run_native("get_type")
    # _____________________________________________________________________

    def set_type(self, btype):
        return self.run_native("set_type", btype)
    # _____________________________________________________________________

    def get_shape_scale(self):
        return self.run_native("get_shape_scale")
    # _____________________________________________________________________

    def set_shape_scale(self, shapeScale):
        return self.run_native("set_shape_scale", shapeScale)
    # _____________________________________________________________________

    def get_linear_velocity(self):
        return Point.create_attached(self._native.get_linear_velocity, self._native.set_linear_velocity)
    # _____________________________________________________________________

    def set_linear_velocity(self, velocity):
        p = libfp_core.Point()
        p.x = velocity.x
        p.y = velocity.y
        
        return self.run_native("set_linear_velocity", p)
    # _____________________________________________________________________

    def get_angular_velocity(self):
        return self.run_native("get_angular_velocity")
    # _____________________________________________________________________

    def set_angular_velocity(self, angularVelocity):
        return self.run_native("set_angular_velocity", angularVelocity)
    
    # _____________________________________________________________________
    
    def get_friction(self):
        return self.run_native("get_friction")
    
    # _____________________________________________________________________
    
    def set_friction(self, friction):
        return self.run_native("set_friction", friction)

    # _____________________________________________________________________
    
    def get_linear_damping(self):
        return self.run_native("get_linear_damping")
    
    # _____________________________________________________________________
    
    def set_linear_damping(self, linearDamping):
        return self.run_native("set_linear_damping", linearDamping)
    # _____________________________________________________________________
    
    def apply_torque(self, torque):
        return self.run_native("apply_torque", torque)
    # _____________________________________________________________________
    
    def apply_angular_impulse(self, impulse):
        return self.run_native("apply_angular_impulse", impulse)

    # _____________________________________________________________________
    
    def apply_force(self, force, point):
        fp_core_force = libfp_core.Point()
        fp_core_force.x = force.x
        fp_core_force.y = force.y
        
        fp_core_point = libfp_core.Point()
        fp_core_point.x = point.x
        fp_core_point.y = point.y
        
        return self.run_native("apply_force", fp_core_force, fp_core_point)
    
    # _____________________________________________________________________
    
    def set_is_sensor(self, isSensor):
        return self.run_native("set_is_sensor", isSensor)
    
    # _____________________________________________________________________
    
    def get_is_sensor(self):
        return self.run_native("get_is_sensor")
    # _____________________________________________________________________
    
    # ---------------------------------------------------------------------
    # Properties
    # ---------------------------------------------------------------------

    transformable = property(get_transformable, set_transformable)
    world = property(get_world, set_world)
    type = property(get_type, set_type)
    shape_scale = property(get_shape_scale, set_shape_scale)
    linear_velocity = property(get_linear_velocity, set_linear_velocity)
    angular_velocity = property(get_angular_velocity, set_angular_velocity)
    friction = property(get_friction, set_friction)
    linear_damping = property(get_linear_damping, set_linear_damping)
    isSensor = property(get_is_sensor, set_is_sensor)

NativeClass.class_map[libfp_core.Body] = Body
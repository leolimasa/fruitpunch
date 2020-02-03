from fruitpunch.native.elements.element import Element
import libfp_core
from fruitpunch.native.native_class import NativeClass

class PhysicsWorld(Element):
    '''
    A container for processing physics and detect collision events.     
    '''

    def __init__(self):
        NativeClass.__init__(self)
        
        self.store(libfp_core.PhysicsWorld())        

    # ---------------------------------------------------------------------
    # Native Methods
    # ---------------------------------------------------------------------

    # _____________________________________________________________________

    def init(self):
        '''
        Makes the physics world ready to accept bodies and trigger 
        contact events.
        '''

        return self.run_native("init")
    # _____________________________________________________________________

    def render_frame(self):
        '''
        Updates the physical world.
        Executed every frame, and is responsible for executing a single 
        step that updates the status of the bodies, contacts, and joints in 
        the physics world. The framerate can be set by setting the timeStep 
        member variable.
        '''

        return self.run_native("render_frame")

    def get_bodies(self):
        return self.run_native("get_bodies")
    # _____________________________________________________________________

    def get_gravity(self):
        return self.run_native("get_gravity")
    # _____________________________________________________________________

    def get_joints(self):
        return self.run_native("get_joints")
    # _____________________________________________________________________

    def get_pixel_size(self):
        return self.run_native("get_pixel_size")
    # _____________________________________________________________________

    def get_position_iterations(self):
        return self.run_native("get_position_iterations")
    # _____________________________________________________________________

    def get_shapers(self):
        return self.run_native("get_shapers")
    # _____________________________________________________________________

    def get_timestep(self):
        return self.run_native("get_timestep")
    # _____________________________________________________________________

    def get_velocity_iterations(self):
        return self.run_native("get_velocity_iterations")
    # _____________________________________________________________________

    def get_world(self):
        return self.run_native("get_world")
    # _____________________________________________________________________

    def get_bodies_sensor_by_default(self):
        return self.run_native("get_bodies_sensor_by_default")
    # _____________________________________________________________________
    
    def set_bodies(self, bodies):
        return self.run_native("set_bodies", bodies)
    # _____________________________________________________________________

    def set_gravity(self, gravity):
        p = libfp_core.Point()
        p.x = gravity.x
        p.y = gravity.y
        
        return self.run_native("set_gravity", p)
    # _____________________________________________________________________

    def set_pixel_size(self, pixelSize):
        return self.run_native("set_pixel_size", pixelSize)
    # _____________________________________________________________________

    def set_position_iterations(self, positionIterations):
        return self.run_native("set_position_iterations", positionIterations)
    # _____________________________________________________________________

    def set_timestep(self, timestep):
        return self.run_native("set_timestep", timestep)
    # _____________________________________________________________________

    def set_velocity_iterations(self, velocityIterations):
        return self.run_native("set_velocity_iterations", velocityIterations)
    
    # ______________________________________________________________________
    
    def set_bodies_sensor_by_default(self, bodiesSensorByDefault):
        print("set_bodies_sensor_by_default called")
        return self.run_native("set_bodies_sensor_by_default", bodiesSensorByDefault)

    # ---------------------------------------------------------------------
    # Properties
    # ---------------------------------------------------------------------

    bodies = property(get_bodies, set_bodies)
    gravity = property(get_gravity, set_gravity)
    joints = property(get_joints)
    pixel_size = property(get_pixel_size, set_pixel_size)
    position_iterations = property(get_position_iterations, set_position_iterations)
    shapers = property(get_shapers)
    timestep = property(get_timestep, set_timestep)
    velocity_iterations = property(get_velocity_iterations, set_velocity_iterations)
    bodies_sensor_by_default = property(get_bodies_sensor_by_default, set_bodies_sensor_by_default)
    world = property(get_world)

NativeClass.class_map[libfp_core.PhysicsWorld] = PhysicsWorld
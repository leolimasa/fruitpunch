'''
Created on Sep 21, 2012

@author: leo
'''
import libfp_core

class PhysicsWorld(libfp_core.PhysicsWorld):
    pass
        

class BodyType:
    static = libfp_core.BodyType.static
    dynamic = libfp_core.BodyType.dynamic
    kinematic = libfp_core.BodyType.kinematic

class Body(libfp_core.Body):
    def __init__(self, body_type=BodyType.dynamic):
        super(Body, self).__init__()
        self.type = body_type
        print("Body initialized")
    
    def on_add(self):
        print("Body added")
        self.create()

class DistanceJoint(libfp_core.DistanceJoint):
    def on_add(self):
        print('DistanceJoint added')
        
class MouseJoint(libfp_core.MouseJoint):
    def on_add(self):
        print('MouseJoint added')
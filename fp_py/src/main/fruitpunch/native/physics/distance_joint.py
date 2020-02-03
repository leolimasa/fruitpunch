from fruitpunch.native.physics.physics_joint import PhysicsJoint
import libfp_core
from fruitpunch.native.native_class import NativeClass

class DistanceJoint(PhysicsJoint):

    def __init__(self, element_a=None, element_b=None):
        NativeClass.__init__(self)
        
        self.store(libfp_core.DistanceJoint())
        
        if not element_a is None:
            self.element_a = element_a
            self.element_b = element_b
                    

    # ---------------------------------------------------------------------
    # Native Methods
    # ---------------------------------------------------------------------

    # _____________________________________________________________________

    def create(self):
        return self.run_native("create")

    # ---------------------------------------------------------------------
    # Properties
    # ---------------------------------------------------------------------


NativeClass.class_map[libfp_core.DistanceJoint] = DistanceJoint
from fruitpunch.native.elements.element import Element
import libfp_core
from fruitpunch.native.native_class import NativeClass

class PhysicsJoint(Element):

    def __init__(self, element_a=None, element_b=None):
        NativeClass.__init__(self)
        
        self.store(libfp_core.PhysicsJoint())
        
        if not element_a is None:
            self.element_a = element_a
            self.element_b = element_b
                    

    # ---------------------------------------------------------------------
    # Native Methods
    # ---------------------------------------------------------------------

    # _____________________________________________________________________

    def create(self):
        return self.run_native("create")
    # _____________________________________________________________________

    def retrieve_body_a(self):
        return self.run_native("retrieve_body_a")
    # _____________________________________________________________________

    def retrieve_body_b(self):
        return self.run_native("retrieve_body_b")
    # _____________________________________________________________________

    def get_world(self):
        return self.run_native("get_world")
    # _____________________________________________________________________

    def get_element_a(self):
        return self.run_native("get_element_a")
    # _____________________________________________________________________

    def set_element_a(self, elementA):
        return self.run_native("set_element_a", elementA)
    # _____________________________________________________________________

    def get_element_b(self):
        return self.run_native("get_element_b")
    # _____________________________________________________________________

    def set_element_b(self, elementB):
        return self.run_native("set_element_b", elementB)
    # _____________________________________________________________________
    
    # ---------------------------------------------------------------------
    # Properties
    # ---------------------------------------------------------------------

    world = property(get_world)
    body_a = property(retrieve_body_a)
    body_b = property(retrieve_body_b)
    element_a = property(get_element_a, set_element_a)
    element_b = property(get_element_b, set_element_b)

NativeClass.class_map[libfp_core.PhysicsJoint] = PhysicsJoint
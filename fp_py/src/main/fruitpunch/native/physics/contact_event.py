
import libfp_core
from fruitpunch.native.common.event import Event
from fruitpunch.native.native_class import NativeClass

class ContactEvent(Event):
    '''
    An event that is triggered when 2 physics objects on screen
    collide with one another...
    '''
    
    def __init__(self):
        NativeClass.__init__(self)
        
        self.store(libfp_core.ContactEvent())
        
    '''
    collision event
    '''
    
    # ---------------------------------------------------------------------
    # Native Methods
    # ---------------------------------------------------------------------
    
    # _____________________________________________________________________

    def get_element_a(self):
        return self.run_native("get_element_a")
    # _____________________________________________________________________
    
    def set_element_a(self, elA):
        return self.run_native("set_element_a", elA)
    # _____________________________________________________________________

    def get_element_b(self):
        return self.run_native("get_element_b")
    # _____________________________________________________________________
    
    def set_element_b(self, elB):
        return self.run_native("set_element_b", elB)
        
    # ---------------------------------------------------------------------
    # Properties
    # ---------------------------------------------------------------------
    
    element_a = property(get_element_a, set_element_a)
    element_b = property(get_element_b, set_element_b)
    
NativeClass.class_map[libfp_core.ContactEvent] = ContactEvent

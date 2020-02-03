'''
Created on Nov 3, 2012

@author: leo
'''
import libfp_core
from fruitpunch.native.native_class import NativeClass
class Event(NativeClass):
    '''
    An event that can be passed to any Observer.
    It is used to store information that will be passed through the observable and
    retrieved by the observer.
    
    In the following example, my character fires the "jump" event:
    
    jump_event = Event("jump")
    jump_event.height = 10
    
    mycharacter.notify(jump_event)
    
    @see: Observer
    '''
    
    def __init__(self, name="undefined"):
        NativeClass.__init__(self)
        
        self.store(libfp_core.Event(name))
        
    def get_name(self):
        return self.run_native("get_name")
    
    name = property(get_name)
    
NativeClass.class_map[libfp_core.Event] = Event
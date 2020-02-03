import libfp_core
from fruitpunch.native.native_class import NativeClass
from fruitpunch.native.common.event import Event


class NumberEvent(Event):
    
    def __init__(self, name="undefined"):
        NativeClass.__init__(self)
        
        self.store(libfp_core.NumberEvent(name))
        
    def get_number(self):
        return self.run_native("get_number")
    
    def set_number(self, number):
        return self.run_native("set_number", number)
    
    number = property(get_number, set_number)
    
NativeClass.class_map[libfp_core.NumberEvent] = NumberEvent
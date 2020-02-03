import libfp_core
from fruitpunch.native.native_class import NativeClass

class Iterator(NativeClass):

    def __init__(self):
        NativeClass.__init__(self)
        
        self.store(libfp_core.Iterator())
    
    def go_to(self, i):
        return self.run_native("go_to", i)
    
    def get(self):
        return self.run_native("get")
    
    def next(self):
        val = self.run_native("next")
        if not val:
            raise StopIteration
        return self.get()
    
    def remove(self):
        return self.run_native("remove")
    
NativeClass.class_map[libfp_core.Iterator] = Iterator
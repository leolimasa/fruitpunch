from fruitpunch.native.common.observable import Observable
import libfp_core
from fruitpunch.native.native_class import NativeClass

class Property(Observable):
    def __init__(self):
        NativeClass.__init__(self)
        
        self.store(libfp_core.Property())
        self.listen({"get": self.on_get,
                     "set": self.on_set})
    
    def on_get(self, ev):
        ev.value = self.get()
    
    def on_set(self, ev):
        self.set(ev.value)
    
    def get(self):
        '''
        Abstract method to be implemented by the user
        '''
        pass
    
    def set(self, value):
        '''
        Abstract method to be implemented by the user
        '''
        pass
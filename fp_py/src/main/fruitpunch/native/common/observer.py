from fruitpunch.native.native_class import NativeClass
import libfp_core

class ObserverWrap(libfp_core.ObserverWrap):
    def action(self):
        ev = NativeClass.to_python(self.get_event())
        f = self.function
        f(ev)

class Observer(NativeClass):
    def __init__(self):
        NativeClass.__init__(self)
        
        self.store(ObserverWrap())
        self._native.function = self.action
    
    # _________________________________________________________________________
    
    def get_event(self):
        return self.run_native("get_event")
    
    # _________________________________________________________________________
    
    def get_event_name(self):
        return self.run_native("get_event_name")
    
    # _________________________________________________________________________
    
    def get_instance(self):
        return self.run_native("get_instance")
    
    # _________________________________________________________________________
    
    def action(self):
        # by default, this does nothing, since it is supposed to
        # be overriden by the child
        pass
    
    # _________________________________________________________________________
        
        
    event = property(get_event)
    event_name = property(get_event_name)
    instance = property(get_instance)
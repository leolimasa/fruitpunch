from fruitpunch.native.native_class import NativeClass
import libfp_core
from fruitpunch.native.common.event import Event

class PropertyEvent(Event):
    '''
    Event triggered when a property is set or returned.     
    '''

    def __init__(self, evname=None):
        NativeClass.__init__(self)
        
        if not evname is None:
            self.store(libfp_core.PropertyEvent(evname))        

    # ---------------------------------------------------------------------
    # Native Methods
    # ---------------------------------------------------------------------

    # _____________________________________________________________________

    def get_value(self):
        return self.run_native("get_value")
    # _____________________________________________________________________

    def set_value(self, value):
        return self.run_native("set_value", value)

    # ---------------------------------------------------------------------
    # Properties
    # ---------------------------------------------------------------------

    value = property(get_value, set_value)

NativeClass.class_map[libfp_core.PropertyEvent] = PropertyEvent
from fruitpunch.native.elements.animation import Animation
import libfp_core
from fruitpunch.native.native_class import NativeClass
from fruitpunch.native.elements.playable import Playable
from fruitpunch.attribute_property import AttributeProperty

class Tween(Playable):

    def __init__(self, instance=None, attribute=None):
        NativeClass.__init__(self)

        self.store(libfp_core.Tween())
        
        # We want the property to be created once it starts running
        self.listen({"pre_render": self.create_property})
        self.instance = instance
        self.attribute = attribute        

    # ---------------------------------------------------------------------
    # Native Methods
    # ---------------------------------------------------------------------

    def render_single(self, frame):
        return self.run_native("render_single", frame)
    # _____________________________________________________________________

    def calculate_duration(self):
        return self.run_native("calculate_duration")
    # _____________________________________________________________________

    def interpolate(self, step):
        '''
        
        Should return a normalized function from which the tween will be 
        calculated. A normalized function has boundaries between 0 and 1, 
        where 0 is the start of the tween, and 1 is the end. Those values 
        will be provided by the step argument.
        '''

        return self.run_native("interpolate", step)
    # _____________________________________________________________________

    def get_duration(self):
        return self.run_native("get_duration")
    # _____________________________________________________________________

    def set_duration(self, duration):
        return self.run_native("set_duration", duration)
    # _____________________________________________________________________

    def get_end_value(self):
        return self.run_native("get_end_value")
    # _____________________________________________________________________

    def set_end_value(self, endValue):
        return self.run_native("set_end_value", endValue)
    # _____________________________________________________________________

    def get_property(self):
        return self.run_native("get_property")
    # _____________________________________________________________________

    def set_property(self, prop):
        return self.run_native("set_property", prop)
    # _____________________________________________________________________

    def get_start_value(self):
        return self.run_native("get_start_value")
    # _____________________________________________________________________

    def set_start_value(self, startValue):
        return self.run_native("set_start_value", startValue)
    
    # _____________________________________________________________________
    
    def create_property(self, ev=None):
        '''
        If self.instance and self.attribute are set, this will automatically
        create a property that use that information to set the tween value
        of the target instance.
        '''
        
        if self.instance == None or self.attribute == None or self.prop != None:
            return
        
        self.prop = AttributeProperty(self.instance, self.attribute)
        

    # ---------------------------------------------------------------------
    # Properties
    # ---------------------------------------------------------------------

    duration = property(get_duration, set_duration)
    end_value = property(get_end_value, set_end_value)
    prop = property(get_property, set_property)
    start_value = property(get_start_value, set_start_value)

NativeClass.class_map[libfp_core.Tween] = Tween
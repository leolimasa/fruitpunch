from fruitpunch.native.elements.playable import Playable
import libfp_core
from fruitpunch.native.native_class import NativeClass

class Animation(Playable):


    def __init__(self):
        NativeClass.__init__(self)
        
        self.store(libfp_core.Animation())        

    # ---------------------------------------------------------------------
    # Native Methods
    # ---------------------------------------------------------------------

    # _____________________________________________________________________

    def calculate_duration(self):
        return self.run_native("calculate_duration")
    # _____________________________________________________________________

    def render_single(self, frame):
        return self.run_native("render_single", frame)

    # ---------------------------------------------------------------------
    # Properties
    # ---------------------------------------------------------------------


NativeClass.class_map[libfp_core.Animation] = Animation
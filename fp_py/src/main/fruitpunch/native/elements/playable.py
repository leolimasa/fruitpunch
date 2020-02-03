from fruitpunch.native.elements.element import Element
import libfp_core
from fruitpunch.native.native_class import NativeClass

class Playable(Element):

    def __init__(self):
        NativeClass.__init__(self)
        
        self.store(libfp_core.Playable())
        
        self.listen({"render_single": self.on_render_single,
                     "calculate_duration": self.on_calculate_duration})

    # ---------------------------------------------------------------------
    # Native Methods
    # ---------------------------------------------------------------------

    # _____________________________________________________________________

    def start(self):
        return self.run_native("start")
    # _____________________________________________________________________

    def stop(self):
        return self.run_native("stop")

    # _____________________________________________________________________

    def get_current_frame(self):
        return self.run_native("get_current_frame")
    # _____________________________________________________________________

    def set_current_frame(self, currentFrame):
        return self.run_native("set_current_frame", currentFrame)
    # _____________________________________________________________________

    def is_playing(self):
        return self.run_native("is_playing")
    # _____________________________________________________________________

    def set_playing(self, isPlaying):
        return self.run_native("set_playing", isPlaying)
    # _____________________________________________________________________

    def is_loop(self):
        return self.run_native("is_loop")
    # _____________________________________________________________________

    def set_loop(self, loop):
        return self.run_native("set_loop", loop)
    # _____________________________________________________________________

    def get_start_frame(self):
        return self.run_native("get_start_frame")
    # _____________________________________________________________________

    def set_start_frame(self, startFrame):
        return self.run_native("set_start_frame", startFrame)
    # _____________________________________________________________________

    def get_end_frame(self):
        return self.run_native("get_end_frame")
    
    # _____________________________________________________________________
    
    def set_frame_duration(self, duration):
        return self.run_native("set_frame_duration", duration)
    
    # _____________________________________________________________________
    
    def get_frame_duration(self):
        return self.run_native("get_frame_duration")
    
    # _____________________________________________________________________
    
    def on_render_single(self, e):
        self.render_single(e.number)
    
    # _____________________________________________________________________
    
    def on_calculate_duration(self, e):
        e.number = self.calculate_duration()    
    
    # _____________________________________________________________________
    
    def render_single(self, frame_number):
        pass
    
    # _____________________________________________________________________
    
    def calculate_duration(self):
        pass

    # ---------------------------------------------------------------------
    # Properties
    # ---------------------------------------------------------------------

    current_frame = property(get_current_frame, set_current_frame)
    start_frame = property(get_start_frame, set_start_frame)
    end_frame = property(get_end_frame)
    loop = property(is_loop, set_loop)
    frame_duration = property(get_frame_duration, set_frame_duration)

NativeClass.class_map[libfp_core.Playable] = Playable
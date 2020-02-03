import libfp_core
from fruitpunch.native.native_class import NativeClass
from fruitpunch.native.common.observable import Observable

class App(Observable):

    def __init__(self):
        NativeClass.__init__(self)
        
        self.store(libfp_core.App())
        self.listen({"render": self.on_render, 
                     "init": self.on_init, 
                     "change_scene": self.on_scene_change})
        
    # ---------------------------------------------------------------------
    # Native Methods
    # ---------------------------------------------------------------------

    def init(self):
        '''
        Associates the app to the runtime.
        Associates this App to the runtime by attaching the renderFrame to
        the current runtime. Fires: "init".
        '''

        return self.run_native("init")
    # _____________________________________________________________________

    def render_frame(self):
        '''
        Renders the frame of the current scene, if there is one.
        
        '''

        return self.run_native("render_frame")
    # _____________________________________________________________________

    def go_to_scene(self, scene):
        '''
        Unloads the currently loaded scene and loads a new one.
        '''

        return self.run_native("go_to_scene", scene)
    # _____________________________________________________________________

    def on_init(self, event):
        '''
        Method to be implemented by the client.
        '''
        pass
    # _____________________________________________________________________

    def on_render(self, event):
        '''
        Method to be implemented by the client.
        '''
        pass
    
    # _____________________________________________________________________

    def on_scene_change(self, event):
        '''
        Method to be implemented by the client.
        '''
        pass
    # _____________________________________________________________________

    def get_current_scene(self):
        return self.run_native("get_current_scene")
    # _____________________________________________________________________

    def get_runtime(self):
        return self.run_native("get_runtime")
    # _____________________________________________________________________

    def set_current_scene(self, currentScene):
        return self.run_native("set_current_scene", currentScene)

    # ---------------------------------------------------------------------
    # Properties
    # ---------------------------------------------------------------------

    current_scene = property(get_current_scene, set_current_scene)
    runtime = property(get_runtime)
    
NativeClass.class_map[libfp_core.App] = App
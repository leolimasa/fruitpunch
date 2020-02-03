from fruitpunch import App

class RunnerApp(App):
    
    
    def __init__(self, scene):
        super(RunnerApp, self).__init__()
        self.scene = scene
    
    def on_init(self, event):
        self.go_to_scene(self.scene)
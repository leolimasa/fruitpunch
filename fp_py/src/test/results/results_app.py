'''
Created on Aug 15, 2012

@author: leo
'''
from fruitpunch import App
from results.results_scene import ResultsScene

class ResultsApp(App):
    '''
    classdocs
    '''

    def on_init(self, event):
        scene = ResultsScene()
        scene.results = self.results
        self.go_to_scene(scene)
        
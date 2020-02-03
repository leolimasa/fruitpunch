'''
Created on Dec 22, 2012

@author: leo
'''
import unittest
from fruitpunch import Scene, Collector, Sprite, App

class TestApp(App):
    def on_init(self, event):
        self.go_to_scene(self.scene)

class TestScene(Scene):
    def on_init(self, ev):
        sprite = Sprite("grey.png")
        self.add(sprite)
        
        c = sprite.add(Collector())
        
        self.collector = c
        self.sprite = sprite

class TestCollector(unittest.TestCase):


    def setUp(self):
        app = TestApp()
        self.scene = TestScene()
        app.scene = self.scene
        app.init()


    def tearDown(self):
        pass

    def testOnAdd(self):
        c = self.scene.collector

        self.assertEqual(c.min_bounds.x, 0)
        self.assertEqual(c.min_bounds.y, 0)
        self.assertEqual(c.max_bounds.x, 800)
        self.assertEqual(c.max_bounds.y, 600)
    
    def testOnRender(self):
        c = self.scene.collector
        s = self.scene.sprite
        
        # Do not remove if it is within bounds
        s.left = 100
        s.top = 100
        for i in range(70):
            self.scene.render_frame()
            
        self.assertEqual(s.parent, self.scene)
        
        # Remove if it is out of bounds
        s.left = -100
        s.top = -100
        for i in range(70):
            self.scene.render_frame()
        
        self.assertEqual(s.parent, None)


if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()